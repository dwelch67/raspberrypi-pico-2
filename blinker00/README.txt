
This is the printf hello world of microcontrollers, blink an led 
based on a count to N delay loop, minimal code to get gpio going.

You can look at the blink_simple example in the pico examples as
a starting point.  What they do not show you there is some items
buried behind the scenes.

For the pico 1, one of the things you have to do is release reset to
IO_BANK0.  And set up the pin as a SIO output.

int notmain ( void )
{
    unsigned int ra;

    PUT32(RESETS_RESET_CLR,1<<5); //IO_BANK0
    while(1)
    {
        if((GET32(RESETS_RESET_DONE_RW)&(1<<5))!=0) break;
    }
    PUT32(SIO_GPIO_OE_CLR,1<<25);
    PUT32(SIO_GPIO_OUT_CLR,1<<25);
    PUT32(IO_BANK0_GPIO25_CTRL_RW,5); //SIO
    PUT32(SIO_GPIO_OE_SET,1<<25);
    for(ra=0;ra<100;ra++)
    {
        PUT32(SIO_GPIO_OUT_XOR,1<<25);
        DELAY(0x10000);
    }
    return(0);
}


With the pico 2 another logic block needs to be enabled and touched in
order to get basic gpio output and that is PADS_BANK0. 

int notmain ( void )
{
    unsigned int ra;

    ra=(1<<6)|(1<<9); //IO_BANK0 PADS_BANK0
    PUT32(RESETS_RESET_CLR,ra);
    while(1)
    {
        if((GET32(RESETS_RESET_DONE_RW)&ra)==ra) break;
    }
    PUT32(SIO_GPIO_OE_CLR,1<<PIN);
    PUT32(SIO_GPIO_OUT_CLR,1<<PIN);
    PUT32(PADS_BANK0_BASE_GPIO25_SET,1<<6);
    PUT32(IO_BANK0_GPIO25_CTRL_RW,5); //SIO
    PUT32(PADS_BANK0_BASE_GPIO25_CLR,1<<8); //ISO
    PUT32(SIO_GPIO_OE_SET,1<<PIN);
    while(1)
    {
        PUT32(SIO_GPIO_OUT_XOR,1<<PIN);
        DELAY(0x100000);
    }
    return(0);
}

Some of the addres space has changed although they used the same names
for things that were there before.

The pico 2 also has two cortex-m cores but they are m33 instead of m0+
which is a more robust core with basically more thumb2 instructions.
It also contains two risc-v cores, a whole other processor family,
incompatible with arm.  I do not yet know if you can have both types
running at the same time.  I have reason to believe the arm starts first
and then if it detects a riscv binary then it runs the riscv, what that
arm does after that, assuming this is how it works, I didnt look.

How they tell the binaries apart is that we now have to put what they
call an embedded start block and end block in the binary.  From comments
it indicates within the first 256 bytes.  The cortex-m typically starts
at the first address with the vector table.  Riscv is not vector table
based it has a starting address like the full sized arms did and that
sounds like they expect that to be the beginning of the application as
well, but depending on the risc-v design, you can start it elsewhere.
Their binary design for arm they have the start block after the vector
table and it looks something like this

.align
.globl start_block
start_block:
.word 0xFFFFDED3
.word 0x10210142 ;#@ arm
.word 0x000001FF
.word end_block - start_block
.word 0xAB123579

You can go try to read their code for more details.  The first and last
word are hardcoded magic patterns they hope are not part of a real
binary.  The second word is actually four bytes with each byte meaning
something.  For some reason they have the start and end blocks point
at each other.  They put their end block at the end of the binary so I
did as well.

For riscv for some reason they chose to put the start block at the
start of the binary, messing up the entry point for the code as a reasult
they have a mechanism to indicate the entry point and for some reason
the stack pointer init value in this header, making it a longer
header.  But for my binary design I put the bootstrap first and then
the start block allowing me to have the same format start block as arm
except using the riscv magic bytes.

.align 2
.globl start_block
start_block:
.word 0xFFFFDED3
.word 0x11010142 ;#@ risc-v
.word 0x000001FF
.word end_block - start_block
.word 0xAB123579

The assembly languages for .align are different for arm .align means
four byte boundary for riscv I assume it means two byte.  For this to
work these words have to be word aligned, so .align 2 is required
for riscv (or you can use something more portable like .balign ,etc).

Both end blocks look the same other than .align and yes I could have
used .balign and had them identical.

.align
.globl end_block
end_block:
.word 0xFFFFDED3
.word 0x000001FE
.word 0x000001FF
.word start_block - end_block
.word 0xAB123579

There is no arm/risc-v difference in the end block.

There is an ever increasing fad to not learn how to use tools and
continue to over complicate and bloat the linker script for example.

Their arm binary design

vector table
start block
bootstrap
compiled code/application
end block

My design
bootstrap (including vector table)
start block
compiled code/application
end block.

My linker script (for this blinker00 example)

MEMORY
{
    flash : ORIGIN = 0x10000000, LENGTH = 0x10000
}
SECTIONS
{
    .text   : { *(.text*)   } > flash
}

Yeah...

There is no need to make a custom section for the vector table and
the start block and the bootstrap and end block.  Here is the
secret:

Make all of them .text, the default if you specify nothing.

    $(ARMGNU)-ld $(LOPS) -T flash.ld start_arm.o startblock.arm.o notmain.o endblock.o -o notmain.flash.elf

And then the order that you put things on the command line are how
they go into the binary.

At first I was overcomplicating as I was figuring out how to make
working binaries, and then the whole arm vs risc-v thing.  As I write
this I am seriouisly thinking of changing the design to this?


.cpu cortex-m0
.thumb

    .word 0x20081000
    .word reset

.thumb_func
reset:

    ;@ does the second one actually run? no
    ldr r0,=0xD0000000
    ldr r0,[r0]
    cmp r0,#0
    beq zero
    b .
    zero:

    bl notmain
    b .

To this

.cpu cortex-m0
.thumb

    .word 0x20081000
    .word reset

.globl start_block
start_block:
    .word 0xFFFFDED3
    .word 0x10210142 ;#@ arm
    .word 0x000001FF
    .word end_block - start_block
    .word 0xAB123579

.thumb_func
reset:

    ;@ does the second one actually run? no
    ldr r0,=0xD0000000
    ldr r0,[r0]
    cmp r0,#0
    beq zero
    b .
    zero:

    bl notmain
    b .

Since I now know what I know, and something similar for riscv.

Easier to get the end block at the end having it as its own file
and last in the linker script list of objects.

I have a document on the UF2 file format and tool.  Looks like it is
a microsoft invention.  Overall it is not a bad solution, they use it
in a specific way, that way has only varied slightly for the pico 2.
Borrowing from myself it appears I had done something probably wrong
with the checksum thing and sram vs flash, but then later on in my
pico 1 days I figured out something else but created a 4 byte bug that
somehow I didnt hit.  Anyway...

It is a container file made from 512 byte chunks, each chunk has a small
header and carries a 256 byte payload (leaving almost half of the chunk
unused).  The blocks are numbered from zero and each has the current
block number and total blocks.  There is now a different marker for
arm vs riscv but borrowing from myself I accidentally didnt switch it
and crossing the streams worked.  

My tool at this time produces a binary match to the files from their 
tool.  It is not a generic tool, it works for the example it is 
associated with at the time the example was written.  Nothing about
these examples are generic, they are one to dozens of self contained
individual examples, just add a toolchain.  Not reference designs but
instead, ideally, you can baremetal program too demonstrations with
ideally a higher chance of success than the typical bare metal examples.
Intended for you to learn, see, and roll your own, not to use as reference
designs.  As part of that I want as few, ideally zero, third party
tools and repos, other than a toolchain.  This includes in particular
the uf2 tool.  Easy enough to go get and then steal their tool to use
with your baremetal project.  At the same time incredibly educational
and valueable and relative to other things, easy to take an evening and
read the dozen or so things that make up the file, use/make some tools
to examine the binaries and perhaps make your own tool.  Of the file
formats out there, the way the pico folks use this one, is a pretty good
first file format to experience.

picotool uf2 convert input.elf output.uf2 --family rp2350-arm-s --abs-block
picotool uf2 convert input.elf output.uf2 --family rp2350-riscv --abs-block

For some reason, that I could speculate, if you view what would look
like a proper file and then they shoved a mostlyh hardcoded first chunk
in front, messing up the block count stuff, technically, but it works
for their solution, so I just added that block to mine, even though
experimentally, for this example, it worked without it.

Another note, if you look at thier bootstraps and the docs, there is
a disconnect.  If you can find them for the arm and the riscv go ahead
and look, these were not written by the same person.  Perhaps at some
point in development of their product they needed this but, even the
docs imply it is not needed and experimentally it appears to be not
needed.  The full sized pi parts are such that all the cores start
at once and you, as I call it, have to "sort the cores" you have to
write the startup code to take the different cores down different paths.
If you let them all just execute the same uart example then you
see the first characters you send out repeated N times then as they
compete with each other and that peripheral some characters you wanted
come out others are lost to the ether.  So you have to look for a
specific core and branch it down a different path and/or branch the
others down a different path (using some not really well/incomplete
arm documentation).  Here they have a cpuid register not to be confused
with arms cpuid, it basicallyh has one bit and zero is core 0 and 1
is core one.  

    ;@ does the second one actually run? no
    ldr r0,=0xD0000000
    ldr r0,[r0]
    cmp r0,#0
    beq zero
    b .
    zero:

    bl notmain
    b .

They indicate the proper thing to do with core one is this magic dance
to get it to branch back into the bootloader.  I just put it into an
infiite loop and if I change the beq to a bne (or equivalent in the
riscv code) nothing happens, neither core 1 is booting into this code.
Arguably I can just remove it, and I might...

.thumb_func
reset:
    bl notmain
    b .

Both processor designs have internal registers.  The assembly language
for riscv allows for addresses or names for these registers and the
design of the riscv architecture is such that there is a core id.
A core is called a hart, and there are different modes including machine
mode so 

    csrr x10, mhartid
    bnez x10, notzero

    jal notmain
    j .

notzero:
    j .

csr read the machine hart id.  Which apparently for this is a zero
or not zero (the riscv spec says that one hart must be numbered zero).

One expects that for risc-v you could also read from 0xd0000000.

Starting and using core 1 is left for another day to figure out.  And
if you can get all four cores, two arm, two riscv running at the same
time.

The riscv bootstrap could then be

    la x2,0x20081000
    jal notmain
    j .

Why 0x20081000 and not 0x20001000 as you usually do and not 0x20082000?
The docs imply/state the design of their srams is for these high
blocks to be for stack.  There are two cores of each flavor.  They used
0x20082000.  If I desire and figure out how to use the second one then 
I will use 0x20082000 as its stack starting point for core 1.  That is 
my thinking for now and I could change it at any time.

Proper pico 2 boards have a normal led on gpio pin 25, you can get
through blinking led examples without any pins or additional hardware.
Eventually you will want pins and a uart.

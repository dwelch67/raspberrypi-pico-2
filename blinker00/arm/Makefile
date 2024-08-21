
ARMGNU ?= arm-none-eabi

XCPU = -mcpu=cortex-m0

AOPS = --warn --fatal-warnings $(XCPU)
COPS = -Wall -O2 -ffreestanding $(XCPU)
LOPS = -nostdlib -nostart_armfiles

all : notmain.sram.uf2 notmain.flash.uf2

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	#rm -f *.uf2
	rm -f makeuf2

makeuf2 : makeuf2.c
	gcc -O2 makeuf2.c -o makeuf2

notmain.flash.uf2 : notmain.flash.bin makeuf2
	./makeuf2 notmain.flash.bin notmain.flash.uf2 arm flash

notmain.sram.uf2 : notmain.sram.bin makeuf2
	./makeuf2 notmain.sram.bin notmain.sram.uf2 arm sram

xnotmain.sram.uf2 : notmain.sram.bin
	picotool uf2 convert notmain.sram.elf notmain.sram.uf2 --family rp2350-arm-s --abs-block

xnotmain.flash.uf2 : notmain.flash.bin
	picotool uf2 convert notmain.flash.elf notmain.flash.uf2 --family rp2350-arm-s --abs-block

start_arm.o : start_arm.s
	$(ARMGNU)-as $(AOPS) start_arm.s -o start_arm.o

startblock.arm.o : startblock.arm.s
	$(ARMGNU)-as $(AOPS) startblock.arm.s -o startblock.arm.o

endblock.o : endblock.s
	$(ARMGNU)-as $(AOPS) endblock.s -o endblock.o

notmain.o : notmain.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c notmain.c -o notmain.o

notmain.sram.bin :          sram.ld start_arm.o startblock.arm.o notmain.o endblock.o
	$(ARMGNU)-ld $(LOPS) -T sram.ld start_arm.o startblock.arm.o notmain.o endblock.o -o notmain.sram.elf
	$(ARMGNU)-objdump -D notmain.sram.elf > notmain.sram.list
	$(ARMGNU)-objcopy -O binary notmain.sram.elf notmain.sram.bin

notmain.flash.bin :         flash.ld start_arm.o startblock.arm.o notmain.o endblock.o
	$(ARMGNU)-ld $(LOPS) -T flash.ld start_arm.o startblock.arm.o notmain.o endblock.o -o notmain.flash.elf
	$(ARMGNU)-objdump -D notmain.flash.elf > notmain.flash.list
	$(ARMGNU)-objcopy -O binary notmain.flash.elf notmain.flash.bin

##-------------------------------------------------------------------------
##
## Copyright (c) 2024 David Welch dwelch@dwelch.com
##
## Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
##
##-------------------------------------------------------------------------

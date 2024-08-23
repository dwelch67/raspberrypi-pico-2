
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void DELAY ( unsigned int );

#define RESETS_BASE                 0x40020000

#define RESETS_RESET_RW             (RESETS_BASE+0x0+0x0000)
#define RESETS_RESET_XOR            (RESETS_BASE+0x0+0x1000)
#define RESETS_RESET_SET            (RESETS_BASE+0x0+0x2000)
#define RESETS_RESET_CLR            (RESETS_BASE+0x0+0x3000)

#define RESETS_RESET_DONE_RW        (RESETS_BASE+0x8+0x0000)
#define RESETS_RESET_DONE_XOR       (RESETS_BASE+0x8+0x1000)
#define RESETS_RESET_DONE_SET       (RESETS_BASE+0x8+0x2000)
#define RESETS_RESET_DONE_CLR       (RESETS_BASE+0x8+0x3000)

#define SIO_BASE                    0xD0000000

#define SIO_GPIO_OUT_RW             (SIO_BASE+0x10)
#define SIO_GPIO_OUT_SET            (SIO_BASE+0x18)
#define SIO_GPIO_OUT_CLR            (SIO_BASE+0x20)
#define SIO_GPIO_OUT_XOR            (SIO_BASE+0x28)

#define SIO_GPIO_OE_RW              (SIO_BASE+0x30)
#define SIO_GPIO_OE_SET             (SIO_BASE+0x38)
#define SIO_GPIO_OE_CLR             (SIO_BASE+0x40)
#define SIO_GPIO_OE_XOR             (SIO_BASE+0x48)

#define IO_BANK0_BASE               0x40028000

//WHY SPARKFUN WHY???
#define IO_BANK0_GPIO2_STATUSL_RW   (IO_BANK0_BASE+0x00C+0x0000)
#define IO_BANK0_GPIO2_STATUSL_XOR  (IO_BANK0_BASE+0x00C+0x1000)
#define IO_BANK0_GPIO2_STATUSL_SET  (IO_BANK0_BASE+0x00C+0x2000)
#define IO_BANK0_GPIO2_STATUSL_CLR  (IO_BANK0_BASE+0x00C+0x3000)

//WHY SPARKFUN WHY???
#define IO_BANK0_GPIO2_CTRL_RW      (IO_BANK0_BASE+0x014+0x0000)
#define IO_BANK0_GPIO2_CTRL_XOR     (IO_BANK0_BASE+0x014+0x1000)
#define IO_BANK0_GPIO2_CTRL_SET     (IO_BANK0_BASE+0x014+0x2000)
#define IO_BANK0_GPIO2_CTRL_CLR     (IO_BANK0_BASE+0x014+0x3000)

#define IO_BANK0_GPIO25_STATUSL_RW  (IO_BANK0_BASE+0x0C8+0x0000)
#define IO_BANK0_GPIO25_STATUSL_XOR (IO_BANK0_BASE+0x0C8+0x1000)
#define IO_BANK0_GPIO25_STATUSL_SET (IO_BANK0_BASE+0x0C8+0x2000)
#define IO_BANK0_GPIO25_STATUSL_CLR (IO_BANK0_BASE+0x0C8+0x3000)

#define IO_BANK0_GPIO25_CTRL_RW     (IO_BANK0_BASE+0x0CC+0x0000)
#define IO_BANK0_GPIO25_CTRL_XOR    (IO_BANK0_BASE+0x0CC+0x1000)
#define IO_BANK0_GPIO25_CTRL_SET    (IO_BANK0_BASE+0x0CC+0x2000)
#define IO_BANK0_GPIO25_CTRL_CLR    (IO_BANK0_BASE+0x0CC+0x3000)

#define PADS_BANK0_BASE             0x40038000

//WHY SPARKFUN WHY???
#define PADS_BANK0_BASE_GPIO2_RW    (PADS_BANK0_BASE+0x0C+0x0000)
#define PADS_BANK0_BASE_GPIO2_XOR   (PADS_BANK0_BASE+0x0C+0x1000)
#define PADS_BANK0_BASE_GPIO2_SET   (PADS_BANK0_BASE+0x0C+0x2000)
#define PADS_BANK0_BASE_GPIO2_CLR   (PADS_BANK0_BASE+0x0C+0x3000)

#define PADS_BANK0_BASE_GPIO25_RW   (PADS_BANK0_BASE+0x68+0x0000)
#define PADS_BANK0_BASE_GPIO25_XOR  (PADS_BANK0_BASE+0x68+0x1000)
#define PADS_BANK0_BASE_GPIO25_SET  (PADS_BANK0_BASE+0x68+0x2000)
#define PADS_BANK0_BASE_GPIO25_CLR  (PADS_BANK0_BASE+0x68+0x3000)

#define CLOCKS_BASE                 0x40010000

#define CLK_REF_CTRL_RW             (CLOCKS_BASE+0x30+0x0000)
#define CLK_REF_CTRL_XOR            (CLOCKS_BASE+0x30+0x1000)
#define CLK_REF_CTRL_SET            (CLOCKS_BASE+0x30+0x2000)
#define CLK_REF_CTRL_CLR            (CLOCKS_BASE+0x30+0x3000)

#define CLK_SYS_CTRL_RW             (CLOCKS_BASE+0x3C+0x0000)
#define CLK_SYS_CTRL_XOR            (CLOCKS_BASE+0x3C+0x1000)
#define CLK_SYS_CTRL_SET            (CLOCKS_BASE+0x3C+0x2000)
#define CLK_SYS_CTRL_CLR            (CLOCKS_BASE+0x3C+0x3000)

#define CLK_SYS_RESUS_CTRL_RW       (CLOCKS_BASE+0x84+0x0000)
#define CLK_SYS_RESUS_CTRL_XOR      (CLOCKS_BASE+0x84+0x1000)
#define CLK_SYS_RESUS_CTRL_SET      (CLOCKS_BASE+0x84+0x2000)
#define CLK_SYS_RESUS_CTRL_CLR      (CLOCKS_BASE+0x84+0x3000)

#define XOSC_BASE                   0x40048000

#define XOSC_CTRL_RW                (XOSC_BASE+0x00+0x0000)
#define XOSC_CTRL_XOR               (XOSC_BASE+0x00+0x1000)
#define XOSC_CTRL_SET               (XOSC_BASE+0x00+0x2000)
#define XOSC_CTRL_CLR               (XOSC_BASE+0x00+0x3000)

#define XOSC_STATUS_RW              (XOSC_BASE+0x04+0x0000)
#define XOSC_STATUS_XOR             (XOSC_BASE+0x04+0x1000)
#define XOSC_STATUS_SET             (XOSC_BASE+0x04+0x2000)
#define XOSC_STATUS_CLR             (XOSC_BASE+0x04+0x3000)

#define XOSC_STARTUP_RW             (XOSC_BASE+0x0C+0x0000)
#define XOSC_STARTUP_XOR            (XOSC_BASE+0x0C+0x1000)
#define XOSC_STARTUP_SET            (XOSC_BASE+0x0C+0x2000)
#define XOSC_STARTUP_CLR            (XOSC_BASE+0x0C+0x3000)

#define XOSC_COUNT_RW               (XOSC_BASE+0x10+0x0000)
#define XOSC_COUNT_XOR              (XOSC_BASE+0x10+0x1000)
#define XOSC_COUNT_SET              (XOSC_BASE+0x10+0x2000)
#define XOSC_COUNT_CLR              (XOSC_BASE+0x10+0x3000)



//WHY SPARKFUN WHY???
#define PIN 2
#ifndef PIN
#define PIN 25
#endif

#define STK_CSR 0xE000E010
#define STK_RVR 0xE000E014
#define STK_CVR 0xE000E018

static void do_delay ( unsigned int x )
{
    unsigned int ra;

    for(ra=0;ra<x;)
    {
        if((GET32(STK_CSR)&(1<<16))!=0)
        {
            ra++;
        }
    }
}

static void clock_init ( void )
{
    PUT32(CLK_SYS_RESUS_CTRL_RW,0);
    PUT32(XOSC_CTRL_RW,0xAA0);      //1 - 15MHZ
    PUT32(XOSC_STARTUP_RW,47);      //from code
    PUT32(XOSC_CTRL_SET,0xFAB000);  //enable
    while(1)
    {
        if((GET32(XOSC_STATUS_RW)&0x80000000)!=0) break;
    }
    PUT32(CLK_REF_CTRL_RW,2); //XOSC
    PUT32(CLK_SYS_CTRL_RW,0); //reset/clk_ref
}

int notmain ( void )
{
    unsigned int ra;

    clock_init();

    ra=(1<<6)|(1<<9); //IO_BANK0 PADS_BANK0
    PUT32(RESETS_RESET_CLR,ra);
    while(1)
    {
        if((GET32(RESETS_RESET_DONE_RW)&ra)==ra) break;
    }
    PUT32(SIO_GPIO_OE_CLR,1<<PIN);
    PUT32(SIO_GPIO_OUT_CLR,1<<PIN);

    if(PIN==2)
    {
        PUT32(PADS_BANK0_BASE_GPIO2_SET,1<<6);
        PUT32(IO_BANK0_GPIO2_CTRL_RW,5); //SIO
        PUT32(PADS_BANK0_BASE_GPIO2_CLR,1<<8); //ISO
    }
    else
    {
        PUT32(PADS_BANK0_BASE_GPIO25_SET,1<<6);
        PUT32(IO_BANK0_GPIO25_CTRL_RW,5); //SIO
        PUT32(PADS_BANK0_BASE_GPIO25_CLR,1<<8); //ISO
    }

    PUT32(SIO_GPIO_OE_SET,1<<PIN);


    PUT32(STK_CSR,0x00000004);
    PUT32(STK_RVR,12000000-1);
    PUT32(STK_CVR,12000000-1);
    PUT32(STK_CSR,0x00000005);

    while(1)
    {
        PUT32(SIO_GPIO_OUT_XOR,1<<PIN);
        do_delay(10);
    }

    return(0);
}

//-------------------------------------------------------------------------
//
// Copyright (c) 2024 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------

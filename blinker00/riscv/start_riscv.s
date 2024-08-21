
.globl _start
_start:

    la x2,0x20081000

    ;#does the second one actually start? no
    csrr x10, mhartid
    bnez x10, notzero

    jal notmain
    j .

notzero:
    j .

.globl PUT32
PUT32:
    sw x11,(x10)
    ret

.globl GET32
GET32:
    lw x10,(x10)
    ret

.globl dummy
dummy:
    ret

.globl DELAY
DELAY:
    addi x10, x10,-1
    bnez x10, DELAY
    ret

;#-------------------------------------------------------------------------
;#
;# Copyright (c) 2024 David Welch dwelch@dwelch.com
;#
;# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
;#
;# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
;#
;# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
;#
;#-------------------------------------------------------------------------

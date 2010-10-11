/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *****************************************************************************/

/*
 * See ../notes/dac.txt for more info
 */

/**
 * @file dac.h
 */

#ifndef _DAC_H_
#define _DAC_H_

#ifdef __cplusplus
extern "C"{
#endif

#define DAC_BASE  0x40007400

typedef struct {
    volatile uint32 CR;
    volatile uint32 SWTRIGR;
    volatile uint32 DHR12R1;
    volatile uint32 DHR12L1;
    volatile uint32 DHR8R1;
    volatile uint32 DHR12R2;
    volatile uint32 DHR12L2;
    volatile uint32 DHR8R2;
    volatile uint32 DHR12RD;
    volatile uint32 DHR12LD;
    volatile uint32 DHR8RD;
    volatile uint32 DOR1;
    volatile uint32 DOR2;
} DAC_Map;


// And here are the register bit ranges
#define DAC_CR_EN1      BIT(0)
#define DAC_CR_BOFF1    BIT(1)
#define DAC_CR_TEN1     BIT(2)
#define DAC_CR_TSEL1    (BIT(3) | BIT(4) | BIT(5))
#define DAC_CR_WAVE1    (BIT(6) | BIT(7))
#define DAC_CR_MAMP1    (BIT(8) | BIT(9) | BIT(10) | BIT(11))
#define DAC_CR_DMAEN1   BIT(12)
#define DAC_CR_EN2      BIT(16)
#define DAC_CR_BOFF2    BIT(17)
#define DAC_CR_TEN2     BIT(18)
#define DAC_CR_TSEL2    (BIT(19) | BIT(20) | BIT(21))
#define DAC_CR_WAVE2    (BIT(22) | BIT(23))
#define DAC_CR_MAMP2    (BIT(24) | BIT(25) | BIT(26) | BIT(27))
#define DAC_CR_DMAEN2   BIT(28)

#define DAC_SWTRIGR_SWTRIG1     BIT(0)
#define DAC_SWTRIGR_SWTRIG2     BIT(1)

#define DAC_DHR12R1_DACC1DHR     0x00000FFF

#define DAC_DHR12L1_DACC1DHR     0x0000FFF0

#define DAC_DHR8R1_DACC1DHR      0x000000FF

#define DAC_DHR12R2_DACC2DHR     0x00000FFF

#define DAC_DHR12L2_DACC2DHR     0x0000FFF0

#define DAC_DHR8R2_DACC2DHR      0x000000FF

#define DAC_DHR12RD_DACC1DHR     0x00000FFF
#define DAC_DHR12RD_DACC2DHR     0x0FFF0000

#define DAC_DHR12LD_DACC1DHR     0x0000FFF0
#define DAC_DHR12LD_DACC2DHR     0xFFF00000

#define DAC_DHR8RD_DACC1DHR      0x000000FF
#define DAC_DHR8RD_DACC2DHR      0x0000FF00

#define DAC_DOR1                 0x00000FFF

#define DAC_DOR2                 0x00000FFF

void dac_init(void);
void dac_write(uint8 chan, uint16 val);

#ifdef __cplusplus
} // extern "C"
#endif


#endif

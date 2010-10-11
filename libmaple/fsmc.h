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
 * See ../notes/fsmc.txt for more info
 */

/**
 * @file fsmc.h
 */

#ifndef _FSMC_H_
#define _FSMC_H_

#ifdef __cplusplus
extern "C"{
#endif

// There are 4 FSMC chip-select devices; here are the SRAM-specific registers
// for each

#define FSMC1_BASE  0xA0000000
#define FSMC2_BASE  0xA0000008
#define FSMC3_BASE  0xA0000010
#define FSMC4_BASE  0xA0000018

typedef struct {
    volatile uint32 BCR;
    volatile uint32 BTR;
    //uint32 pad[62];      // double check this?
    //__io uint32 BWTR;
} FSMC_Bank;

// And here are the register bit ranges
#define FSMC_BCR_MBKEN      0b00000000000000000000000000000001
#define FSMC_BCR_MUXEN      0b00000000000000000000000000000010
#define FSMC_BCR_MTYP       0b00000000000000000000000000001100
#define FSMC_BCR_MWID       0b00000000000000000000000000110000
#define FSMC_BCR_FACCEN     0b00000000000000000000000001000000
#define FSMC_BCR_BURSTEN    0b00000000000000000000000100000000
#define FSMC_BCR_WAITPOL    0b00000000000000000000001000000000
#define FSMC_BCR_WRAPMOD    0b00000000000000000000010000000000
#define FSMC_BCR_WAITCFG    0b00000000000000000000100000000000
#define FSMC_BCR_WREN       0b00000000000000000001000000000000
#define FSMC_BCR_WAITEN     0b00000000000000000010000000000000
#define FSMC_BCR_EXTMOD     0b00000000000000000100000000000000
#define FSMC_BCR_CBURSTRW   0b00000000000010000000000000000000
#define FSMC_BTR_ADDSET     0b00000000000000000000000000001111
#define FSMC_BTR_ADDHOLD    0b00000000000000000000000011110000
#define FSMC_BTR_DATAST     0b00000000000000001111111100000000
#define FSMC_BTR_BUSTURN    0b00000000000011110000000000000000
#define FSMC_BTR_CLKDIV     0b00000000111100000000000000000000
#define FSMC_BTR_DATALAT    0b00001111000000000000000000000000
#define FSMC_BTR_ACCMOD     0b00110000000000000000000000000000
#define FSMC_BWTR_ADDSET    0b00000000000000000000000000001111
#define FSMC_BWTR_ADDHLD    0b00000000000000000000000011110000
#define FSMC_BWTR_DATAST    0b00000000000000001111111100000000
#define FSMC_BWTR_CLKDIV    0b00000000111100000000000000000000
#define FSMC_BWTR_DATLAT    0b00001111000000000000000000000000
#define FSMC_BWTR_ACCMOD    0b00110000000000000000000000000000

void fsmc_native_sram_init(void);

#ifdef __cplusplus
} // extern "C"
#endif


#endif

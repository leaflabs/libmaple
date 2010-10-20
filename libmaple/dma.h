/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Michael Hope.
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

/**
 *  @file dma.h
 *
 *  @brief Direct Memory Access peripheral support
 */

#ifndef _DMA_H_
#define _DMA_H_

#ifdef __cplusplus
extern "C"{
#endif

/** Base address of the DMA1 peripheral */
#define DMA1_BASE                0x40020000
/** DMA Interrupt Status Register */
#define DMA1_ISR                 (DMA1_BASE + 0x00)
/** DMA Interrput Flag Clear Register */
#define DMA1_IFCR                (DMA1_BASE + 0x04)
/** DMA Channel Configuration Register */
#define DMA1_CCR1                (DMA1_BASE + 0x08)
/** DMA Channel Number of Data Register */
#define DMA1_CNDTR1              (DMA1_BASE + 0x0C)
/** DMA Channel Peripheral Address Register */
#define DMA1_CPAR1               (DMA1_BASE + 0x10)
/** DMA Channel Memory Address Register */
#define DMA1_CMAR1               (DMA1_BASE + 0x14)
/** Spacing between channel registers */
#define DMA_CHANNEL_STRIDE       20

typedef enum dma_mode_flags {
    /** Auto-increment memory address */
    DMA_MINC_MODE = 4,
    /** Auto-increment peripheral address */
    DMA_PINC_MODE = 2,
    /** Circular mode */
    DMA_CIRC_MODE = 1,
} dma_mode_flags;

void dma_init(uint8 channel, volatile void *peripheral, bool from_peripheral, dma_mode_flags mode);
void dma_start(uint8 channel, volatile void *buffer, uint16 count);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

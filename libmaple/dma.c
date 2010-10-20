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
 *  @file dma.c
 *
 *  @brief Direct Memory Access peripheral support
 */

#include "libmaple.h"
#include "dma.h"
#include "rcc.h"

#define DMA_EN    BIT(0)

typedef struct dma_regs
{
    uint32 CCR;
    uint32 CNDTR;
    uint32 CPAR;
    uint32 CMAR;
} dma_regs;

/** Get the base address of the given channel, asserting and returning
 * NULL on illegal
 */
static dma_regs *dma_get_regs(uint8 channel) {
    if (channel >= 1 && channel <= 7) {
        return (dma_regs *)(DMA1_CCR1 + DMA_CHANNEL_STRIDE * (channel-1));
    }
    else {
        ASSERT(false);
        return NULL;
    }
}

/** Initialise a DMA channel.  Start the transfer using dma_start().
 *
 *  @param channel          the channel number (1..7)
 *  @param peripheral       address of the peripheral
 *  @param from_peripheral  true if transfer goes from the peripheral
 *                          to memory
 *  @param mode             OR of the dma_mode_flags
 */
void dma_init(uint8 channel, volatile void *peripheral, bool from_peripheral, enum dma_mode_flags mode) {
    volatile dma_regs *regs = dma_get_regs(channel);

    if (regs != NULL) {
        rcc_clk_enable(RCC_DMA1);

        /* Disable the channel.  PENDING: May not be needed */
        regs->CCR = 0;

        uint32 cr = 0
                | (0 << 12)   // Low priority
                | (0 << 10)   // Memory size = 8 bits
                | (1 <<  8)   // Peripheral size = 16 bits
                | (mode << 5) // Increment and circular modes
                | (0 << 0);   // Not enabled

        regs->CPAR = peripheral;

        if (!from_peripheral) {
            cr |= 1 << 4; // From memory
        }

        /* Stay disabled until started */
        regs->CCR = cr;
    }
}

void dma_start(uint8 channel, volatile void *buffer, uint16 count)
{
    volatile dma_regs *regs = dma_get_regs(channel);

    if (regs != NULL) {
        regs->CCR &= ~DMA_EN;
        regs->CMAR = (uint32)buffer;
        regs->CNDTR = count;

        regs->CCR |= DMA_EN;
    }
}

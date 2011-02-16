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
#include "nvic.h"

#define DMA_EN    BIT(0)

typedef struct dma_regs {
    uint32 CCR;
    uint32 CNDTR;
    uint32 CPAR;
    uint32 CMAR;
} dma_regs;

typedef struct DMAChannel {
    void (*handler)(void);
    uint32 irq_line;
} DMAChannel;

volatile static DMAChannel dma_channels[] = {
    { .handler = NULL, .irq_line = NVIC_DMA_CH1 },
    { .handler = NULL, .irq_line = NVIC_DMA_CH2 },
    { .handler = NULL, .irq_line = NVIC_DMA_CH3 },
    { .handler = NULL, .irq_line = NVIC_DMA_CH4 },
    { .handler = NULL, .irq_line = NVIC_DMA_CH5 },
    { .handler = NULL, .irq_line = NVIC_DMA_CH6 },
    { .handler = NULL, .irq_line = NVIC_DMA_CH7 }
};

/** Get the base address of the given channel, asserting and returning
 * NULL on illegal
 */
static dma_regs *dma_get_regs(uint8 channel) {
    if (channel >= 1 && channel <= 7) {
        return (dma_regs *)(DMA1_CCR1 + DMA_CHANNEL_STRIDE * (channel-1));
    } else {
        ASSERT(0);
        return NULL;
    }
}

/* Zero-based indexing */
static inline void dispatch_handler(uint8 channel_idx) {
    ASSERT(dma_channels[channel_idx].handler);
    if (dma_channels[channel_idx].handler) {
        (dma_channels[channel_idx].handler)();
    }
}

void DMAChannel1_IRQHandler(void) {
    dispatch_handler(0);
}

void DMAChannel2_IRQHandler(void) {
    dispatch_handler(1);
}

void DMAChannel3_IRQHandler(void) {
    dispatch_handler(2);
}

void DMAChannel4_IRQHandler(void) {
    dispatch_handler(3);
}

void DMAChannel5_IRQHandler(void) {
    dispatch_handler(4);
}

void DMAChannel6_IRQHandler(void) {
    dispatch_handler(5);
}

void DMAChannel7_IRQHandler(void) {
    dispatch_handler(6);
}

void dma_init(uint8 channel, volatile void *paddr,
              dma_transfer_size psize, dma_transfer_size msize,
              int mode) {
    volatile dma_regs *regs = dma_get_regs(channel);

    if (regs != NULL) {
        rcc_clk_enable(RCC_DMA1);

        regs->CCR = ((0 << 12)        /* Low priority */
                     | (msize << 10)
                     | (psize <<  8)
                     | (0 << 0)       /* Disabled (until started) */
                     | mode);

        regs->CPAR = (uint32)paddr;
    }
}

void dma_start(uint8 channel, volatile void *buffer, uint16 count) {
    volatile dma_regs *regs = dma_get_regs(channel);

    if (regs != NULL) {
        regs->CCR &= ~DMA_EN; /* CMAR may not be written with EN set */
        regs->CMAR = (uint32)buffer;
        regs->CNDTR = count;

        regs->CCR |= DMA_EN;
    }
}

void dma_attach_interrupt(uint8 channel, voidFuncPtr handler) {
    channel--;                  /* 1-based -> 0-based indexing */
    dma_channels[channel].handler = handler;
    nvic_irq_enable(dma_channels[channel].irq_line);
}

void dma_detach_interrupt(uint8 channel) {
    channel--;
    nvic_irq_disable(dma_channels[channel].irq_line);
    dma_channels[channel].handler = NULL;
}

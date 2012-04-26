/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Michael Hope.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/include/libmaple/dma.h
 *
 * @author Marti Bolivar <mbolivar@leaflabs.com>;
 *         Original implementation by Michael Hope
 *
 * @brief Direct Memory Access peripheral support
 */

#ifndef _LIBMAPLE_DMA_H_
#define _LIBMAPLE_DMA_H_

#ifdef __cplusplus
extern "C"{
#endif

/* <series/dma.h> provides:
 *
 * - Normal stuff: dma_reg_map and base pointers, register bit
 *   definitions, dma_dev pointer declarations, and any other
 *   convenience functions useful for that series.
 */
#include <series/dma.h>

#include <libmaple/libmaple_types.h>
#include <libmaple/nvic.h>
#include <libmaple/rcc.h>

/*
 * Devices
 */

/* Encapsulates state related to user interrupt handlers. You
 * shouldn't touch these directly; use dma_attach_interrupt() and
 * dma_detach_interupt() instead. */
typedef struct dma_handler_config {
    void (*handler)(void);     /* User handler */
    nvic_irq_num irq_line;     /* IRQ line for interrupt */
} dma_handler_config;

/** DMA device type */
typedef struct dma_dev {
    dma_reg_map               *regs;       /**< Register map */
    rcc_clk_id                 clk_id;     /**< Clock ID */
    struct dma_handler_config  handlers[]; /**< For internal use */
} dma_dev;

/*
 * Convenience functions
 */

void dma_init(dma_dev *dev);

/*
 * Hack: This is here so the series header can declare it and access
 * dma_dev->regs without knowing the structure of dma_dev. Don't use
 * it outside of a series header.
 */
static __always_inline dma_reg_map* _dma_dev_regs(dma_dev *dev) {
    return dev->regs;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

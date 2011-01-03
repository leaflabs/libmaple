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
 *
 *  TODO: add DMA2 support for high-density devices.
 */

#ifndef _DMA_H_
#define _DMA_H_

#include "libmaple_types.h"

#ifdef __cplusplus
extern "C"{
#endif

/** Base address of the DMA1 peripheral */
#define DMA1_BASE                0x40020000
/** DMA Interrupt Status Register */
#define DMA1_ISR                 (DMA1_BASE + 0x00)
/** DMA Interrupt Flag Clear Register */
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

/** Flags for DMA transfer configuration. */
typedef enum dma_mode_flags {
    DMA_MINC_MODE  = 1 << 7, /**< Auto-increment memory address */
    DMA_PINC_MODE  = 1 << 6, /**< Auto-increment peripheral address */
    DMA_CIRC_MODE  = 1 << 5, /**< Circular mode */
    DMA_FROM_MEM   = 1 << 4, /**< Read from memory to peripheral */
    DMA_TRNS_ERR   = 1 << 3, /**< Interrupt on transfer error */
    DMA_HALF_TRNS  = 1 << 2, /**< Interrupt on half-transfer */
    DMA_TRNS_CMPLT = 1 << 1  /**< Interrupt on transfer completion */
} dma_mode_flags;

/** Source and destination transfer sizes. */
typedef enum dma_transfer_size {
    DMA_SIZE_8BITS  = 0,
    DMA_SIZE_16BITS = 1,
    DMA_SIZE_32BITS = 2
} dma_transfer_size;

/**
 * Initialize a DMA channel.  If desired, attach an interrupt handler
 * using dma_attach_interrupt().  Start the transfer using
 * dma_start().
 *
 * @param channel          the channel number (1..7)
 * @param paddr            address of the peripheral
 * @param psize            peripheral size
 * @param msize            memory size
 * @param mode             OR of the dma_mode_flags
 * @see dma_mode_flags
 * @see dma_attach_interrupt()
 * @see dma_start() */
void dma_init(uint8 channel, volatile void *paddr,
              dma_transfer_size psize, dma_transfer_size msize,
              int mode);

/**
 * Begin a DMA transfer initialized with dma_init().
 *
 * @param channel Channel transfer to start.
 * @param buffer  Buffer to write to (unless DMA_FROM_MEM was set in
 *                mode argument to dma_init(), in which case, buffer
 *                to read from).  This must be aligned with msize
 *                argument to dma_init().
 * @param count   Number of elements to transfer.
 * @see dma_init() */
void dma_start(uint8 channel, volatile void *buffer, uint16 count);

/**
 * Attach an interrupt handler for the given DMA channel.
 * @param channel DMA channel (1..7)
 * @param handler Interrupt handler to attach
 * @see voidFuncPtr */
void dma_attach_interrupt(uint8 channel, voidFuncPtr handler);

/**
 * Detach any handler associated with the given DMA channel.
 * @param channel Channel whose interrupt handler to detach. */
void dma_detach_interrupt(uint8 channel);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

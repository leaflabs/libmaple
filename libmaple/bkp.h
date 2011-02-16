/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs, LLC.
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
 * @file bkp.h
 * @brief Backup register support.
 */

#ifndef _BKP_H_
#define _BKP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BKP_BASE        0x40006C00
#define BKP_RTCCR       (BKP_BASE + 0x2C)
#define BKP_CR          (BKP_BASE + 0x30)
#define BKP_CSR         (BKP_BASE + 0x34)

/**
 * Initialize backup interface. This function enables the power and
 * backup interface clocks.  It does not enable write access to the
 * backup registers.
 */
void bkp_init(void);

/** Disable power and backup interface clocks. */
void bkp_disable(void);

/**
 * Enable write access to the backup registers.  Backup interface must
 * be initialized for subsequent register writes to work.
 * @see bkp_init()
 */
void bkp_enable_writes(void);

/**
 * Disable write access to the backup registers.  Does not disable
 * backup interface clocks.
 */
void bkp_disable_writes(void);

/**
 * Read a value from given backup data register.
 * @param reg Data register to read, from 1 to NR_BKP_REGS (10 on Maple).
 */
uint16 bkp_read(uint8 reg);

/**
 * Write a value to given data register.  Backup interface must have
 * been previously initialized, and write access to backup registers
 * must be enabled.
 * @param reg Data register to write, from 1 to NR_BKP_REGS (10 on Maple).
 * @param val Value to write into the register.
 */
void bkp_write(uint8 reg, uint16 val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

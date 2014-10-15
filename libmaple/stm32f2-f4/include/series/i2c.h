/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung (from <libmaple/i2c.h>).
 * Copyright (c) 2012 LeafLabs, LLC.
 * Copyright (c) 2014 Google, Inc.
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

#ifndef _LIBMAPLE_STM32F2_I2C_H_
#define _LIBMAPLE_STM32F2_I2C_H_

#include <libmaple/i2c_common.h>
#include <libmaple/stm32.h>

/*
 * Register maps
 */

/** I2C register map type */
typedef struct i2c_reg_map {
    __io uint32 CR1;            /**< Control register 1 */
    __io uint32 CR2;            /**< Control register 2 */
    __io uint32 OAR1;           /**< Own address register 1 */
    __io uint32 OAR2;           /**< Own address register 2 */
    __io uint32 DR;             /**< Data register */
    __io uint32 SR1;            /**< Status register 1 */
    __io uint32 SR2;            /**< Status register 2 */
    __io uint32 CCR;            /**< Clock control register */
    __io uint32 TRISE;          /**< TRISE (rise time) register */
    __io uint32 FLTR;           /**< Noise filter register */
} i2c_reg_map;

/** I2C1 register map base pointer */
#define I2C1_BASE               ((struct i2c_reg_map*)0x40005400)
/** I2C2 register map base pointer */
#define I2C2_BASE               ((struct i2c_reg_map*)0x40005800)
/** I2C3 register map base pointer */
#define I2C3_BASE               ((struct i2c_reg_map*)0x40005C00)

/*
 * Devices
 */

extern i2c_dev* const I2C1;
extern i2c_dev* const I2C2;
extern i2c_dev* const I2C3;

/*
 * For internal use
 */

static inline uint32 _i2c_bus_clk(i2c_dev *dev) {
    /* All the I2C peripherals are on APB1 */
    return STM32_PCLK1 / (1000 * 1000);
}

#undef _I2C_HAVE_IRQ_FIXUP
#undef _I2C_HAVE_DEPRECATED_I2C_REMAP

#endif  /* _LIBMAPLE_STM32F1_I2C_H_ */

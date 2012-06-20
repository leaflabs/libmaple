/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
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

#include "i2c_private.h"
#include <libmaple/i2c.h>

/*
 * Devices
 */

static i2c_dev i2c1 = I2C_DEV(1, &gpiob, 7, 6);
static i2c_dev i2c2 = I2C_DEV(2, &gpiob, 11, 10);

/** STM32F1 I2C device 1 */
i2c_dev* const I2C1 = &i2c1;
/** STM32F1 I2C device 2 */
i2c_dev* const I2C2 = &i2c2;

/*
 * IRQ handlers
 */

void __irq_i2c1_ev(void) {
   _i2c_irq_handler(I2C1);
}

void __irq_i2c2_ev(void) {
   _i2c_irq_handler(I2C2);
}

void __irq_i2c1_er(void) {
    _i2c_irq_error_handler(I2C1);
}

void __irq_i2c2_er(void) {
    _i2c_irq_error_handler(I2C2);
}

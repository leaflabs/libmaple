/******************************************************************************
 * The MIT License
 *
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

#include "i2c_private.h"
#include <libmaple/i2c.h>

/*
 * Devices
 */

static i2c_dev i2c1 = I2C_DEV_NEW(1, &gpiob, 7, &gpiob, 6);
static i2c_dev i2c2 = I2C_DEV_NEW(1, &gpioh, 5, &gpioh, 4);
static i2c_dev i2c3 = I2C_DEV_NEW(1, &gpioh, 8, &gpioh, 7);

/** I2C1 device */
i2c_dev* const I2C1 = &i2c1;
/** I2C2 device */
i2c_dev* const I2C2 = &i2c2;
/** I2C3 device */
i2c_dev* const I2C3 = &i2c3;

/*
 * libmaple routines
 */

#define I2C_MODEF_FLAGS (GPIO_MODEF_TYPE_OD | GPIO_MODEF_SPEED_HIGH | \
                         GPIO_MODEF_PUPD_PU)

void i2c_config_gpios(const i2c_dev *dev) {
    /* Untested... */
    gpio_set_modef(sda_port(dev), dev->sda_pin, GPIO_MODE_AF, I2C_MODEF_FLAGS);
    gpio_set_modef(scl_port(dev), dev->scl_pin, GPIO_MODE_AF, I2C_MODEF_FLAGS);
    gpio_set_af(sda_port(dev), dev->sda_pin, GPIO_AF_I2C);
    gpio_set_af(scl_port(dev), dev->scl_pin, GPIO_AF_I2C);
}

void i2c_master_release_bus(const i2c_dev *dev) {
    /* Untested... */
    unsigned flags = (GPIO_MODEF_TYPE_OD | GPIO_MODEF_SPEED_HIGH |
                      GPIO_MODEF_PUPD_PU);
    gpio_write_bit(scl_port(dev), dev->scl_pin, 1);
    gpio_write_bit(sda_port(dev), dev->sda_pin, 1);
    gpio_set_modef(scl_port(dev), dev->scl_pin, GPIO_MODE_OUTPUT,
                   I2C_MODEF_FLAGS);
    gpio_set_modef(sda_port(dev), dev->sda_pin, GPIO_MODE_OUTPUT,
                   I2C_MODEF_FLAGS);
}

/*
 * IRQ Handlers
 */

void __irq_i2c1_ev(void) {
   _i2c_irq_handler(I2C1);
}

void __irq_i2c2_ev(void) {
   _i2c_irq_handler(I2C2);
}

void __irq_i2c3_ev(void) {
   _i2c_irq_handler(I2C3);
}

void __irq_i2c1_er(void) {
    _i2c_irq_error_handler(I2C1);
}

void __irq_i2c2_er(void) {
    _i2c_irq_error_handler(I2C2);
}

void __irq_i2c3_er(void) {
    _i2c_irq_error_handler(I2C3);
}

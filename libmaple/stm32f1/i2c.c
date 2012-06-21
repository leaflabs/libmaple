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
 * Routines
 */

void i2c_config_gpios(const i2c_dev *dev) {
    gpio_set_mode(dev->gpio_port, dev->sda_pin, GPIO_AF_OUTPUT_OD);
    gpio_set_mode(dev->gpio_port, dev->scl_pin, GPIO_AF_OUTPUT_OD);
}

void i2c_master_release_bus(const i2c_dev *dev) {
    gpio_write_bit(dev->gpio_port, dev->scl_pin, 1);
    gpio_write_bit(dev->gpio_port, dev->sda_pin, 1);
    gpio_set_mode(dev->gpio_port, dev->scl_pin, GPIO_OUTPUT_OD);
    gpio_set_mode(dev->gpio_port, dev->sda_pin, GPIO_OUTPUT_OD);
}

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

/*
 * Internal APIs
 */

void _i2c_irq_priority_fixup(i2c_dev *dev) {
    /*
     * Important STM32 Errata:
     *
     * See STM32F10xx8 and STM32F10xxB Errata sheet (Doc ID 14574 Rev 8),
     * Section 2.11.1, 2.11.2.
     *
     * 2.11.1:
     * When the EV7, EV7_1, EV6_1, EV6_3, EV2, EV8, and EV3 events are not
     * managed before the current byte is being transferred, problems may be
     * encountered such as receiving an extra byte, reading the same data twice
     * or missing data.
     *
     * 2.11.2:
     * In Master Receiver mode, when closing the communication using
     * method 2, the content of the last read data can be corrupted.
     *
     * If the user software is not able to read the data N-1 before the STOP
     * condition is generated on the bus, the content of the shift register
     * (data N) will be corrupted. (data N is shifted 1-bit to the left).
     *
     * ----------------------------------------------------------------------
     *
     * In order to ensure that events are not missed, the i2c interrupt must
     * not be preempted. We set the i2c interrupt priority to be the highest
     * interrupt in the system (priority level 0). All other interrupts have
     * been initialized to priority level 16. See nvic_init().
     */
    nvic_irq_set_priority(dev->ev_nvic_line, 0);
    nvic_irq_set_priority(dev->er_nvic_line, 0);
}

void _i2c_set_ccr_trise(i2c_dev *dev, uint32 flags) {
#define I2C_CLK                (STM32_PCLK1/1000000)
    uint32 ccr   = 0;
    uint32 trise = 0;

    /* I2C1 and I2C2 are fed from APB1, clocked at 36MHz */
    i2c_set_input_clk(dev, I2C_CLK);

    if (flags & I2C_FAST_MODE) {
        ccr |= I2C_CCR_FS;

        if (flags & I2C_DUTY_16_9) {
            /* Tlow/Thigh = 16/9 */
            ccr |= I2C_CCR_DUTY;
            ccr |= STM32_PCLK1/(400000 * 25);
        } else {
            /* Tlow/Thigh = 2 */
            ccr |= STM32_PCLK1/(400000 * 3);
        }

        trise = (300 * (I2C_CLK)/1000) + 1;
    } else {
        /* Tlow/Thigh = 1 */
        ccr = STM32_PCLK1/(100000 * 2);
        trise = I2C_CLK + 1;
    }

    /* Set minimum required value if CCR < 1*/
    if ((ccr & I2C_CCR_CCR) == 0) {
        ccr |= 0x1;
    }

    i2c_set_clk_control(dev, ccr);
    i2c_set_trise(dev, trise);
}

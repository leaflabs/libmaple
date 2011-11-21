/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file libmaple/stm32f2/gpio.h
 * @brief STM32F2 General Purpose I/O (GPIO) header.
 */

#ifndef _LIBMAPLE_STM32F2_GPIO_H_
#define _LIBMAPLE_STM32F2_GPIO_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>

/*
 * GPIO register maps and devices
 */

/** GPIO register map type */
typedef struct gpio_reg_map {
    __io uint32 MODER;          /**< Mode register */
    __io uint32 OTYPER;         /**< Output type register */
    __io uint32 OSPEEDR;        /**< Output speed register */
    __io uint32 PUPDR;          /**< Pull-up/pull-down register */
    __io uint32 IDR;            /**< Input data register */
    __io uint32 ODR;            /**< Output data register */
    __io uint32 BSRR;           /**< Bit set/reset register */
    __io uint32 LCKR;           /**< Configuration lock register */
    __io uint32 AFRL;           /**< Alternate function low register */
    __io uint32 AFRH;           /**< Alternate function high register */
} gpio_reg_map;

/** GPIO port A register map base pointer */
#define GPIOA_BASE                      ((struct gpio_reg_map*)0x40020000)
/** GPIO port B register map base pointer */
#define GPIOB_BASE                      ((struct gpio_reg_map*)0x40020400)
/** GPIO port C register map base pointer */
#define GPIOC_BASE                      ((struct gpio_reg_map*)0x40020800)
/** GPIO port D register map base pointer */
#define GPIOD_BASE                      ((struct gpio_reg_map*)0x40020C00)
/** GPIO port E register map base pointer */
#define GPIOE_BASE                      ((struct gpio_reg_map*)0x40021000)
/** GPIO port F register map base pointer */
#define GPIOF_BASE                      ((struct gpio_reg_map*)0x40021400)
/** GPIO port G register map base pointer */
#define GPIOG_BASE                      ((struct gpio_reg_map*)0x40021800)
/** GPIO port H register map base pointer */
#define GPIOH_BASE                      ((struct gpio_reg_map*)0x40021C00)
/** GPIO port I register map base pointer */
#define GPIOI_BASE                      ((struct gpio_reg_map*)0x40022000)

/** GPIO device type */
typedef struct gpio_dev {
    gpio_reg_map *regs;
    rcc_clk_id clk_id;
} gpio_dev;

extern gpio_dev* const GPIOA;
extern gpio_dev gpioa;
extern gpio_dev* const GPIOB;
extern gpio_dev gpiob;
extern gpio_dev* const GPIOC;
extern gpio_dev gpioc;
extern gpio_dev* const GPIOD;
extern gpio_dev gpiod;
extern gpio_dev* const GPIOE;
extern gpio_dev gpioe;
extern gpio_dev* const GPIOF;
extern gpio_dev gpiof;
extern gpio_dev* const GPIOG;
extern gpio_dev gpiog;
extern gpio_dev* const GPIOH;
extern gpio_dev gpioh;
extern gpio_dev* const GPIOI;
extern gpio_dev gpioi;

/*
 * Register bit definitions
 *
 * Currently, we only provide masks to be used for shifting, rather
 * than repeating the same values 16 times.
 */

/* Mode register */

#define GPIO_MODER_INPUT                0x0
#define GPIO_MODER_OUTPUT               0x1
#define GPIO_MODER_AF                   0x2
#define GPIO_MODER_ANALOG               0x3

/* Output type register */

#define GPIO_OTYPER_PP                  0x0
#define GPIO_OTYPER_OD                  0x1

/* Output speed register */

#define GPIO_OSPEEDR_LOW                0x0
#define GPIO_OSPEEDR_MED                0x1
#define GPIO_OSPEEDR_FAST               0x2
#define GPIO_OSPEEDR_HIGH               0x3

/* Pull-up/pull-down register */

#define GPIO_PUPDR_NOPUPD               0x0
#define GPIO_PUPDR_PU                   0x1
#define GPIO_PUPDR_PD                   0x2

/*
 * GPIO routines
 */

/**
 * @brief GPIO pin modes
 */
typedef enum gpio_pin_mode {
    GPIO_MODE_INPUT = GPIO_MODER_INPUT, /**< Input mode */
    GPIO_MODE_OUTPUT = GPIO_MODER_OUTPUT, /**< Output mode */
    GPIO_MODE_AF = GPIO_MODER_AF, /**< Alternate function mode */
    GPIO_MODE_ANALOG = GPIO_MODER_ANALOG, /**< Analog mode */
} gpio_pin_mode;

/**
 * @brief Additional flags to be used when setting a pin's mode.
 *
 * Beyond the basic modes (input, general purpose output, alternate
 * function, and analog), there are three parameters that can affect a
 * pin's mode:
 *
 * 1. Output type: push/pull or open-drain. This only has an effect
 *    for output modes. Choices are: GPIO_MODEF_TYPE_PP (the default)
 *    and GPIO_MODEF_TYPE_OD.
 *
 * 2. Output speed: specifies the frequency at which a pin changes
 *    state. This only has an effect for output modes. Choices are:
 *    GPIO_MODEF_SPEED_LOW (default), GPIO_MODEF_SPEED_MED,
 *    GPIO_MODEF_SPEED_FAST, and GPIO_MODEF_SPEED_HIGH.
 *
 * 3. Push/pull setting: All GPIO pins have weak pull-up and pull-down
 *    resistors that can be enabled when the pin's mode is
 *    set. Choices are: GPIO_MODEF_PUPD_NONE (default),
 *    GPIO_MODEF_PUPD_PU, and GPIO_MODEF_PUPD_PD.
 */
typedef enum gpio_mode_flags {
    /* Output type in bit 0 */
    GPIO_MODEF_TYPE_PP = GPIO_OTYPER_PP, /**< Output push/pull (default).
                                            Applies only when the mode
                                            specifies output. */
    GPIO_MODEF_TYPE_OD = GPIO_OTYPER_OD, /**< Output open drain.
                                            Applies only when the mode
                                            specifies output. */

    /* Speed in bits 2:1 */
    GPIO_MODEF_SPEED_LOW = GPIO_OSPEEDR_LOW << 1, /**< Low speed (default):
                                                     2 MHz. */
    GPIO_MODEF_SPEED_MED = GPIO_OSPEEDR_MED << 1, /**< Medium speed: 25 MHz. */
    GPIO_MODEF_SPEED_FAST = GPIO_OSPEEDR_FAST << 1, /**< Fast speed: 50 MHz. */
    GPIO_MODEF_SPEED_HIGH = GPIO_OSPEEDR_HIGH << 1, /**< High speed:
                                                       100 MHz on 30 pF,
                                                       80 MHz on 15 pF. */

    /* Pull-up/pull-down in bits 4:3 */
    GPIO_MODEF_PUPD_NONE = GPIO_PUPDR_NOPUPD << 3, /**< No pull-up/pull-down
                                                      (default). */
    GPIO_MODEF_PUPD_PU = GPIO_PUPDR_PU << 3, /**< Pull-up */
    GPIO_MODEF_PUPD_PD = GPIO_PUPDR_PD << 3, /**< Pull-down */
} gpio_mode_flags;

void gpio_set_modef(gpio_dev *dev,
                    uint8 pin,
                    gpio_pin_mode mode,
                    unsigned flags);

/**
 * @brief Set the mode of a GPIO pin.
 *
 * Calling this function is equivalent to calling gpio_set_modef(dev,
 * pin, mode, GPIO_MODE_SPEED_HIGH). Note that this overrides the
 * default speed.
 *
 * @param dev GPIO device.
 * @param pin Pin on the device whose mode to set, 0--15.
 * @param mode Mode to set the pin to.
 */
static inline void gpio_set_mode(gpio_dev *dev,
                                 uint8 pin,
                                 gpio_pin_mode mode) {
    gpio_set_modef(dev, pin, mode, GPIO_MODEF_SPEED_HIGH);
}

#ifdef __cplusplus
}
#endif

#endif

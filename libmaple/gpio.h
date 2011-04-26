/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 *  @file gpio.h
 *
 *  @brief General purpose I/0 (GPIO) and Alternate Function I/O
 *         (AFIO) prototypes, defines, and inlined access functions.
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include "libmaple.h"
#include "rcc.h"

#ifdef __cplusplus
extern "C"{
#endif

/*
 * GPIO register maps and devices
 */

/** GPIO register map type */
typedef struct gpio_reg_map {
    __io uint32 CRL;      /**< Port configuration register low */
    __io uint32 CRH;      /**< Port configuration register high */
    __io uint32 IDR;      /**< Port input data register */
    __io uint32 ODR;      /**< Port output data register */
    __io uint32 BSRR;     /**< Port bit set/reset register */
    __io uint32 BRR;      /**< Port bit reset register */
    __io uint32 LCKR;     /**< Port configuration lock register */
} gpio_reg_map;

/**
 * External interrupt line port selector.  Used to determine which
 * GPIO port to map an external interrupt line onto. */
/* (See AFIO sections, below) */
typedef enum {
    AFIO_EXTI_PA,               /**< Use PAx pin. */
    AFIO_EXTI_PB,               /**< Use PBx pin. */
    AFIO_EXTI_PC,               /**< Use PCx pin. */
    AFIO_EXTI_PD,               /**< Use PDx pin. */
#ifdef STM32_HIGH_DENSITY
    AFIO_EXTI_PE,               /**< Use PEx pin. */
    AFIO_EXTI_PF,               /**< Use PFx pin. */
    AFIO_EXTI_PG,               /**< Use PGx pin. */
#endif
} afio_exti_port;

/** GPIO device type */
typedef struct gpio_dev {
    gpio_reg_map *regs;       /**< Register map */
    rcc_clk_id clk_id;        /**< RCC clock information */
    afio_exti_port exti_port; /**< AFIO external interrupt port value */
} gpio_dev;

extern gpio_dev gpioa;
extern gpio_dev* const GPIOA;
extern gpio_dev gpiob;
extern gpio_dev* const GPIOB;
extern gpio_dev gpioc;
extern gpio_dev* const GPIOC;
extern gpio_dev gpiod;
extern gpio_dev* const GPIOD;
#ifdef STM32_HIGH_DENSITY
extern gpio_dev gpioe;
extern gpio_dev* const GPIOE;
extern gpio_dev gpiof;
extern gpio_dev* const GPIOF;
extern gpio_dev gpiog;
extern gpio_dev* const GPIOG;
#endif

/** GPIO port A register map base pointer */
#define GPIOA_BASE ((gpio_reg_map*)0x40010800)
/** GPIO port B register map base pointer */
#define GPIOB_BASE ((gpio_reg_map*)0x40010C00)
/** GPIO port C register map base pointer */
#define GPIOC_BASE ((gpio_reg_map*)0x40011000)
/** GPIO port D register map base pointer */
#define GPIOD_BASE ((gpio_reg_map*)0x40011400)
#ifdef STM32_HIGH_DENSITY
/** GPIO port E register map base pointer */
#define GPIOE_BASE ((gpio_reg_map*)0x40011800)
/** GPIO port F register map base pointer */
#define GPIOF_BASE ((gpio_reg_map*)0x40011C00)
/** GPIO port G register map base pointer */
#define GPIOG_BASE ((gpio_reg_map*)0x40012000)
#endif

/*
 * GPIO register bit definitions
 */

/* Control registers, low and high */
#define GPIO_CR_CNF_INPUT_ANALOG        (0x0 << 2)
#define GPIO_CR_CNF_INPUT_FLOATING      (0x1 << 2)
#define GPIO_CR_CNF_INPUT_PU_PD         (0x2 << 2)
#define GPIO_CR_CNF_OUTPUT_PP           (0x0 << 2)
#define GPIO_CR_CNF_OUTPUT_OD           (0x1 << 2)
#define GPIO_CR_CNF_AF_OUTPUT_PP        (0x2 << 2)
#define GPIO_CR_CNF_AF_OUTPUT_OD        (0x3 << 2)
#define GPIO_CR_MODE_INPUT              0x0
#define GPIO_CR_MODE_OUTPUT_10MHZ       0x1
#define GPIO_CR_MODE_OUTPUT_2MHZ        0x2
#define GPIO_CR_MODE_OUTPUT_50MHZ       0x3

/** GPIO Pin modes.  These only allow for 50MHZ max output speeds; if
 * you want slower, use direct register access. */
typedef enum gpio_pin_mode {
    GPIO_OUTPUT_PP = (GPIO_CR_CNF_OUTPUT_PP |
                      GPIO_CR_MODE_OUTPUT_50MHZ), /**< Output push-pull. */
    GPIO_OUTPUT_OD = (GPIO_CR_CNF_OUTPUT_OD |
                      GPIO_CR_MODE_OUTPUT_50MHZ), /**< Output open-drain. */
    GPIO_AF_OUTPUT_PP = (GPIO_CR_CNF_AF_OUTPUT_PP |
                         GPIO_CR_MODE_OUTPUT_50MHZ), /**< Alternate function
                                                        output push-pull. */
    GPIO_AF_OUTPUT_OD = (GPIO_CR_CNF_AF_OUTPUT_OD |
                         GPIO_CR_MODE_OUTPUT_50MHZ), /**< Alternate function
                                                        output open drain. */
    GPIO_INPUT_ANALOG = (GPIO_CR_CNF_INPUT_ANALOG |
                         GPIO_CR_MODE_INPUT), /**< Analog input. */
    GPIO_INPUT_FLOATING = (GPIO_CR_CNF_INPUT_FLOATING |
                           GPIO_CR_MODE_INPUT), /**< Input floating. */
    GPIO_INPUT_PD = (GPIO_CR_CNF_INPUT_PU_PD |
                     GPIO_CR_MODE_INPUT), /**< Input pull-down. */
    GPIO_INPUT_PU /**< Input pull-up. */
    /* GPIO_INPUT_PU treated as a special case, for ODR twiddling */
} gpio_pin_mode;

/*
 * GPIO Convenience routines
 */

void gpio_init(gpio_dev *dev);
void gpio_init_all(void);
void gpio_set_mode(gpio_dev *dev, uint8 pin, gpio_pin_mode mode);

/**
 * @brief Get a GPIO port's corresponding afio_exti_port.
 * @param dev GPIO device whose afio_exti_port to return.
 */
static inline afio_exti_port gpio_exti_port(gpio_dev *dev) {
    return dev->exti_port;
}

/**
 * Set or reset a GPIO pin.
 *
 * Pin must have previously been configured to output mode.
 *
 * @param dev GPIO device whose pin to set.
 * @param pin Pin on to set or reset
 * @param val If true, set the pin.  If false, reset the pin.
 */
static inline void gpio_write_bit(gpio_dev *dev, uint8 pin, uint8 val) {
    if (val) {
        dev->regs->BSRR = BIT(pin);
    } else {
        dev->regs->BRR = BIT(pin);
    }
}

/**
 * Determine whether or not a GPIO pin is set.
 *
 * Pin must have previously been configured to input mode.
 *
 * @param dev GPIO device whose pin to test.
 * @param pin Pin on dev to test.
 * @return True if the pin is set, false otherwise.
 */
static inline uint32 gpio_read_bit(gpio_dev *dev, uint8 pin) {
    return dev->regs->IDR & BIT(pin);
}

/**
 * Toggle a pin configured as output push-pull.
 * @param dev GPIO device.
 * @param pin Pin on dev to toggle.
 */
static inline void gpio_toggle_bit(gpio_dev *dev, uint8 pin) {
    dev->regs->ODR = dev->regs->ODR ^ BIT(pin);
}

/*
 * AFIO register map
 */

/** AFIO register map */
typedef struct afio_reg_map {
    __io uint32 EVCR;        /**< Event control register.  */
    __io uint32 MAPR;        /**< AF remap and debug I/O configuration
                                register. */
    __io uint32 EXTICR1;     /**< External interrupt configuration
                                register 1. */
    __io uint32 EXTICR2;     /**< External interrupt configuration
                                register 2. */
    __io uint32 EXTICR3;     /**< External interrupt configuration
                                register 3. */
    __io uint32 EXTICR4;     /**< External interrupt configuration
                                register 4. */
    __io uint32 MAPR2;       /**< AF remap and debug I/O configuration
                                register 2. */
} afio_reg_map;

/** AFIO register map base pointer. */
#define AFIO_BASE ((afio_reg_map *)0x40010000)

/*
 * AFIO register bit definitions
 */

/* Event control register */
#define AFIO_EVCR_EVOE                  (0x1 << 7)
#define AFIO_EVCR_PORT_PA               (0x0 << 4)
#define AFIO_EVCR_PORT_PB               (0x1 << 4)
#define AFIO_EVCR_PORT_PC               (0x2 << 4)
#define AFIO_EVCR_PORT_PD               (0x3 << 4)
#define AFIO_EVCR_PORT_PE               (0x4 << 4)
#define AFIO_EVCR_PIN_0                 0x0
#define AFIO_EVCR_PIN_1                 0x1
#define AFIO_EVCR_PIN_2                 0x2
#define AFIO_EVCR_PIN_3                 0x3
#define AFIO_EVCR_PIN_4                 0x4
#define AFIO_EVCR_PIN_5                 0x5
#define AFIO_EVCR_PIN_6                 0x6
#define AFIO_EVCR_PIN_7                 0x7
#define AFIO_EVCR_PIN_8                 0x8
#define AFIO_EVCR_PIN_9                 0x9
#define AFIO_EVCR_PIN_10                0xA
#define AFIO_EVCR_PIN_11                0xB
#define AFIO_EVCR_PIN_12                0xC
#define AFIO_EVCR_PIN_13                0xD
#define AFIO_EVCR_PIN_14                0xE
#define AFIO_EVCR_PIN_15                0xF

/* AF remap and debug I/O configuration register */
#define AFIO_MAPR_SWJ_CFG                      (0x7 << 24)
#define AFIO_MAPR_SWJ_CFG_FULL_SWJ             (0x0 << 24)
#define AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_NJRST    (0x1 << 24)
#define AFIO_MAPR_SWJ_CFG_NO_JTAG_SW           (0x2 << 24)
#define AFIO_MAPR_SWJ_CFG_NO_JTAG_NO_SW        (0x4 << 24)
#define AFIO_MAPR_ADC2_ETRGREG_REMAP           BIT(20)
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP           BIT(19)
#define AFIO_MAPR_ADC1_ETRGREG_REMAP           BIT(18)
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP           BIT(17)
#define AFIO_MAPR_TIM5CH4_IREMAP               BIT(16)
#define AFIO_MAPR_PD01_REMAP                   BIT(15)
#define AFIO_MAPR_CAN_REMAP                    (0x3 << 13)
#define AFIO_MAPR_TIM4_REMAP                   BIT(12)
#define AFIO_MAPR_TIM3_REMAP                   (0x3 << 10)
#define AFIO_MAPR_TIM2_REMAP                   (0x3 << 8)
#define AFIO_MAPR_TIM1_REMAP                   (0x3 << 6)
#define AFIO_MAPR_USART3_REMAP                 (0x3 << 4)
#define AFIO_MAPR_USART2_REMAP                 BIT(3)
#define AFIO_MAPR_USART1_REMAP                 BIT(2)
#define AFIO_MAPR_I2C1_REMAP                   BIT(1)
#define AFIO_MAPR_SPI1_REMAP                   BIT(0)

/* External interrupt configuration registers */

/**
 * External interrupt line numbers.
 */
typedef enum {
    AFIO_EXTI_0,                /**< External interrupt line 0. */
    AFIO_EXTI_1,                /**< External interrupt line 1. */
    AFIO_EXTI_2,                /**< External interrupt line 2. */
    AFIO_EXTI_3,                /**< External interrupt line 3. */
    AFIO_EXTI_4,                /**< External interrupt line 4. */
    AFIO_EXTI_5,                /**< External interrupt line 5. */
    AFIO_EXTI_6,                /**< External interrupt line 6. */
    AFIO_EXTI_7,                /**< External interrupt line 7. */
    AFIO_EXTI_8,                /**< External interrupt line 8. */
    AFIO_EXTI_9,                /**< External interrupt line 9. */
    AFIO_EXTI_10,               /**< External interrupt line 10. */
    AFIO_EXTI_11,               /**< External interrupt line 11. */
    AFIO_EXTI_12,               /**< External interrupt line 12. */
    AFIO_EXTI_13,               /**< External interrupt line 13. */
    AFIO_EXTI_14,               /**< External interrupt line 14. */
    AFIO_EXTI_15,               /**< External interrupt line 15. */
} afio_exti_num;

/* AF remap and debug I/O configuration register 2 */
#define AFIO_MAPR2_FSMC_NADV            BIT(10)
#define AFIO_MAPR2_TIM14_REMAP          BIT(9)
#define AFIO_MAPR2_TIM13_REMAP          BIT(8)
#define AFIO_MAPR2_TIM11_REMAP          BIT(7)
#define AFIO_MAPR2_TIM10_REMAP          BIT(6)
#define AFIO_MAPR2_TIM9_REMAP           BIT(5)

/*
 * AFIO convenience routines
 */

void afio_init(void);
void afio_exti_select(afio_exti_num exti, afio_exti_port gpio_port);

/**
 * @brief Debug port configuration
 *
 * Used to configure the behavior of JTAG and Serial Wire (SW) debug
 * ports and their associated GPIO pins.
 */
typedef enum afio_debug_cfg {
    AFIO_DEBUG_FULL_SWJ = AFIO_MAPR_SWJ_CFG_FULL_SWJ, /**<
                                   Full Serial Wire and JTAG debug */
    AFIO_DEBUG_FULL_SWJ_NO_NJRST = AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_NJRST, /**<
                                   Full Serial Wire and JTAG, but no NJTRST. */
    AFIO_DEBUG_SW_ONLY = AFIO_MAPR_SWJ_CFG_NO_JTAG_SW, /**<
                                   Serial Wire debug only (JTAG-DP disabled,
                                   SW-DP enabled) */
    AFIO_DEBUG_NONE = AFIO_MAPR_SWJ_CFG_NO_JTAG_NO_SW /**<
                                   No debug; all JTAG and SW pins are free
                                   for use as GPIOs. */
} afio_debug_cfg;

/**
 * @brief Enable or disable the JTAG and SW debug ports.
 * @param config Desired debug port configuration
 * @see afio_debug_cfg
 */
static inline void afio_cfg_debug_ports(afio_debug_cfg config) {
    __io uint32 *mapr = &AFIO_BASE->MAPR;
    *mapr = (*mapr & ~AFIO_MAPR_SWJ_CFG) | config;
}

#ifdef __cplusplus
}
#endif

#endif


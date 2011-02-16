/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 *  @file libmaple.h
 *
 *  @brief general include file for libmaple
 */

#ifndef _LIBMAPLE_H_
#define _LIBMAPLE_H_

#include "libmaple_types.h"

/* General configuration */
#define DEBUG_NONE      0
#define DEBUG_FAULT     1
#define DEBUG_ALL       2

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DEBUG_ALL
#endif

/* MCU-specific configuration */
#if defined(MCU_STM32F103RB)
    /* e.g., LeafLabs Maple */

    /* Number of GPIO ports (GPIOA, GPIOB, etc.) */
    #define NR_GPIO_PORTS             4

    /* Total number of GPIO pins */
    #define NR_GPIO_PINS             39

    /* Number of 16-bit backup registers */
    #define NR_BKP_REGS              10

    /* Number of timer devices ports, definitely used */
    #define NR_TIMERS                 4

    /* Number of USART ports */
    #define NR_USART                  3

    /* Has an FSMC bus? */
    #define NR_FSMC                   0

    /* Has an FSMC bus? */
    #define NR_DAC_PINS               0

    /* USB Identifier numbers */
    /* Descriptor strings must be modified by hand in
       usb/descriptors.c for now */
    #define VCOM_ID_VENDOR    0x1EAF
    #define VCOM_ID_PRODUCT   0x0004
    #define USB_DISC_BANK     GPIOC_BASE
    #define USB_DISC_PIN      12
    #define USB_CONFIG_MAX_POWER      (100 >> 1)
    #define RESET_DELAY               (100)

    /* Where to put usercode (based on space reserved for bootloader) */
    #define USER_ADDR_ROM 0x08005000
    #define USER_ADDR_RAM 0x20000C00
    #define STACK_TOP     0x20000800

    /* Debug port settings (from ASSERT) */
    #define ERROR_LED_PORT         GPIOB_BASE
    #define ERROR_LED_PIN          12
    #define ERROR_USART_NUM        USART2
    #define ERROR_USART_BAUD       9600
    #define ERROR_TX_PORT          GPIOA_BASE
    #define ERROR_TX_PIN           2

    /* Just in case, most boards have at least some memory */
    #ifndef RAMSIZE
    #  define RAMSIZE             (caddr_t)0x50000
    #endif

    /* Bitbanded Memory sections */
    #define BITBAND_SRAM_REF   0x20000000
    #define BITBAND_SRAM_BASE  0x22000000
    #define BITBAND_PERI_REF   0x40000000
    #define BITBAND_PERI_BASE  0x42000000

#elif defined(MCU_STM32F103ZE)
    /* e.g., LeafLabs Maple Native */

    #define NR_GPIO_PORTS             7
    #define NR_GPIO_PINS            100
    #define NR_BKP_REGS              42 /* TODO test on Native */
    #define NR_TIMERS                 8
    #define NR_USART                  5 /* NB: 4 and 5 are UART only */
    #define NR_FSMC                   1
    #define NR_DAC_PINS               2

    #define VCOM_ID_VENDOR    0x1EAF
    #define VCOM_ID_PRODUCT   0x0004
    #define USB_DISC_BANK     GPIOB_BASE
    #define USB_DISC_PIN      8
    #define USB_CONFIG_MAX_POWER      (100 >> 1)
    #define RESET_DELAY               (100)

    #define USER_ADDR_ROM 0x08005000
    #define USER_ADDR_RAM 0x20000C00
    #define STACK_TOP     0x20000800

    #define ERROR_LED_PORT         GPIOC_BASE
    #define ERROR_LED_PIN          15
    #define ERROR_USART_NUM        USART1
    #define ERROR_USART_BAUD       9600
    #define ERROR_TX_PORT          GPIOA_BASE
    #define ERROR_TX_PIN           10

    #ifndef RAMSIZE
    #  define RAMSIZE             (caddr_t)0x50000
    #endif

    #define BITBAND_SRAM_REF   0x20000000
    #define BITBAND_SRAM_BASE  0x22000000
    #define BITBAND_PERI_REF   0x40000000
    #define BITBAND_PERI_BASE  0x42000000

#elif defined(MCU_STM32F103CB)
    /* e.g., LeafLabs Maple Mini */

    #define NR_GPIO_PORTS 3
    #define NR_GPIO_PINS  34
    #define NR_BKP_REGS   10    /* TODO test on Mini */
    #define NR_TIMERS     4
    #define NR_USART      3
    #define NR_FSMC       0
    #define NR_DAC_PINS   0

    #define VCOM_ID_VENDOR       0x1EAF
    #define VCOM_ID_PRODUCT      0x0005
    #define USB_DISC_BANK        GPIOB_BASE
    #define USB_DISC_PIN         9
    #define USB_CONFIG_MAX_POWER (100 >> 1)
    #define RESET_DELAY          100

    #define USER_ADDR_ROM 0x08005000
    #define USER_ADDR_RAM 0x20000C00
    #define STACK_TOP     0x20000800

    #define ERROR_LED_PORT   GPIOB_BASE
    #define ERROR_LED_PIN    12
    #define ERROR_USART_NUM  USART2
    #define ERROR_USART_BAUD 9600
    #define ERROR_TX_PORT    GPIOA_BASE
    #define ERROR_TX_PIN     2

    #ifndef RAMSIZE
    #  define RAMSIZE             (caddr_t)0x50000
    #endif

    /* Bitbanded Memory sections */
    #define BITBAND_SRAM_REF   0x20000000
    #define BITBAND_SRAM_BASE  0x22000000
    #define BITBAND_PERI_REF   0x40000000
    #define BITBAND_PERI_BASE  0x42000000

#else

#error "No MCU type specified. Add something like -DMCU_STM32F103RB "   \
       "to your compiler arguments (probably in a Makefile)."

#endif

/* Requires board configuration info */
#include "util.h"

#endif


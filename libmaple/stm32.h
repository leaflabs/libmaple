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
 * @file stm32.h
 * @brief STM32 chip-specific definitions
 */

#ifndef _STM32_H_
#define _STM32_H_

/*
 * User-specific configuration.
 *
 * The #defines here depend upon how libmaple is used.  Because of the
 * potential for a mismatch between them and the actual libmaple
 * usage, you should try to keep their number to an absolute minimum.
 */

#ifdef __DOXYGEN_PREDEFINED_HACK

    /**
     * \def PCLK1
     * Clock speed of APB1 peripherals, in Hz.
     */
    #define PCLK1

    /**
     * \def PCLK2
     * Clock speed of APB2 peripherals, in Hz.
     */
    #define PCLK2

#endif

#ifndef PCLK1
#define PCLK1   36000000U
#endif
#ifndef PCLK2
#define PCLK2   72000000U
#endif

/*
 * Density-specific configuration.
 */

#ifdef __DOXYGEN_PREDEFINED_HACK

    /**
     * \def NR_INTERRUPTS
     *
     * Number of interrupts in the NVIC.  This define is automatically
     * generated whenever the proper density is defined (currently, this
     * is restricted to defining one of STM32_MEDIUM_DENSITY and
     * STM32_HIGH_DENSITY).
     */
    #define NR_INTERRUPTS

#endif

#ifdef STM32_MEDIUM_DENSITY
    #define NR_INTERRUPTS 43
#else
#ifdef STM32_HIGH_DENSITY
    #define NR_INTERRUPTS 60
#else
#error "No STM32 board type defined!"
#endif
#endif

/*
 * MCU-specific configuration.
 */

#ifdef __DOXYGEN_PREDEFINED_HACK

    /**
     * Number of GPIO ports
     */
    #define NR_GPIO_PORTS

    /* SRAM_SIZE intentionally not documented as I'm not convinced
     * it's a good idea [mbolivar]. */

    /**
     * @brief Multiplier to convert microseconds into loop iterations
     *        in delay_us().
     *
     * @see delay_us()
     */
    #define DELAY_US_MULT

#endif

#if defined(MCU_STM32F103RB)
    /* e.g., LeafLabs Maple */

    #define NR_GPIO_PORTS              4
    #define SRAM_SIZE             0x5000
    #define DELAY_US_MULT             12

#elif defined(MCU_STM32F103ZE)
    /* e.g., LeafLabs Maple Native */

    #define NR_GPIO_PORTS              7
    #define SRAM_SIZE            0x10000
    #define DELAY_US_MULT             12

#elif defined(MCU_STM32F103CB)
    /* e.g., LeafLabs Maple Mini */

    /* Note that this is not, strictly speaking, true.  But only pins
     * 0 and 1 exist, and they're used for OSC on the Mini, so we'll
     * live with this for now. */
    #define NR_GPIO_PORTS              3

    #define SRAM_SIZE             0x5000
    #define DELAY_US_MULT             12

#elif defined(MCU_STM32F103RE)
    /* e.g., LeafLabs Maple RET6 edition */

    #define NR_GPIO_PORTS              4
    #define SRAM_SIZE            0x10000
    #define DELAY_US_MULT             12

#else

#error "No MCU type specified. Add something like -DMCU_STM32F103RB "   \
       "to your compiler arguments (probably in a Makefile)."

#endif

#endif  /* _STM32_H_ */

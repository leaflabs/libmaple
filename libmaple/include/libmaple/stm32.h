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

#ifndef _LIBMAPLE_STM32_H_
#define _LIBMAPLE_STM32_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * STM32 series identifiers.
 *
 * Don't make these into an enum; the preprocessor needs them.
 */

/** STM32F1 series. */
#define STM32_SERIES_F1 0
/** STM32F2 series. */
#define STM32_SERIES_F2 1
/** STM32L1 series. */
#define STM32_SERIES_L1 2
/** STM32F4 series. */
#define STM32_SERIES_F4 3

/* The series header is responsible for defining:
 *
 * - Everything enclosed in the following __DOXYGEN_PREDEFINED_HACK
 *   conditional block.
 */
#include <series/stm32.h>

#ifdef __DOXYGEN_PREDEFINED_HACK

/*
 * Clock configuration.
 *
 * These defines depend upon how the MCU is configured.  Because of
 * the potential for a mismatch between them and the actual clock
 * configuration, keep their number to a minimum.
 */

/**
 * @brief APB1 clock speed, in Hz.
 */
#define STM32_PCLK1

/**
 *  @brief APB2 clock speed, in Hz.
 */
#define STM32_PCLK2

/** @brief Deprecated. Use STM32_PCLK1 instead. */
#define PCLK1
/** @brief Deprecated. Use STM32_PCLK2 instead. */
#define PCLK2

/*
 * Series- and MCU-specific values.
 */

/**
 * @brief STM32 series value for the MCU being targeted.
 *
 * At time of writing, allowed values are: STM32_SERIES_F1,
 * STM32_SERIES_F2. This set of values will expand as libmaple adds
 * support for more STM32 series MCUs.
 */
#define STM32_MCU_SERIES

/**
 * @brief Number of interrupts in the vector table.
 *
 * This does not include Cortex-M interrupts (NMI, HardFault, etc.).
 */
#define STM32_NR_INTERRUPTS

/**
 * Number of GPIO ports.
 */
#define STM32_NR_GPIO_PORTS

/**
 * @brief Multiplier to convert microseconds into loop iterations
 *        in delay_us().
 *
 * @see delay_us()
 */
#define STM32_DELAY_US_MULT

/**
 * @brief Pointer to end of built-in SRAM.
 *
 * Points to the address which is 1 byte past the last valid
 * SRAM address.
 */
#define STM32_SRAM_END

#endif  /* __DOXYGEN_PREDEFINED_HACK */

/*
 * The following are for backwards compatibility only.
 */

/* PCLK1 and PCLK2 are for backwards compatibility only; don't use in
 * new code. */
#ifndef PCLK1
#define PCLK1 STM32_PCLK1
#endif
#if PCLK1 != STM32_PCLK1
#error "PCLK1 (which is deprecated) differs from STM32_PCLK1."
#endif
#ifndef PCLK2
#define PCLK2 STM32_PCLK2
#endif
#if PCLK2 != STM32_PCLK2
#error "PCLK2 (which is deprecated) differs from STM32_PCLK2."
#endif

/** @brief Deprecated. Use STM32_NR_INTERRUPTS instead. */
#define NR_INTERRUPTS                   STM32_NR_INTERRUPTS
/** @brief Deprecated. Use STM32_NR_GPIO_PORTS instead. */
#define NR_GPIO_PORTS                   STM32_NR_GPIO_PORTS
/** @brief Deprecated. Use STM32_DELAY_US_MULT instead. */
#define DELAY_US_MULT                   STM32_DELAY_US_MULT

#ifdef __cplusplus
}
#endif

#endif

/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010, 2011 LeafLabs, LLC.
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
 * @file libmaple/stm32f1/stm32.h
 * @brief STM32F1 chip- and series-specific definitions.
 */

#ifndef _LIBMAPLE_STM32F1_H_
#define _LIBMAPLE_STM32F1_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Clock configuration.
 */

#ifndef STM32_PCLK1
#define STM32_PCLK1                     36000000U
#endif

#ifndef STM32_PCLK2
#define STM32_PCLK2                     72000000U
#endif

#ifndef STM32_DELAY_US_MULT
#define STM32_DELAY_US_MULT             12 /* FIXME: value is incorrect. */
#endif

/*
 * Density-specific values.
 */

#ifdef STM32_MEDIUM_DENSITY
#   define STM32_NR_INTERRUPTS          43
#elif defined(STM32_HIGH_DENSITY)
#   define STM32_NR_INTERRUPTS          60
#else
#error "Unsupported STM32F1 density, or no density specified. Add something " \
       "like -DSTM32_MEDIUM_DENSITY to your compiler arguments."
#endif

/*
 * Series- and MCU-specific values.
 */

#define STM32_MCU_SERIES                STM32_SERIES_F1

#if defined(MCU_STM32F103RB)
#   define STM32_NR_GPIO_PORTS          4
#   define STM32_SRAM_END               ((void*)0x20005000)

#elif defined(MCU_STM32F103ZE)
#   define STM32_NR_GPIO_PORTS          7
#   define STM32_SRAM_END               ((void*)0x20010000)

#elif defined(MCU_STM32F103CB)
    /* This STM32_NR_GPIO_PORTS is not stricly true, but only pins 0
     * and exist, and they're used for OSC (e.g. on e.g. LeafLabs
     * Maple Mini), so we'll live with this for now. */
#   define STM32_NR_GPIO_PORTS          3
#   define STM32_SRAM_END               ((void*)0x20005000)

#elif defined(MCU_STM32F103RE)
#   define STM32_NR_GPIO_PORTS          4
#   define STM32_SRAM_END               ((void*)0x20010000)

#else
#error "Unrecognized STM32F1 MCU, or no MCU specified. Add something like " \
       "-DMCU_STM32F103RB to your compiler arguments."
#endif

#ifdef __cplusplus
}
#endif

#endif

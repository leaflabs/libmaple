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
 * @file rcc.h
 * @brief Reset and Clock Control (RCC) interface.
 */

#ifndef _LIBMAPLE_RCC_H_
#define _LIBMAPLE_RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>
#include <series/rcc.h>

/* Note: Beyond the usual (registers, etc.), it's up to the series
 * header to define the following types:
 *
 * - rcc_pllsrc: For each PLL source (passed to rcc_clk_init()).
 *
 * - rcc_pll_multiplier: If appropriate (TODO verify this makes sense).
 *
 * - rcc_clk_id: For each available peripheral. These are widely used
 *   as unique IDs (TODO extricate from RCC?). Peripherals which are
 *   common across families should use the same token for their
 *   rcc_clk_id in each series header.
 *
 * - rcc_clk_domain: For each clock domain (returned by rcc_dev_clk()).
 *
 * - rcc_prescaler (and a suitable set of dividers): for rcc_set_prescaler().
 */

/**
 * SYSCLK sources
 * @see rcc_clk_init()
 */
typedef enum rcc_sysclk_src {
    RCC_CLKSRC_HSI = 0x0,
    RCC_CLKSRC_HSE = 0x1,
    RCC_CLKSRC_PLL = 0x2,
} rcc_sysclk_src;

void rcc_clk_init(rcc_sysclk_src sysclk_src,
                  rcc_pllsrc pll_src,
                  rcc_pll_multiplier pll_mul);
void rcc_clk_enable(rcc_clk_id device);
void rcc_reset_dev(rcc_clk_id device);
rcc_clk_domain rcc_dev_clk(rcc_clk_id device);
void rcc_set_prescaler(rcc_prescaler prescaler, uint32 divider);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

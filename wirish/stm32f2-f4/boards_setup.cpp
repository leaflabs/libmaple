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

/**
 * @file wirish/stm32f2/boards_setup.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief STM32F2 chip setup.
 *
 * This file controls how init() behaves on the STM32F2. Be very
 * careful when changing anything here. Many of these values depend
 * upon each other.
 */

#include "boards_private.h"

#include <libmaple/gpio.h>
#include <libmaple/syscfg.h>
#include <libmaple/libmaple_types.h>
#include <wirish/wirish_types.h>
#include <board/board.h>

// PLL config for 25 MHz external crystal --> 120 MHz SYSCLK, with
// 48 MHz PLL48CK.
#ifndef BOARD_PLL_Q
#define BOARD_PLL_Q 5
#endif
#ifndef BOARD_PLL_P
#define BOARD_PLL_P 2
#endif
#ifndef BOARD_PLL_N
#define BOARD_PLL_N 240
#endif
#ifndef BOARD_PLL_M
#define BOARD_PLL_M 25
#endif

static stm32f2_rcc_pll_data pll_data = {BOARD_PLL_Q,
                                        BOARD_PLL_P,
                                        BOARD_PLL_N,
                                        BOARD_PLL_M};

namespace wirish {
    namespace priv {
        // PLL clocked off of HSE, with above configuration data.
        __weak rcc_pll_cfg w_board_pll_cfg = {RCC_PLLSRC_HSE, &pll_data};

        // Global ADC prescaler
        //
        // On F2, with f_APB2 = 60 MHz, we need f_ADC = f_PCLK2 / 2 to
        // get the (maximum) f_ADC = 30 MHz.
        __weak adc_prescaler w_adc_pre = ADC_PRE_PCLK2_DIV_2;

        // Conservative ADC sample rate. Goal is error less than 1/4
        // LSB with 50 KOhm input impedance.
        //
        // On F2, with f_ADC = 30 MHz, error is acceptable assuming an
        // internal sample and hold capacitance C_ADC at most 8.8 pF
        // (ST doesn't specify the maximum C_ADC, so we had to take a
        // guess). See Equation 1 and Table 61 in the F2 datasheet for
        // more details.
        __weak adc_smp_rate w_adc_smp = ADC_SMPR_144;

        __weak void board_reset_pll(void) {
            // Set PLLCFGR to its reset value.
            RCC_BASE->PLLCFGR = 0x24003010; // FIXME lose the magic number.
        }

        __weak void board_setup_clock_prescalers(void) {
            // On F2, with f_SYSCLK = 120 MHz (as determined by
            // board_pll_cfg),
            //
            // f_AHB  = f_SYSCLK / 1 = 120 MHz
            // f_APB1 = f_AHB / 4    =  30 MHz
            // f_APB2 = f_AHB / 2    =  60 MHz
            rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
            rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_4);
            rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_2);
        }

        __weak void board_setup_gpio(void) {
            gpio_init_all();
        }

        __weak void board_setup_usb(void) {
            // Nothing to do.
        }

        __weak void series_init(void) {
            // We need SYSCFG for external interrupts
            syscfg_init();
            // Turn on the I/O compensation cell, since we drive the
            // GPIOs quickly by default.
            syscfg_enable_io_compensation();
        }

    }
}

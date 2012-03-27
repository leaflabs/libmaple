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
#include <wirish/wirish_types.h>

// PLL configuration for 25 MHz external oscillator --> 120 MHz SYSCLK.
#define PLL_Q 5
#define PLL_P 2
#define PLL_N 240
#define PLL_M 25
static stm32f2_rcc_pll_data pll_data = {PLL_Q, PLL_P, PLL_N, PLL_M};

namespace wirish {
    namespace priv {
        // PLL clocked off of HSE, with above configuration data.
        rcc_pll_cfg w_board_pll_cfg = {RCC_PLLSRC_HSE, &pll_data};
        // As f_APB2 = 60 MHz (see board_setup_clock_prescalers),
        // we need f_ADC = f_PCLK2 / 2 to get the (maximum)
        // f_ADC = 30 MHz.
        adc_prescaler w_adc_pre = ADC_PRE_PCLK2_DIV_2;
        // With clocks as specified here (i.e. f_ADC = 30 MHz), this
        // ADC sample rate allows for error less than 1/4 LSB with a
        // 50 KOhm input impedance, assuming an internal sample and
        // hold capacitance C_ADC at most 8.8 pF. See Equation 1 and
        // Table 61 in the F2 datasheet for more details.
        adc_smp_rate w_adc_smp = ADC_SMPR_144;

        void board_reset_pll(void) {
            // Set PLLCFGR to its reset value.
            RCC_BASE->PLLCFGR = 0x24003010; // FIXME lose the magic number.
        }

        void board_setup_clock_prescalers(void) {
            // With f_SYSCLK = 120 MHz (as determined by board_pll_cfg),
            //
            // f_AHB = f_SYSCLK / 1 = 120 MHz
            rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
            // f_APB1 = f_AHB / 4 = 30 MHz
            rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_4);
            // f_APB2 = f_AHB / 2 = 60 MHz
            rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_2);
        }

        void board_setup_gpio(void) {
            gpio_init_all();
        }

        void board_setup_timers(void) {
            // TODO
        }

        void board_setup_usb(void) {
            // TODO
        }

    }
}

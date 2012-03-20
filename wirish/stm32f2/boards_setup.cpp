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
 */

#include <libmaple/rcc.h>
#include <libmaple/gpio.h>

#define PLL_Q 5
#define PLL_P 2
#define PLL_N 240
#define PLL_M 25
static stm32f2_rcc_pll_data pll_data = {PLL_Q, PLL_P, PLL_N, PLL_M};

namespace wirish {
    namespace priv {
        rcc_pll_cfg board_pll_cfg = {RCC_PLLSRC_HSE, &pll_data};

        void board_reset_pll(void) {
            // Set PLLCFGR to its reset value.
            RCC_BASE->PLLCFGR = 0x24003010; // FIXME lose the magic number.
        }

        void board_setup_clock_prescalers(void) {
            rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
            rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_4);
            rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_2);
        }

        void board_setup_gpio(void) {
            gpio_init_all();
        }

        void board_setup_adc(void) {
            // TODO
        }

        void board_setup_timers(void) {
            // TODO
        }

        void board_setup_usb(void) {
            // TODO
        }

    }
}


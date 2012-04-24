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
 * @file wirish/stm32f1/boards_setup.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief STM32F1 chip setup.
 *
 * This file controls how init() behaves on the STM32F1. Be very
 * careful when changing anything here. Many of these values depend
 * upon each other.
 */

#include "boards_private.h"

#include <libmaple/gpio.h>
#include <libmaple/timer.h>
#include <libmaple/usb_cdcacm.h>

#include <board/board.h>

// Allow boards to provide a PLL multiplier. This is useful for
// e.g. STM32F100 value line MCUs, which use slower multipliers.
// (We're leaving the default to RCC_PLLMUL_9 for now, since that
// works for F103 performance line MCUs, which is all that LeafLabs
// currently officially supports).
#ifndef BOARD_RCC_PLLMUL
#define BOARD_RCC_PLLMUL RCC_PLLMUL_9
#endif

/* FIXME: Reintroduce all "#if 0"'ed blocks once libmaple provides
 * these definitions again. */

namespace wirish {
    namespace priv {

        static stm32f1_rcc_pll_data pll_data = {BOARD_RCC_PLLMUL};
        rcc_pll_cfg w_board_pll_cfg = {RCC_PLLSRC_HSE, &pll_data};
        adc_prescaler w_adc_pre = ADC_PRE_PCLK2_DIV_6;
        adc_smp_rate w_adc_smp = ADC_SMPR_55_5;

        static void config_timer(timer_dev*);

        void board_reset_pll(void) {
            // TODO
        }

        void board_setup_clock_prescalers(void) {
            rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
            rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_2);
            rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_1);
        }

        void board_setup_gpio(void) {
            gpio_init_all();
            // Initialize AFIO here, too, so peripheral remaps and external
            // interrupts work out of the box.
            afio_init();
        }

        void board_setup_timers(void) {
            timer_foreach(config_timer);
        }

        void board_setup_usb(void) {
#if 0
#    if STM32_HAVE_USB
            usb_cdcacm_enable(BOARD_USB_DISC_DEV, BOARD_USB_DISC_BIT);
#    endif
#endif
        }

        /*
         * Auxiliary routines
         */

        static void config_timer(timer_dev *dev) {
#if 0
            timer_adv_reg_map *regs = (dev->regs).adv;
            const uint16 full_overflow = 0xFFFF;
            const uint16 half_duty = 0x8FFF;

            timer_init(dev);
            timer_pause(dev);

            regs->CR1 = TIMER_CR1_ARPE;
            regs->PSC = 1;
            regs->SR = 0;
            regs->DIER = 0;
            regs->EGR = TIMER_EGR_UG;

            switch (dev->type) {
            case TIMER_ADVANCED:
                regs->BDTR = TIMER_BDTR_MOE | TIMER_BDTR_LOCK_OFF;
                // fall-through
            case TIMER_GENERAL:
                timer_set_reload(dev, full_overflow);

                for (int channel = 1; channel <= 4; channel++) {
                    timer_set_compare(dev, channel, half_duty);
                    timer_oc_set_mode(dev, channel, TIMER_OC_MODE_PWM_1, TIMER_OC_PE);
                }
                // fall-through
            case TIMER_BASIC:
                break;
            }

            timer_resume(dev);
#endif
        }
    }
}

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
 * @file wirish/boards.cpp
 * @brief Generic board routines.
 *
 * This file is mostly interesting for the init() function, which
 * configures Flash, the core sytem clocks, and a variety of other
 * available peripherals on the board so the rest of Wirish doesn't
 * have to turn things on before using them.
 *
 * How init() does this is chip-specific. See the chip-specific pieces
 * of Wirish (under e.g. wirish/stm32f1/, wirish/stmf32f2) for
 * details.
 *
 * Finally, prior to returning, init() calls boardInit(), which allows
 * boards to perform any initialization they need to. This file
 * includes a weak no-op definition of boardInit(), so boards that
 * don't need any special initialization don't have to define their
 * own.
 */

#include <wirish/boards.h>
#include <libmaple/libmaple_types.h>
#include <libmaple/flash.h>
#include <libmaple/nvic.h>
#include <libmaple/systick.h>
#include "boards_private.h"

static void setup_flash(void);
static void setup_clocks(void);
static void setup_nvic(void);
static void setup_adcs(void);

/*
 * Exported functions
 */

void init(void) {
    setup_flash();
    setup_clocks();
    setup_nvic();
    systick_init(SYSTICK_RELOAD_VAL);
    wirish::priv::board_setup_gpio();
    setup_adcs();
    wirish::priv::board_setup_timers();
    wirish::priv::board_setup_usb();
    boardInit();
}

/* Provide a default boardInit(). */
__weak void boardInit(void) {
}

/* You could farm this out to the files in boards/ if e.g. it takes
 * too long to test on Maple Native (all those FSMC pins...). */
bool boardUsesPin(uint8 pin) {
    for (int i = 0; i < BOARD_NR_USED_PINS; i++) {
        if (pin == boardUsedPins[i]) {
            return true;
        }
    }
    return false;
}

/*
 * Auxiliary routines
 */

static void setup_flash(void) {
    // Turn on as many Flash "go faster" features as
    // possible. flash_enable_features() just ignores any flags it
    // can't support.
    flash_enable_features(FLASH_PREFETCH | FLASH_ICACHE | FLASH_DCACHE);
    // Configure the wait states, assuming we're operating at "close
    // enough" to 3.3V.
    flash_set_latency(FLASH_SAFE_WAIT_STATES);
}

static void setup_clocks(void) {
    // Turn on HSI. We'll switch to and run off of this while we're
    // setting up the main PLL.
    rcc_turn_on_clk(RCC_CLK_HSI);

    // Turn off and reset the clock subsystems we'll be using, as well
    // as the clock security subsystem (CSS). Note that resetting CFGR
    // to its default value of 0 implies a switch to HSI for SYSCLK.
    RCC_BASE->CFGR = 0x00000000;
    rcc_disable_css();
    rcc_turn_off_clk(RCC_CLK_PLL);
    rcc_turn_off_clk(RCC_CLK_HSE);
    wirish::priv::board_reset_pll();
    // Clear clock readiness interrupt flags and turn off clock
    // readiness interrupts.
    RCC_BASE->CIR = 0x00000000;

    // Enable HSE, and wait until it's ready.
    rcc_turn_on_clk(RCC_CLK_HSE);
    while (!rcc_is_clk_ready(RCC_CLK_HSE))
        ;

    // Configure AHBx, APBx, etc. prescalers and the main PLL.
    wirish::priv::board_setup_clock_prescalers();
    rcc_configure_pll(&wirish::priv::w_board_pll_cfg);

    // Enable the PLL, and wait until it's ready.
    rcc_turn_on_clk(RCC_CLK_PLL);
    while(!rcc_is_clk_ready(RCC_CLK_PLL))
        ;

    // Finally, switch to the now-ready PLL as the main clock source.
    rcc_switch_sysclk(RCC_CLKSRC_PLL);
}

static void setup_nvic(void) {
#ifdef VECT_TAB_FLASH
    nvic_init(USER_ADDR_ROM, 0);
#elif defined VECT_TAB_RAM
    nvic_init(USER_ADDR_RAM, 0);
#elif defined VECT_TAB_BASE
    nvic_init((uint32)0x08000000, 0);
#else
#error "You must select a base address for the vector table."
#endif
}

static void adc_default_config(const adc_dev *dev) {
    adc_enable_single_swstart(dev);
    adc_set_sample_rate(dev, wirish::priv::w_adc_smp);
}

static void setup_adcs(void) {
    adc_set_prescaler(wirish::priv::w_adc_pre);
    adc_foreach(adc_default_config);
}

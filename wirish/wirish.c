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
 * @brief generic maple board bring up:
 *
 * By default, we bring up all maple boards running on the stm32 to 72mhz,
 * clocked off the PLL, driven by the 8MHz external crystal.
 *
 * AHB and APB2 are clocked at 72MHz
 * APB1 is clocked at 36MHz
 */

#include "wirish.h"
#include "systick.h"
#include "gpio.h"
#include "nvic.h"
#include "usb.h"
#include "rcc.h"
#include "fsmc.h"
#include "dac.h"
#include "flash.h"

void init(void) {
    /* make sure the flash is ready before spinning the high speed clock up */
    flash_enable_prefetch();
    flash_set_latency(FLASH_WAIT_STATE_2);

#if NR_FSMC > 0
    fsmc_native_sram_init();
#endif

#if NR_DAC_PINS > 0
    dac_init();
#endif
 
    /* initialize clocks  */
    rcc_clk_init(RCC_CLKSRC_PLL, RCC_PLLSRC_HSE, RCC_PLLMUL_9);
    rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1);
    rcc_set_prescaler(RCC_PRESCALER_APB1, RCC_APB1_HCLK_DIV_2);
    rcc_set_prescaler(RCC_PRESCALER_APB2, RCC_APB2_HCLK_DIV_1);

    nvic_init();
    systick_init(SYSTICK_RELOAD_VAL);
    gpio_init();
    adc_init();
    timer_init(TIMER1, 1);
    timer_init(TIMER2, 1);
    timer_init(TIMER3, 1);
    timer_init(TIMER4, 1);
#if NR_TIMERS >= 8
    timer_init(TIMER5, 1);
    timer_init(TIMER8, 1);
#endif
    setupUSB();

    /* include the board-specific init macro */
    BOARD_INIT;
}

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
 * @file rcc.c
 * @brief Clock setup, peripheral enable and reset routines.
 */

#include "libmaple.h"
#include "flash.h"
#include "rcc.h"
#include "bitband.h"

typedef enum clock_domain {
    APB1,
    APB2,
    AHB
} clock_domain;

struct rcc_dev_info {
    const clock_domain clk_domain;
    const uint8 line_num;
};

/* device descriptor tables  */
static const __attr_flash struct rcc_dev_info rcc_dev_table[] = {
    [RCC_SRAM]    = { .clk_domain = AHB,  .line_num = 2 },
    [RCC_GPIOA]   = { .clk_domain = APB2, .line_num = 2 },
    [RCC_GPIOB]   = { .clk_domain = APB2, .line_num = 3 },
    [RCC_GPIOC]   = { .clk_domain = APB2, .line_num = 4 },
    [RCC_GPIOD]   = { .clk_domain = APB2, .line_num = 5 },
    [RCC_AFIO]    = { .clk_domain = APB2, .line_num = 0 },
    [RCC_ADC1]    = { .clk_domain = APB2, .line_num = 9 },
    [RCC_ADC2]    = { .clk_domain = APB2, .line_num = 10 },
    [RCC_USART1]  = { .clk_domain = APB2, .line_num = 14 },
    [RCC_USART2]  = { .clk_domain = APB1, .line_num = 17 },
    [RCC_USART3]  = { .clk_domain = APB1, .line_num = 18 },
    [RCC_TIMER1]  = { .clk_domain = APB2, .line_num = 11 },
    [RCC_TIMER2]  = { .clk_domain = APB1, .line_num = 0 },
    [RCC_TIMER3]  = { .clk_domain = APB1, .line_num = 1 },
    [RCC_TIMER4]  = { .clk_domain = APB1, .line_num = 2 },
    [RCC_SPI1]    = { .clk_domain = APB2, .line_num = 12 },
    [RCC_SPI2]    = { .clk_domain = APB1, .line_num = 14 },
    [RCC_DMA1]    = { .clk_domain = AHB,  .line_num = 0 },
    [RCC_PWR]     = { .clk_domain = APB1, .line_num = 28 },
    [RCC_BKP]     = { .clk_domain = APB1, .line_num = 27 },
    [RCC_CAN]     = { .clk_domain = APB1, .line_num = 25 },
    [RCC_USB]     = { .clk_domain = APB1, .line_num = 23 },
    [RCC_I2C1]    = { .clk_domain = APB1, .line_num = 22 },
    [RCC_I2C2]    = { .clk_domain = APB1, .line_num = 21 },
    [RCC_CRC]     = { .clk_domain = AHB,  .line_num = 6 },
    [RCC_WWDG]    = { .clk_domain = APB2, .line_num = 11 },
    [RCC_FLITF]   = { .clk_domain = AHB,  .line_num = 4 },
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    [RCC_SDIO]    = { .clk_domain = AHB,  .line_num = 10 },
    [RCC_FSMC]    = { .clk_domain = AHB,  .line_num = 8 },
    [RCC_GPIOE]   = { .clk_domain = APB2, .line_num = 6 },
    [RCC_GPIOF]   = { .clk_domain = APB2, .line_num = 7 },
    [RCC_GPIOG]   = { .clk_domain = APB2, .line_num = 8 },
    [RCC_ADC3]    = { .clk_domain = APB2, .line_num = 15 },
    [RCC_UART4]   = { .clk_domain = APB1, .line_num = 19 },
    [RCC_UART5]   = { .clk_domain = APB1, .line_num = 20 },
    [RCC_TIMER5]  = { .clk_domain = APB1, .line_num = 3 },
    [RCC_TIMER6]  = { .clk_domain = APB1, .line_num = 4 },
    [RCC_TIMER7]  = { .clk_domain = APB1, .line_num = 5 },
    [RCC_TIMER8]  = { .clk_domain = APB2, .line_num = 13 },
    [RCC_DAC]     = { .clk_domain = APB1, .line_num = 29 },
    [RCC_DMA2]    = { .clk_domain = AHB,  .line_num = 1 },
    [RCC_SPI3]    = { .clk_domain = APB1, .line_num = 15 },
#endif
#ifdef STM32_XL_DENSITY
    [RCC_TIMER9]  = { .clk_domain = APB2, .line_num = 19 },
    [RCC_TIMER10] = { .clk_domain = APB2, .line_num = 20 },
    [RCC_TIMER11] = { .clk_domain = APB2, .line_num = 21 },
    [RCC_TIMER12] = { .clk_domain = APB1, .line_num = 6 },
    [RCC_TIMER13] = { .clk_domain = APB1, .line_num = 7 },
    [RCC_TIMER14] = { .clk_domain = APB1, .line_num = 8 },
#endif
};

/**
 * @brief Initialize the clock control system. Initializes the system
 *        clock source to use the PLL driven by an external oscillator
 * @param sysclk_src system clock source, must be PLL
 * @param pll_src pll clock source, must be RCC_CFGR_PLLSRC_HSE
 * @param pll_mul pll multiplier
 */
void rcc_clk_init(uint32 sysclk_src, uint32 pll_src, uint32 pll_mul) {
    uint32 cfgr;

    /* Assume that we're going to clock the chip off the PLL, fed by
     * the HSE */
    ASSERT(sysclk_src == RCC_CLKSRC_PLL &&
           pll_src    == RCC_CFGR_PLLSRC_HSE);

    RCC_BASE->CFGR = pll_src | pll_mul;

    /* Turn on the HSE */
    *bb_perip(&RCC_BASE->CR, RCC_CR_HSEON_BIT) = 1;
    while (!(*bb_perip(&RCC_BASE->CR, RCC_CR_HSERDY_BIT)))
        ;

    /* Now the PLL */
    *bb_perip(&RCC_BASE->CR, RCC_CR_PLLON_BIT) = 1;
    while (!(*bb_perip(&RCC_BASE->CR, RCC_CR_PLLRDY_BIT)))
        ;

    /* Finally, let's switch over to the PLL  */
    cfgr = RCC_BASE->CFGR;
    cfgr &= ~RCC_CFGR_SW;
    cfgr |= RCC_CFGR_SW_PLL;
    RCC_BASE->CFGR = cfgr;
    while ((RCC_BASE->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ;
}

/**
 * @brief Turn on the clock line on a device
 * @param device Clock ID of the device to turn on.
 */
void rcc_clk_enable(rcc_clk_id id) {
    uint8 lnum = rcc_dev_table[id].line_num;
    __io uint32 *enr;

    switch(rcc_dev_table[id].clk_domain) {
    case APB1:
        enr = &RCC_BASE->APB1ENR;
        break;
    case APB2:
         enr = &RCC_BASE->APB2ENR;
        break;
    case AHB:
        enr = &RCC_BASE->AHBENR;
        break;
    }

    *bb_perip(enr, lnum) = 1;
}

/**
 * @brief Set the divider on a device prescaler
 * @param prescaler prescaler to set
 * @param divider prescaler divider
 */
void rcc_set_prescaler(rcc_prescaler prescaler, uint32 divider) {
    static const uint32 masks[] = {
        [RCC_PRESCALER_AHB] = RCC_CFGR_HPRE,
        [RCC_PRESCALER_APB1] = RCC_CFGR_PPRE1,
        [RCC_PRESCALER_APB2] = RCC_CFGR_PPRE2,
        [RCC_PRESCALER_USB] = RCC_CFGR_USBPRE,
        [RCC_PRESCALER_ADC] = RCC_CFGR_ADCPRE,
    };
    uint32 cfgr;

    cfgr = RCC_BASE->CFGR;
    cfgr &= ~masks[prescaler];
    cfgr |= divider;
    RCC_BASE->CFGR = cfgr;
}

/**
 * @brief Reset a device
 * @param device Clock ID of the device to reset; the device must be
 *               on APB1 or APB2.
 */
void rcc_reset_dev(rcc_clk_id id) {
    uint8 lnum = rcc_dev_table[id].line_num;
    __io uint32 *rstr = 0;

    switch (rcc_dev_table[id].clk_domain) {
    case APB1:
        rstr = &RCC_BASE->APB1RSTR;
        break;
    case APB2:
        rstr = &RCC_BASE->APB2RSTR;
        break;
    case AHB:
        ASSERT(0);
        break;
    }

    if (rstr == 0) {
        return;
    }

    *bb_perip(rstr, lnum) = 1;
    *bb_perip(rstr, lnum) = 0;
}

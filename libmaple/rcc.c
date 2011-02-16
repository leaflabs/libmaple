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
 * @brief Implements pretty much only the basic clock setup on the
 *        stm32, clock enable/disable and peripheral reset commands.
 */

#include "libmaple.h"
#include "flash.h"
#include "rcc.h"

enum {
    APB1,
    APB2,
    AHB
};

struct rcc_dev_info {
    const uint8 clk_domain;
    const uint8 line_num;
};

/* device descriptor tables  */
static const struct rcc_dev_info rcc_dev_table[] = {
    [RCC_GPIOA]  = { .clk_domain = APB2, .line_num = 2 },
    [RCC_GPIOB]  = { .clk_domain = APB2, .line_num = 3 },
    [RCC_GPIOC]  = { .clk_domain = APB2, .line_num = 4 },
    [RCC_GPIOD]  = { .clk_domain = APB2, .line_num = 5 },
    [RCC_GPIOE]  = { .clk_domain = APB2, .line_num = 6 }, // High-density only
    [RCC_GPIOF]  = { .clk_domain = APB2, .line_num = 7 }, // High-density only
    [RCC_GPIOG]  = { .clk_domain = APB2, .line_num = 8 }, // High-density only
    [RCC_AFIO]   = { .clk_domain = APB2, .line_num = 0 },
    [RCC_ADC1]   = { .clk_domain = APB2, .line_num = 9 },
    [RCC_ADC2]   = { .clk_domain = APB2, .line_num = 10 },
    [RCC_USART1] = { .clk_domain = APB2, .line_num = 14 },
    [RCC_USART2] = { .clk_domain = APB1, .line_num = 17 },
    [RCC_USART3] = { .clk_domain = APB1, .line_num = 18 },
    [RCC_UART4]  = { .clk_domain = APB1, .line_num = 19 }, // High-density only
    [RCC_UART5]  = { .clk_domain = APB1, .line_num = 20 }, // High-density only
    [RCC_TIMER1] = { .clk_domain = APB2, .line_num = 11 },
    [RCC_TIMER2] = { .clk_domain = APB1, .line_num = 0 },
    [RCC_TIMER3] = { .clk_domain = APB1, .line_num = 1 },
    [RCC_TIMER4] = { .clk_domain = APB1, .line_num = 2 },
    [RCC_TIMER5] = { .clk_domain = APB1, .line_num = 3 }, // High-density only
    [RCC_TIMER6] = { .clk_domain = APB1, .line_num = 4 }, // High-density only
    [RCC_TIMER7] = { .clk_domain = APB1, .line_num = 5 }, // High-density only
    [RCC_TIMER8] = { .clk_domain = APB2, .line_num = 13 }, // High-density only
    [RCC_SPI1]   = { .clk_domain = APB2, .line_num = 12 },
    [RCC_SPI2]   = { .clk_domain = APB1, .line_num = 14 },
    [RCC_FSMC]   = { .clk_domain = AHB,  .line_num = 8 }, // High-density only
    [RCC_DAC]    = { .clk_domain = APB1, .line_num = 9 }, // High-density only
    [RCC_DMA1]   = { .clk_domain = AHB,  .line_num = 0 },
    [RCC_DMA2]   = { .clk_domain = AHB,  .line_num = 1 }, // High-density only
};

/**
 * @brief Initialize the clock control system. Initializes the system
 *        clock source to use the PLL driven by an external oscillator
 * @param sysclk_src system clock source, must be PLL
 * @param pll_src pll clock source, must be HSE
 * @param pll_mul pll multiplier
 */
void rcc_clk_init(uint32 sysclk_src, uint32 pll_src, uint32 pll_mul) {
    /* Assume that we're going to clock the chip off the PLL, fed by
     * the HSE */
    ASSERT(sysclk_src == RCC_CLKSRC_PLL &&
           pll_src    == RCC_PLLSRC_HSE);

    uint32 cfgr = 0;
    uint32 cr = RCC_READ_CR();

    cfgr =  (pll_src | pll_mul);
    RCC_WRITE_CFGR(cfgr);

    /* Turn on the HSE  */
    cr |= RCC_CR_HSEON;
    RCC_WRITE_CR(cr);
    while (!(RCC_READ_CR() & RCC_CR_HSERDY))
        ;

    /* Now the PLL  */
    cr |= RCC_CR_PLLON;
    RCC_WRITE_CR(cr);
    while (!(RCC_READ_CR() & RCC_CR_PLLRDY))
        ;

    /* Finally, let's switch over to the PLL  */
    cfgr &= ~RCC_CFGR_SW;
    cfgr |= RCC_CFGR_SW_PLL;
    RCC_WRITE_CFGR(cfgr);
    while ((RCC_READ_CFGR() & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ;
}

/**
 * @brief Turn on the clock line on a device
 * @param dev_num device to turn on
 */
void rcc_clk_enable(uint32 dev_num) {
    static const uint32 enable_regs[] = {
        [APB1] = RCC_APB1ENR,
        [APB2] = RCC_APB2ENR,
        [AHB] = RCC_AHBENR,
    };

    uint8 clk_domain = rcc_dev_table[dev_num].clk_domain;

    __set_bits(enable_regs[clk_domain], BIT(rcc_dev_table[dev_num].line_num));
}

/**
 * @brief Set the divider on a device prescaler
 * @param prescaler prescaler to set
 * @param divider prescaler divider
 */
void rcc_set_prescaler(uint32 prescaler, uint32 divider) {
    static const uint32 masks[] = {
        [RCC_PRESCALER_AHB] = RCC_CFGR_HPRE,
        [RCC_PRESCALER_APB1] = RCC_CFGR_PPRE1,
        [RCC_PRESCALER_APB2] = RCC_CFGR_PPRE2,
        [RCC_PRESCALER_USB] = RCC_CFGR_USBPRE,
        [RCC_PRESCALER_ADC] = RCC_CFGR_ADCPRE,
    };

    uint32 cfgr = RCC_READ_CFGR();

    cfgr &= ~masks[prescaler];
    cfgr |= divider;
    RCC_WRITE_CFGR(cfgr);
}

/**
 * @brief reset a device
 * @param dev_num device to reset
 */
void rcc_reset_dev(uint32 dev_num) {
    static const uint32 reset_regs[] = {
        [APB1] = RCC_APB1RSTR,
        [APB2] = RCC_APB2RSTR,
    };

    uint8 clk_domain = rcc_dev_table[dev_num].clk_domain;

    __set_bits(reset_regs[clk_domain], BIT(rcc_dev_table[dev_num].line_num));
    __clear_bits(reset_regs[clk_domain], BIT(rcc_dev_table[dev_num].line_num));
}

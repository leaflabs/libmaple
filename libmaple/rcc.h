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
 * @file rcc.h
 * @brief reset and clock control definitions and prototypes
 */

#ifndef _RCC_H_
#define _RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

/* registers  */
#define RCC_BASE               0x40021000
#define RCC_CR                 (RCC_BASE + 0x0)
#define RCC_CFGR               (RCC_BASE + 0x4)
#define RCC_CIR                (RCC_BASE + 0x8)
#define RCC_APB2RSTR           (RCC_BASE + 0xC)
#define RCC_APB1RSTR           (RCC_BASE + 0x10)
#define RCC_AHBENR             (RCC_BASE + 0x14)
#define RCC_APB2ENR            (RCC_BASE + 0x18)
#define RCC_APB1ENR            (RCC_BASE + 0x1C)
#define RCC_BDCR               (RCC_BASE + 0x20)
#define RCC_CSR                (RCC_BASE + 0x24)
#define RCC_AHBSTR             (RCC_BASE + 0x28)
#define RCC_CFGR2              (RCC_BASE + 0x2C)

#define RCC_CFGR_USBPRE        (0x1 << 22)
#define RCC_CFGR_ADCPRE        (0x3 << 14)
#define RCC_CFGR_PPRE1         (0x7 << 8)
#define RCC_CFGR_PPRE2         (0x7 << 11)
#define RCC_CFGR_HPRE          (0xF << 4)
#define RCC_CFGR_PLLSRC        (0x1 << 16)

#define RCC_CFGR_SWS           (0x3 << 2)
#define RCC_CFGR_SWS_PLL       (0x2 << 2)
#define RCC_CFGR_SWS_HSE       (0x1 << 2)

#define RCC_CFGR_SW            (0x3 << 0)
#define RCC_CFGR_SW_PLL        (0x2 << 0)
#define RCC_CFGR_SW_HSE        (0x1 << 0)

/* CR status bits  */
#define RCC_CR_HSEON           (0x1 << 16)
#define RCC_CR_HSERDY          (0x1 << 17)
#define RCC_CR_PLLON           (0x1 << 24)
#define RCC_CR_PLLRDY          (0x1 << 25)

#define RCC_WRITE_CFGR(val)    __write(RCC_CFGR, val)
#define RCC_READ_CFGR()        __read(RCC_CFGR)

#define RCC_WRITE_CR(val)      __write(RCC_CR, val)
#define RCC_READ_CR()          __read(RCC_CR)

/* sysclk source  */
#define RCC_CLKSRC_HSI                          (0x0)
#define RCC_CLKSRC_HSE                          (0x1)
#define RCC_CLKSRC_PLL                          (0x2)

/* pll entry clock source  */
#define RCC_PLLSRC_HSE                          (0x1 << 16)
#define RCC_PLLSRC_HSI_DIV_2                    (0x0 << 16)

/* adc prescaler dividers  */
#define RCC_ADCPRE_PCLK_DIV_2                   (0x0 << 14)
#define RCC_ADCPRE_PCLK_DIV_4                   (0x1 << 14)
#define RCC_ADCPRE_PCLK_DIV_6                   (0x2 << 14)
#define RCC_ADCPRE_PCLK_DIV_8                   (0x3 << 14)

/* apb1 prescaler dividers  */
#define RCC_APB1_HCLK_DIV_1                     (0x0 << 8)
#define RCC_APB1_HCLK_DIV_2                     (0x4 << 8)
#define RCC_APB1_HCLK_DIV_4                     (0x5 << 8)
#define RCC_APB1_HCLK_DIV_8                     (0x6 << 8)
#define RCC_APB1_HCLK_DIV_16                    (0x7 << 8)

/* apb2 prescaler dividers  */
#define RCC_APB2_HCLK_DIV_1                     (0x0 << 11)
#define RCC_APB2_HCLK_DIV_2                     (0x4 << 11)
#define RCC_APB2_HCLK_DIV_4                     (0x5 << 11)
#define RCC_APB2_HCLK_DIV_8                     (0x6 << 11)
#define RCC_APB2_HCLK_DIV_16                    (0x7 << 11)

/* ahb prescaler dividers  */
#define RCC_AHB_SYSCLK_DIV_1                    (0x0 << 4)
#define RCC_AHB_SYSCLK_DIV_2                    (0x8 << 4)
#define RCC_AHB_SYSCLK_DIV_4                    (0x9 << 4)
#define RCC_AHB_SYSCLK_DIV_8                    (0xA << 4)
#define RCC_AHB_SYSCLK_DIV_16                   (0xB << 4)
#define RCC_AHB_SYSCLK_DIV_32                   (0xC << 4)
#define RCC_AHB_SYSCLK_DIV_64                   (0xD << 4)
#define RCC_AHB_SYSCLK_DIV_128                  (0xD << 4)
#define RCC_AHB_SYSCLK_DIV_256                  (0xE << 4)
#define RCC_AHB_SYSCLK_DIV_512                  (0xF << 4)

/* pll multipliers  */
#define RCC_PLLMUL_2                            (0x0 << 18)
#define RCC_PLLMUL_3                            (0x1 << 18)
#define RCC_PLLMUL_4                            (0x2 << 18)
#define RCC_PLLMUL_5                            (0x3 << 18)
#define RCC_PLLMUL_6                            (0x4 << 18)
#define RCC_PLLMUL_7                            (0x5 << 18)
#define RCC_PLLMUL_8                            (0x6 << 18)
#define RCC_PLLMUL_9                            (0x7 << 18)
#define RCC_PLLMUL_10                           (0x8 << 18)
#define RCC_PLLMUL_11                           (0x9 << 18)
#define RCC_PLLMUL_12                           (0xA << 18)
#define RCC_PLLMUL_13                           (0xB << 18)
#define RCC_PLLMUL_14                           (0xC << 18)
#define RCC_PLLMUL_15                           (0xD << 18)
#define RCC_PLLMUL_16                           (0xE << 18)


/* prescalers */
enum {
    RCC_PRESCALER_AHB,
    RCC_PRESCALER_APB1,
    RCC_PRESCALER_APB2,
    RCC_PRESCALER_USB,
    RCC_PRESCALER_ADC
};

// RCC Devices
enum {
    RCC_GPIOA,
    RCC_GPIOB,
    RCC_GPIOC,
    RCC_GPIOD,
    RCC_GPIOE,       // High-density devices only (Maple Native)
    RCC_GPIOF,       // High-density devices only (Maple Native)
    RCC_GPIOG,       // High-density devices only (Maple Native)
    RCC_AFIO,
    RCC_ADC1,
    RCC_ADC2,
    RCC_USART1,
    RCC_USART2,
    RCC_USART3,
    RCC_UART4,      // High-density devices only (Maple Native)
    RCC_UART5,      // High-density devices only (Maple Native)
    RCC_TIMER1,
    RCC_TIMER2,
    RCC_TIMER3,
    RCC_TIMER4,
    RCC_TIMER5,      // High-density devices only (Maple Native)
    RCC_TIMER6,      // High-density devices only (Maple Native)
    RCC_TIMER7,      // High-density devices only (Maple Native)
    RCC_TIMER8,      // High-density devices only (Maple Native)
    RCC_SPI1,
    RCC_SPI2,
    RCC_FSMC,        // High-density devices only (Maple Native)
    RCC_DAC,         // High-density devices only (Maple Native)
    RCC_DMA1,
    RCC_DMA2,        // High-density devices only (Maple Native)
};


void rcc_clk_init(uint32 sysclk_src, uint32 pll_src, uint32 pll_mul);
void rcc_clk_enable(uint32 dev);
void rcc_reset_dev(uint32 dev);
void rcc_set_prescaler(uint32 prescaler, uint32 divider);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

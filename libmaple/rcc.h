/* *****************************************************************************
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
 * ****************************************************************************/

/**
 *  @brief reset and clock control definitions and prototypes
 */

#ifndef _RCC_H_
#define _RCC_H_

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

/* device numbers  */
enum {
   RCC_GPIOA,
   RCC_GPIOB,
   RCC_GPIOC,
   RCC_GPIOD,
   RCC_AFIO,
   RCC_ADC1,
   RCC_USART1,
   RCC_USART2,
   RCC_USART3,
   RCC_USART4,
   RCC_USART5,
   RCC_TIMER1,
   RCC_TIMER2,
   RCC_TIMER3,
   RCC_TIMER4,
};

/* prescalers */
enum {
   RCC_PRESCALER_AHB,
   RCC_PRESCALER_APB1,
   RCC_PRESCALER_APB2,
   RCC_PRESCALER_USB,
   RCC_PRESCALER_ADC
};


void rcc_clk_init(uint32 sysclk_src, uint32 pll_src, uint32 pll_mul);
void rcc_clk_enable(uint32 dev);
void rcc_reset_dev(uint32 dev);
void rcc_set_prescaler(uint32 prescaler, uint32 divider);

#endif



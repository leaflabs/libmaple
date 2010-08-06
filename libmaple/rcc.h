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
 *  @file rcc.h
 *
 *  @brief 
 */

#ifndef _RCC_H_
#define _RCC_H_

struct rcc_device {
   uint32 apb1_prescale;
   uint32 apb2_prescale;
   uint32 ahb_prescale;
   uint32 sysclk_src;
   uint32 pll_src;
   uint32 pll_mul;
};

#define RCC_CLKSRC_HSI                          (0x0)
#define RCC_CLKSRC_HSE                          (0x1)
#define RCC_CLKSRC_PLL                          (0x2)

#define RCC_PLLSRC_HSI_DIV_2                (0x0 << 16)
#define RCC_PLLSRC_HSE                      (0x1 << 16)

#define RCC_APB1_HCLK_DIV_1                     (0x0 << 8)
#define RCC_APB1_HCLK_DIV_2                     (0x4 << 8)
#define RCC_APB1_HCLK_DIV_4                     (0x5 << 8)
#define RCC_APB1_HCLK_DIV_8                     (0x6 << 8)
#define RCC_APB1_HCLK_DIV_16                    (0x7 << 8)

#define RCC_APB2_HCLK_DIV_1                     (0x0 << 11)
#define RCC_APB2_HCLK_DIV_2                     (0x4 << 11)
#define RCC_APB2_HCLK_DIV_4                     (0x5 << 11)
#define RCC_APB2_HCLK_DIV_8                     (0x6 << 11)
#define RCC_APB2_HCLK_DIV_16                    (0x7 << 11)

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

/* remove!!  */
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

/* APB2 reset bits  */
#define RCC_APB2RSTR_USART1RST   BIT(14)
#define RCC_APB2RSTR_SPI1RST     BIT(12)
#define RCC_APB2RSTR_TIM1RST     BIT(11)
#define RCC_APB2RSTR_ADC2RST     BIT(10)
#define RCC_APB2RSTR_ADC1RST     BIT(9)
#define RCC_APB2RSTR_IOERST      BIT(6)
#define RCC_APB2RSTR_IODRST      BIT(5)
#define RCC_APB2RSTR_IOCRST      BIT(4)
#define RCC_APB2RSTR_IOBRST      BIT(3)
#define RCC_APB2RSTR_IOARST      BIT(2)
#define RCC_APB2RSTR_AFIORST     BIT(0)

#define RCC_APB1RSTR_USB         BIT(23)

/* APB2 peripheral clock enable bits  */
#define RCC_APB2ENR_USART1EN   BIT(14)
#define RCC_APB2ENR_SPI1EN     BIT(12)
#define RCC_APB2ENR_TIM1EN     BIT(11)
#define RCC_APB2ENR_ADC2EN     BIT(10)
#define RCC_APB2ENR_ADC1EN     BIT(9)
#define RCC_APB2ENR_IOEEN      BIT(6)
#define RCC_APB2ENR_IODEN      BIT(5)
#define RCC_APB2ENR_IOCEN      BIT(4)
#define RCC_APB2ENR_IOBEN      BIT(3)
#define RCC_APB2ENR_IOAEN      BIT(2)
#define RCC_APB2ENR_AFIOEN     BIT(0)

/* APB1 peripheral clock enable bits  */
#define RCC_APB1ENR_TIM2EN     BIT(0)
#define RCC_APB1ENR_TIM3EN     BIT(1)
#define RCC_APB1ENR_TIM4EN     BIT(2)
#define RCC_APB1ENR_USART2EN   BIT(17)
#define RCC_APB1ENR_USART3EN   BIT(18)
#define RCC_APB1ENR_SPI2EN     BIT(14)
#define RCC_APB1ENR_USB        BIT(23)

#define rcc_enable_clk_spi1()     __set_bits(RCC_APB2ENR, RCC_APB2ENR_SPI1EN)
#define rcc_enable_clk_spi2()     __set_bits(RCC_APB1ENR, RCC_APB1ENR_SPI2EN)

#define rcc_enable_clk_timer1()   __set_bits(RCC_APB2ENR, RCC_APB2ENR_TIM1EN)
#define rcc_enable_clk_timer2()   __set_bits(RCC_APB1ENR, RCC_APB1ENR_TIM2EN)
#define rcc_enable_clk_timer3()   __set_bits(RCC_APB1ENR, RCC_APB1ENR_TIM3EN)
#define rcc_enable_clk_timer4()   __set_bits(RCC_APB1ENR, RCC_APB1ENR_TIM4EN)

#define rcc_enable_clk_gpioa()    __set_bits(RCC_APB2ENR, RCC_APB2ENR_IOAEN)
#define rcc_enable_clk_gpiob()    __set_bits(RCC_APB2ENR, RCC_APB2ENR_IOBEN)
#define rcc_enable_clk_gpioc()    __set_bits(RCC_APB2ENR, RCC_APB2ENR_IOCEN)
#define rcc_enable_clk_gpiod()    __set_bits(RCC_APB2ENR, RCC_APB2ENR_IODEN)
#define rcc_enable_clk_afio()     __set_bits(RCC_APB2ENR, RCC_APB2ENR_AFIOEN)

#define rcc_enable_clk_usart1()   __set_bits(RCC_APB2ENR, RCC_APB2ENR_USART1EN)
#define rcc_enable_clk_usart2()   __set_bits(RCC_APB1ENR, RCC_APB1ENR_USART2EN)
#define rcc_enable_clk_usart3()   __set_bits(RCC_APB1ENR, RCC_APB1ENR_USART3EN)

#define rcc_enable_clk_adc1()     __set_bits(RCC_APB2ENR, RCC_APB2ENR_ADC1EN)

#define rcc_reset_adc1()          { __set_bits(RCC_APB2RSTR, RCC_APB2RSTR_ADC1RST);   \
                                    __clear_bits(RCC_APB2RSTR, RCC_APB2RSTR_ADC1RST); \
                                  }

#define rcc_reset_usb()           { __set_bits(RCC_APB1RSTR, RCC_APB1RSTR_USB);   \
                                    __clear_bits(RCC_APB1RSTR, RCC_APB1RSTR_USB); \
                                  }


#define PCLK2_DIV_2            0x00008000

#ifdef __cplusplus
extern "C"{
#endif

void rcc_init(struct rcc_device *dev);

#ifdef __cplusplus
}
#endif

#endif



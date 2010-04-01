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
 *  @file rcc.c
 *
 *  @brief Implements pretty much only the basic clock setup on the maple,
 *  exposes a handful of clock enable/disable and peripheral reset commands.
 */

#include "libmaple.h"
#include "flash.h"
#include "rcc.h"

static void set_ahb_prescaler(uint32 divider) {
   uint32 cfgr = __read(RCC_CFGR);

   cfgr &= ~HPRE;

   switch (divider) {
   case SYSCLK_DIV_1:
      cfgr |= SYSCLK_DIV_1;
      break;
   default:
      ASSERT(0);
   }

   __write(RCC_CFGR, cfgr);
}

static void set_apb1_prescaler(uint32 divider) {
   uint32 cfgr = __read(RCC_CFGR);

   cfgr &= ~PPRE1;

   switch (divider) {
   case HCLK_DIV_2:
      cfgr |= HCLK_DIV_2;
      break;
   default:
      ASSERT(0);
   }

   __write(RCC_CFGR, cfgr);
}

static void set_apb2_prescaler(uint32 divider) {
   uint32 cfgr = __read(RCC_CFGR);

   cfgr &= ~PPRE2;

   switch (divider) {
   case HCLK_DIV_1:
      cfgr |= HCLK_DIV_1;
      break;
   default:
      ASSERT(0);
   }

   __write(RCC_CFGR, cfgr);
}

/* FIXME: magic numbers  */
static void pll_init(void) {
   uint32 cfgr;

   cfgr = __read(RCC_CFGR);
   cfgr &= (~PLLMUL | PLL_INPUT_CLK_HSE);

   /* pll multiplier 9, input clock hse */
   __write(RCC_CFGR, cfgr | PLL_MUL_9 | PLL_INPUT_CLK_HSE);

   /* enable pll  */
   __set_bits(RCC_CR, PLLON);
   while(!__get_bits(RCC_CR, PLLRDY)) {
      asm volatile("nop");
   }

   /* select pll for system clock source  */
   cfgr = __read(RCC_CFGR);
   cfgr &= ~RCC_CFGR_SWS;
   __write(RCC_CFGR, cfgr | RCC_CFGR_SWS_PLL);

   while (__get_bits(RCC_CFGR, 0x00000008) != 0x8) {
      asm volatile("nop");
   }
}

static void hse_init(void) {
   __set_bits(RCC_CR, HSEON);
   while (!HSERDY) {
      asm volatile("nop");
   }
}

void rcc_init(void) {
   hse_init();

   /* Leave this here for now...  */
   /* Enable Prefetch Buffer */
   flash_enable_prefetch();

   /* Flash 2 wait state */
   flash_set_latency();

   set_ahb_prescaler(SYSCLK_DIV_1);
   set_apb1_prescaler(HCLK_DIV_2);
   set_apb2_prescaler(HCLK_DIV_1);
   pll_init();
}

void rcc_set_adc_prescaler(uint32 divider) {
   uint32 cfgr = __read(RCC_CFGR);
   cfgr &= ~ADCPRE;
   __write(RCC_CFGR, cfgr | PCLK2_DIV_2);
}

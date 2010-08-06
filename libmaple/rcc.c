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
 *  @brief Implements pretty much only the basic clock setup on the stm32,
 *  exposes a handful of clock enable/disable and peripheral reset commands.
 */

#include "libmaple.h"
#include "flash.h"
#include "rcc.h"

#define RCC_CFGR_PPRE1                           (0x7 << 8)
#define RCC_CFGR_PPRE2                           (0x7 << 11)
#define RCC_CFGR_HPRE                            (0xF << 4)
#define RCC_CFGR_PLLSRC                          (0x1 << 16)

#define RCC_CFGR_SWS                             (0x3 << 2)
#define RCC_CFGR_SWS_PLL                         (0x2 << 2)
#define RCC_CFGR_SWS_HSE                         (0x1 << 2)

#define RCC_CFGR_SW                              (0x3 << 0)
#define RCC_CFGR_SW_PLL                          (0x2 << 0)
#define RCC_CFGR_SW_HSE                          (0x1 << 0)

/* CR status bits  */
#define RCC_CR_HSEON                             (0x1 << 16)
#define RCC_CR_HSERDY                            (0x1 << 17)
#define RCC_CR_PLLON                             (0x1 << 24)
#define RCC_CR_PLLRDY                            (0x1 << 25)

#define RCC_WRITE_CFGR(val)                      __write(RCC_CFGR, val)
#define RCC_READ_CFGR()                          __read(RCC_CFGR)

#define RCC_WRITE_CR(val)                        __write(RCC_CR, val)
#define RCC_READ_CR()                            __read(RCC_CR)

/**
 * @brief Initialize the clock control system. Sets up only the basics:
 *      APB1 clock prescaler
 *      APB2 clock prescaler
 *      AHB clock prescaler
 *      System clock source (Must be PLL)
 *      PLL clock source (Must be high-speed external clock)
 *      PLL Multiplier
 * @param dev initialization struct
 * @sideeffect Switches clock source to PLL, clock speed to HSE_CLK*PLLMUL
 */
void rcc_init(struct rcc_device *dev) {
   /* Assume that we're going to clock the chip off the PLL, fed by
    * the HSE */
   ASSERT(dev->sysclk_src == RCC_CLKSRC_PLL &&
          dev->pll_src    == RCC_PLLSRC_HSE);

   uint32 cfgr = 0;
   uint32 cr = RCC_READ_CR();

   cfgr =  (dev->apb1_prescale |
            dev->apb2_prescale |
            dev->ahb_prescale  |
            dev->pll_src       |
            dev->pll_mul);
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

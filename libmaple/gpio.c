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
 *  @file gpio.c
 *
 *  @brief GPIO initialization routine
 */

#include "libmaple.h"
#include "rcc.h"
#include "gpio.h"

void gpio_init(void) {
   rcc_enable_clk_gpioa();
   rcc_enable_clk_gpiob();
   rcc_enable_clk_gpioc();
   rcc_enable_clk_gpiod();
   rcc_enable_clk_afio();
}

void gpio_set_mode(GPIO_Port* port, uint8 gpio_pin, GPIOPinMode mode) {
   uint32 tmp;
   uint32 shift = POS(gpio_pin % 8);
   GPIOReg CR;

   ASSERT(port);
   ASSERT(gpio_pin < 16);

   if (mode == GPIO_MODE_INPUT_PU) {
      port->ODR |= BIT(gpio_pin);
      mode = CNF_INPUT_PD;
   } else if (mode == GPIO_MODE_INPUT_PD) {
      port->ODR &= ~BIT(gpio_pin);
   }

   CR = (gpio_pin < 8) ? &(port->CRL) : &(port->CRH);

   tmp = *CR;
   tmp &= POS_MASK(shift);
   tmp |= mode << shift;

   *CR = tmp;

}

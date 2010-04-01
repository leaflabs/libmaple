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
 *  @file wiring.c
 *
 *  @brief
 */

#include "wiring.h"
#include "rcc.h"
#include "systick.h"
#include "gpio.h"

void nvic_init(void);

void init(void) {
   rcc_init();
   nvic_init();
   systick_init();
   gpio_init();
   adc_init();
   timer_init(1, 1);
   timer_init(2, 1);
   timer_init(3, 1);
   timer_init(4, 1);
}

void nvic_init(void) {
#ifdef VECT_TAB_ROM
   nvic_set_vector_table(USER_ADDR_ROM, 0x0);
#warning writing to ROM
#elif defined VECT_TAB_RAM
   nvic_set_vector_table(USER_ADDR_RAM, 0x0);
#warning writing to RAM
#else // VECT_TAB_BASE
   /* Set the Vector Table base location at 0x08000000 */
   nvic_set_vector_table(((uint32)0x08000000), 0x0);
#endif
}

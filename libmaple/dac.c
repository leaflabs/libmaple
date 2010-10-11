/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
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

#include "libmaple.h"
#include "rcc.h"
#include "gpio.h"
#include "dac.h"

/**
 * @brief DAC peripheral routines.
 */

/* Only one, so global to this file */
DAC_Map *dac = (DAC_Map*)(DAC_BASE);

/* This numbering follows the registers (1-indexed) */
#define DAC_CHA     1
#define DAC_CHB     2

/* Sets up the DAC peripheral */
void dac_init(void) {
    /* First turn on the clock */
    rcc_clk_enable(RCC_DAC);

    /* Then setup ANALOG mode on PA4 and PA5 */
    gpio_set_mode(GPIOA_BASE,  4, CNF_INPUT_ANALOG);
    gpio_set_mode(GPIOA_BASE,  5, CNF_INPUT_ANALOG);

    /* Then do register stuff.  Default does no triggering, and
     * buffered output, so all good. */
    dac->CR |= DAC_CR_EN1;
    dac->CR |= DAC_CR_EN2;
}

void dac_write(uint8 chan, uint16 val) {
    switch(chan) {
    case DAC_CHA:
        dac->DHR12R1 = 0x0FFF & val;
        break;
    case DAC_CHB:
        dac->DHR12R2 = 0x0FFF & val;
        break;
    default:
        ASSERT(0);  // can't happen
    }
}

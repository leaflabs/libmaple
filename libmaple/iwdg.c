/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Michael Hope.
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
 *  @file iwdg.c
 *
 *  @brief Independent watchdog support
 */

#include "libmaple.h"
#include "iwdg.h"

#define IWDG_UNLOCK   0x5555
#define IWDG_START    0xCCCC
#define IWDG_FEED     0xAAAA

/**
 *  @brief Initialise and start the watchdog
 *
 *  The prescaler and reload set the timeout.  A prescaler of 3 divides
 *  the 40 kHz clock by 32 and gives roughly 1 ms per reload.
 */
void iwdg_init(uint8 prescaler, uint16 reload) {
    __write(IWDG_KR, IWDG_UNLOCK);
    __write(IWDG_PR, prescaler);
    __write(IWDG_RLR, reload);

    /* Start things off */
    __write(IWDG_KR, IWDG_START);
    __write(IWDG_KR, IWDG_FEED);
}

void iwdg_feed(void) {
    __write(IWDG_KR, IWDG_FEED);
}

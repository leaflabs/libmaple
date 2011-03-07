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

/**
 * @brief
 */

#include "libmaple.h"
#include "rcc.h"
#include "gpio.h"
#include "fsmc.h"

/* Sets up the FSMC peripheral to use the SRAM chip on the maple
 * native as an external segment of system memory space.  This
 * implementation is for the IS62WV51216BLL 8mbit chip (55ns
 * timing) */
void fsmc_native_sram_init(void) {
    FSMC_Bank *bank;

    /* First we setup all the GPIO pins. */
    /* Data lines... */
    gpio_set_mode(GPIOD_BASE,  0, MODE_AF_OUTPUT_PP); /* D2 */
    gpio_set_mode(GPIOD_BASE,  1, MODE_AF_OUTPUT_PP); /* D3 */
    gpio_set_mode(GPIOD_BASE,  8, MODE_AF_OUTPUT_PP); /* D13 */
    gpio_set_mode(GPIOD_BASE,  9, MODE_AF_OUTPUT_PP); /* D14 */
    gpio_set_mode(GPIOD_BASE, 10, MODE_AF_OUTPUT_PP); /* D15 */
    gpio_set_mode(GPIOD_BASE, 14, MODE_AF_OUTPUT_PP); /* D0 */
    gpio_set_mode(GPIOD_BASE, 15, MODE_AF_OUTPUT_PP); /* D1 */
    gpio_set_mode(GPIOE_BASE,  7, MODE_AF_OUTPUT_PP); /* D4 */
    gpio_set_mode(GPIOE_BASE,  8, MODE_AF_OUTPUT_PP); /* D5 */
    gpio_set_mode(GPIOE_BASE,  9, MODE_AF_OUTPUT_PP); /* D6 */
    gpio_set_mode(GPIOE_BASE, 10, MODE_AF_OUTPUT_PP); /* D7 */
    gpio_set_mode(GPIOE_BASE, 11, MODE_AF_OUTPUT_PP); /* D8 */
    gpio_set_mode(GPIOE_BASE, 12, MODE_AF_OUTPUT_PP); /* D9 */
    gpio_set_mode(GPIOE_BASE, 13, MODE_AF_OUTPUT_PP); /* D10 */
    gpio_set_mode(GPIOE_BASE, 14, MODE_AF_OUTPUT_PP); /* D11 */
    gpio_set_mode(GPIOE_BASE, 15, MODE_AF_OUTPUT_PP); /* D12 */

    /* Address lines... */
    gpio_set_mode(GPIOD_BASE, 11, MODE_AF_OUTPUT_PP); /* A16 */
    gpio_set_mode(GPIOD_BASE, 12, MODE_AF_OUTPUT_PP); /* A17 */
    gpio_set_mode(GPIOD_BASE, 13, MODE_AF_OUTPUT_PP); /* A18 */
    gpio_set_mode(GPIOF_BASE,  0, MODE_AF_OUTPUT_PP); /* A0 */
    gpio_set_mode(GPIOF_BASE,  1, MODE_AF_OUTPUT_PP); /* A1 */
    gpio_set_mode(GPIOF_BASE,  2, MODE_AF_OUTPUT_PP); /* A2 */
    gpio_set_mode(GPIOF_BASE,  3, MODE_AF_OUTPUT_PP); /* A3 */
    gpio_set_mode(GPIOF_BASE,  4, MODE_AF_OUTPUT_PP); /* A4 */
    gpio_set_mode(GPIOF_BASE,  5, MODE_AF_OUTPUT_PP); /* A5 */
    gpio_set_mode(GPIOF_BASE, 12, MODE_AF_OUTPUT_PP); /* A6 */
    gpio_set_mode(GPIOF_BASE, 13, MODE_AF_OUTPUT_PP); /* A7 */
    gpio_set_mode(GPIOF_BASE, 14, MODE_AF_OUTPUT_PP); /* A8 */
    gpio_set_mode(GPIOF_BASE, 15, MODE_AF_OUTPUT_PP); /* A9 */
    gpio_set_mode(GPIOG_BASE,  0, MODE_AF_OUTPUT_PP); /* A10 */
    gpio_set_mode(GPIOG_BASE,  1, MODE_AF_OUTPUT_PP); /* A11 */
    gpio_set_mode(GPIOG_BASE,  2, MODE_AF_OUTPUT_PP); /* A12 */
    gpio_set_mode(GPIOG_BASE,  3, MODE_AF_OUTPUT_PP); /* A13 */
    gpio_set_mode(GPIOG_BASE,  4, MODE_AF_OUTPUT_PP); /* A14 */
    gpio_set_mode(GPIOG_BASE,  5, MODE_AF_OUTPUT_PP); /* A15 */

    /* And control lines... */
    gpio_set_mode(GPIOD_BASE,  4, MODE_AF_OUTPUT_PP); /* NOE */
    gpio_set_mode(GPIOD_BASE,  5, MODE_AF_OUTPUT_PP); /* NWE */

    gpio_set_mode(GPIOD_BASE,  7, MODE_AF_OUTPUT_PP); /* NE1 */
    gpio_set_mode(GPIOG_BASE,  9, MODE_AF_OUTPUT_PP); /* NE2 */
    gpio_set_mode(GPIOG_BASE, 10, MODE_AF_OUTPUT_PP); /* NE3 */
    gpio_set_mode(GPIOG_BASE, 12, MODE_AF_OUTPUT_PP); /* NE4 */

    gpio_set_mode(GPIOE_BASE,  0, MODE_AF_OUTPUT_PP); /* NBL0 */
    gpio_set_mode(GPIOE_BASE,  1, MODE_AF_OUTPUT_PP); /* NBL1 */

    /* Next enable the clock */
    rcc_clk_enable(RCC_FSMC);

    /* Then we configure channel 1 the FSMC SRAM peripheral (all SRAM
     * channels are in "Bank 1" of the FSMC) */
    bank = (FSMC_Bank*)(FSMC1_BASE);

    /* FIXME replace with macros from fsmc.h */
    bank->BCR = (1 << 12) | (1 << 4) | 1;
    bank->BTR = (3 << 8);

    /* (FSMC_BWTR3 not used for this simple configuration.) */
}


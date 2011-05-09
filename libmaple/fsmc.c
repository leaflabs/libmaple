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

/* These values determined for a particular SRAM chip by following the
 * calculations in the ST FSMC application note. */
#define FSMC_ADDSET 0x0
#define FSMC_DATAST 0x3

/* Sets up the FSMC peripheral to use the SRAM chip on the maple
 * native as an external segment of system memory space.  This
 * implementation is for the IS62WV51216BLL 8mbit chip (55ns
 * timing) */
void fsmc_native_sram_init(void) {
    FSMC_Bank *bank;

    /* First we setup all the GPIO pins. */
    /* Data lines... */
    gpio_set_mode(GPIOD_BASE,  0, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE,  1, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE,  8, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE,  9, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE, 10, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE, 14, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE, 15, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE,  7, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE,  8, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE,  9, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE, 10, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE, 11, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE, 12, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE, 13, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE, 14, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOE_BASE, 15, MODE_AF_OUTPUT_PP);

    /* Address lines... */
    gpio_set_mode(GPIOD_BASE, 11, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE, 12, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOD_BASE, 13, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE,  0, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE,  1, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE,  2, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE,  3, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE,  4, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE,  5, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE, 12, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE, 13, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE, 14, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOF_BASE, 15, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOG_BASE,  0, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOG_BASE,  1, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOG_BASE,  2, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOG_BASE,  3, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOG_BASE,  4, MODE_AF_OUTPUT_PP);
    gpio_set_mode(GPIOG_BASE,  5, MODE_AF_OUTPUT_PP);

    /* And control lines... */
    gpio_set_mode(GPIOD_BASE,  4, MODE_AF_OUTPUT_PP);   // NOE
    gpio_set_mode(GPIOD_BASE,  5, MODE_AF_OUTPUT_PP);   // NWE

    gpio_set_mode(GPIOD_BASE,  7, MODE_AF_OUTPUT_PP);   // NE1
    gpio_set_mode(GPIOG_BASE,  9, MODE_AF_OUTPUT_PP);   // NE2
    gpio_set_mode(GPIOG_BASE, 10, MODE_AF_OUTPUT_PP);   // NE3
    gpio_set_mode(GPIOG_BASE, 12, MODE_AF_OUTPUT_PP);   // NE4

    gpio_set_mode(GPIOE_BASE,  0, MODE_AF_OUTPUT_PP);   // NBL0
    gpio_set_mode(GPIOE_BASE,  1, MODE_AF_OUTPUT_PP);   // NBL1

    /* Next enable the clock */
    rcc_clk_enable(RCC_FSMC);

    /* Then we configure channel 1 the FSMC SRAM peripheral (all SRAM
     * channels are in "Bank 1" of the FSMC) */
    bank = (FSMC_Bank*)(FSMC1_BASE);

    /* Everything else is cleared (BCR1) */
    bank->BCR = 0x0000;

    /* Memory type is SRAM */
    bank->BCR &= ~(FSMC_BCR_MTYP);  // '00'

    /* Databus width is 16bits */
    bank->BCR &= ~(FSMC_BCR_MWID);
    bank->BCR |= 0x1 << 4;          // '01'

    /* Memory is nonmultiplexed */
    bank->BCR &= ~(FSMC_BCR_MUXEN); // '0'

    /* Need write enable to write to the chip */
    bank->BCR |= FSMC_BCR_WREN;

    /* Set ADDSET */
    bank->BTR &= ~(FSMC_BTR_ADDSET);
    bank->BTR |= (FSMC_BTR_ADDSET | FSMC_ADDSET);

    /* Set DATAST */
    bank->BTR &= ~(FSMC_BTR_DATAST);
    bank->BTR |= (FSMC_BTR_DATAST | (FSMC_DATAST << 8));

    /* Enable channel 1 */
    bank->BCR |= FSMC_BCR_MBKEN;    // '1'

    /* (FSMC_BWTR3 not used for this simple configuration.) */
}


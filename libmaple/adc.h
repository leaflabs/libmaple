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
 *  @file adc.h
 *
 *  @brief ADC prototypes and defines
 */

#ifndef _ADC_H_
#define _ADC_H_
#include "util.h"

#ifdef __cplusplus
extern "C"{
#endif

/* Notes:
 * The maximum input impedance on each channel MUST be below .4kohms,
 * or face the wrath of incorrect readings...
 * This can be changed at the expense of sample time... see datasheet
 *
 * Need to up the sample time if otherwise... see datasheet */

/* We'll only use ADC1 for now...  */
#define ADC_BASE                 0x40012400
#define ADC_SR                   *(volatile uint32*)(ADC_BASE + 0)
#define ADC_CR1                  *(volatile uint32*)(ADC_BASE + 0x4)
#define ADC_CR2                  *(volatile uint32*)(ADC_BASE + 0x8)
#define ADC_SMPR1                *(volatile uint32*)(ADC_BASE + 0xC)
#define ADC_SMPR2                *(volatile uint32*)(ADC_BASE + 0x10)
#define ADC_SQR1                 *(volatile uint32*)(ADC_BASE + 0x2C)
#define ADC_SQR3                 *(volatile uint32*)(ADC_BASE + 0x34)
#define ADC_DR                   *(volatile uint32*)(ADC_BASE + 0x4C)

#define CR2_EXTSEL_SWSTART       (0xE << 16)
#define CR2_RSTCAL               (BIT(3))
#define CR2_EXTTRIG              (BIT(20))

/* Bit banded bits  */
#define CR2_ADON_BIT             *(volatile uint32*)(BITBAND_PERI(ADC_BASE+0x8, 0))
#define CR2_CAL_BIT              *(volatile uint32*)(BITBAND_PERI(ADC_BASE+0x8, 2))
#define CR2_RSTCAL_BIT           *(volatile uint32*)(BITBAND_PERI(ADC_BASE+0x8, 3))
#define CR2_SWSTART_BIT          *(volatile uint32*)(BITBAND_PERI(ADC_BASE+0x8 + 2, 6))
#define SR_EOC_BIT               *(volatile uint32*)(BITBAND_PERI(ADC_BASE+0, 1))

#define NR_ANALOG_PINS           29

/* Initialize ADC1 to do one-shot conversions  */
void adc_init(void);
void adc_disable(void);

/* Perform a single conversion on ADC[0-16],
 * PRECONDITIONS:
 *   adc initialized */
static inline int adc_read(int channel) {
    /* Set channel  */
    ADC_SQR3 = channel;

    /* Start the conversion  */
    CR2_SWSTART_BIT = 1;

    /* Wait for it to finish  */
    while(SR_EOC_BIT == 0)
        ;

    return ADC_DR;
}



#ifdef __cplusplus
} // extern "C"
#endif
#endif


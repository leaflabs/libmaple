/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created: 12/18/09 02:35:10
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file adc.h
 *
 *  @brief ADC prototypes and defines
 */

#ifndef _ADC_H_
#define _ADC_H_
#include <inttypes.h>
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
#define ADC_SR                   *(volatile uint32_t*)(ADC_BASE + 0)
#define ADC_CR1                  *(volatile uint32_t*)(ADC_BASE + 0x4)
#define ADC_CR2                  *(volatile uint32_t*)(ADC_BASE + 0x8)
#define ADC_SMPR1                *(volatile uint32_t*)(ADC_BASE + 0xC)
#define ADC_SMPR2                *(volatile uint32_t*)(ADC_BASE + 0x10)
#define ADC_SQR1                 *(volatile uint32_t*)(ADC_BASE + 0x2C)
#define ADC_SQR3                 *(volatile uint32_t*)(ADC_BASE + 0x34)
#define ADC_DR                   *(volatile uint32_t*)(ADC_BASE + 0x4C)

#define CR2_EXTSEL_SWSTART       (0xE << 16)
#define CR2_RSTCAL               (BIT(3))
#define CR2_EXTTRIG              (BIT(20))

/* Bit banded bits  */
#define CR2_ADON_BIT             *(volatile uint32_t*)(BITBAND_PERI(ADC_BASE+0x8, 0))
#define CR2_CAL_BIT              *(volatile uint32_t*)(BITBAND_PERI(ADC_BASE+0x8, 2))
#define CR2_RSTCAL_BIT           *(volatile uint32_t*)(BITBAND_PERI(ADC_BASE+0x8, 3))
#define CR2_SWSTART_BIT          *(volatile uint32_t*)(BITBAND_PERI(ADC_BASE+0x8 + 2, 6))
#define SR_EOC_BIT               *(volatile uint32_t*)(BITBAND_PERI(ADC_BASE+0, 1))

#define NR_ANALOG_PINS           16

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


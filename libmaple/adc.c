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
 *  Created: 12/18/09 02:34:47
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file adc.c
 *
 *  @brief Analog to digital converter routines
 */

#include "stm32f10x_rcc.h"
#include "adc.h"
#include <stdio.h>
#include <inttypes.h>

/* The ADC input clock is generated from PCLK2/APB2 divided by a prescaler
 * and it must not exceed 14MHz.
 *
 * ADC1 and ADC2 are clocked by APB2
 *
 * 1) Power on by setting ADON in ADC_CR2
 * Conversion starts when ADON is set for a second time after some
 * time t > t_stab.
 *
 * Up to 16 selected conversion must be selected in ADC_SQRx
 *
 * Single conversion mode:
 * Set the ADON bit in the ADC_CR2 register
 * Once the conversion is complete:
 *  Converted data is stored in ADC_DR
 *  EOC flag is set
 *  Interrupt is generated if EOCIE is set
 *
 * Calibration:
 * Calibration is started by setting the CAL bit in the ADC_CR2 register.
 * Once calibration is over, the CAL bit is reset by hardware and normal
 * conversion can be performed. Calibrate at power-on.
 *
 * ALIGN in ADC_CR2 selects the alignment of data
 *
 * IMPORTANT: maximum external impedance must be below 0.4kOhms for 1.5
 * sample conversion time.
 *
 * At 55.5 cycles/sample, the external input impedance < 50kOhms*/

void adc_init(void) {
    /* PCLK2 is the APB2 clock */
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    /* Enable ADC1 clock so that we can talk to it */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* Put everything back to power-on defaults */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);

    ADC_CR1  = 0;
    ADC_CR2  = CR2_EXTSEL_SWSTART | CR2_EXTTRIG;  // Software triggers conversions
    ADC_SQR1 = 0;

    /* Up the sample conversion time to 55.5 cycles/sec, see note above  */
    /* TODO: fix magic numbers  */
    ADC_SMPR1 = 0xB6DB6D;
    ADC_SMPR2 = 0x2DB6DB6D;

    /* Enable the ADC  */
    CR2_ADON_BIT = 1;

    /* Reset the calibration registers and then perform a reset  */
    CR2_RSTCAL_BIT = 1;
    while(CR2_RSTCAL_BIT)
        ;

    CR2_CAL_BIT = 1;
    while(CR2_CAL_BIT)
        ;
}


void adc_disable(void) {
    CR2_ADON_BIT = 0;
}

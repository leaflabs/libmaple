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
 *  @file adc.c
 *
 *  @brief Analog to digital converter routines
 */

#include "libmaple.h"
#include "rcc.h"
#include "adc.h"

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
   rcc_set_adc_prescaler(PCLK2_DIV_2);
   rcc_enable_clk_adc1();
   rcc_reset_adc1();

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

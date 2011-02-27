/******************************************************************************
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
 *****************************************************************************/

/**
 * @brief Analog to digital converter routines
 *
 * IMPORTANT: maximum external impedance must be below 0.4kOhms for 1.5
 * sample conversion time.
 *
 * At 55.5 cycles/sample, the external input impedance < 50kOhms.
 *
 * See stm32 manual RM008 for how to calculate this.
 */

#include "libmaple.h"
#include "rcc.h"
#include "adc.h"

adc_dev adc1 = {
    .regs   = (adc_reg_map*)ADC1_BASE,
    .clk_id = RCC_ADC1
};
const adc_dev *ADC1 = &adc1;

adc_dev adc2 = {
    .regs   = (adc_reg_map*)ADC2_BASE,
    .clk_id = RCC_ADC2
};
const adc_dev *ADC2 = &adc2;

#if NR_ADCS >= 3
adc_dev adc3 = {
    .regs   = (adc_reg_map*)ADC3_BASE,
    .clk_id = RCC_ADC3
};
const adc_dev *ADC3 = &adc3;
#endif

static void adc_calibrate(adc_reg_map *regs);

/**
 * @brief Initialize an ADC peripheral. Only supports software triggered
 * conversions.
 * @param dev ADC peripheral to initialize
 * @param flags unused
 */
void adc_init(const adc_dev *dev, uint32 flags) {
    /* Spin up the clocks */
    rcc_set_prescaler(RCC_PRESCALER_ADC, RCC_ADCPRE_PCLK_DIV_6);
    rcc_clk_enable(dev->clk_id);
    rcc_reset_dev(dev->clk_id);

    /* Software triggers conversions, conversion on external events */
    adc_set_extsel(dev->regs, 7);
    adc_set_exttrig(dev->regs, 1);

    /* Enable the ADC */
    adc_enable(dev->regs);

    /* Calibrate ADC */
    adc_calibrate(dev->regs);
}

/**
 * @brief Set external event select for regular group
 * @param regs adc register map
 * @param trigger event to select. See ADC_CR2 EXTSEL[2:0] bits.
 */
void adc_set_extsel(adc_reg_map *regs, uint8 trigger) {
    uint32 cr2 = regs->CR2;
    cr2 &= ~ADC_CR2_EXTSEL;
    cr2 |= (trigger & 0x7) << 17;
    regs->CR2 = cr2;
}


/**
 * @brief Turn the given sample rate into values for ADC_SMPRx. Don't
 * call this during conversion.
 * @param regs adc register map
 * @param smp_rate sample rate to set
 * @see adc_smp_rate
 */
void adc_set_sample_rate(adc_reg_map *regs, adc_smp_rate smp_rate) {
    uint32 adc_smpr1_val = 0, adc_smpr2_val = 0;
    int i;
    for (i = 0; i < 10; i++) {
        if (i < 8) {
            /* ADC_SMPR1 determines sample time for channels [10,17] */
            adc_smpr1_val |= smp_rate << (i * 3);
        }
        /* ADC_SMPR2 determines sample time for channels [0,9] */
        adc_smpr2_val |= smp_rate << (i * 3);
    }
    regs->SMPR1 = adc_smpr1_val;
    regs->SMPR2 = adc_smpr2_val;
}

/**
 * @brief Calibrate an ADC peripheral
 * @param regs adc register map
 */
static void adc_calibrate(adc_reg_map *regs) {
    __io uint32 *rstcal_bit = (__io uint32*)BITBAND_PERI(&(regs->CR2), 3);
    __io uint32 *cal_bit = (__io uint32*)BITBAND_PERI(&(regs->CR2), 2);

    *rstcal_bit = 1;
    while (*rstcal_bit)
        ;

    *cal_bit = 1;
    while (*cal_bit)
        ;
}

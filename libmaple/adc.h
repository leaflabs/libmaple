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
 *  @file adc.h
 *
 *  @brief Analog-to-Digital Conversion (ADC) header.
 */

#ifndef _ADC_H_
#define _ADC_H_

#include "libmaple.h"
#include "bitband.h"
#include "rcc.h"

#ifdef __cplusplus
extern "C"{
#endif

/** ADC register map type. */
typedef struct adc_reg_map {
    __io uint32 SR;             ///< Status register
    __io uint32 CR1;            ///< Control register 1
    __io uint32 CR2;            ///< Control register 2
    __io uint32 SMPR1;          ///< Sample time register 1
    __io uint32 SMPR2;          ///< Sample time register 2
    __io uint32 JOFR1;          ///< Injected channel data offset register 1
    __io uint32 JOFR2;          ///< Injected channel data offset register 2
    __io uint32 JOFR3;          ///< Injected channel data offset register 3
    __io uint32 JOFR4;          ///< Injected channel data offset register 4
    __io uint32 HTR;            ///< Watchdog high threshold register
    __io uint32 LTR;            ///< Watchdog low threshold register
    __io uint32 SQR1;           ///< Regular sequence register 1
    __io uint32 SQR2;           ///< Regular sequence register 2
    __io uint32 SQR3;           ///< Regular sequence register 3
    __io uint32 JSQR;           ///< Injected sequence register
    __io uint32 JDR1;           ///< Injected data register 1
    __io uint32 JDR2;           ///< Injected data register 2
    __io uint32 JDR3;           ///< Injected data register 3
    __io uint32 JDR4;           ///< Injected data register 4
    __io uint32 DR;             ///< Regular data register
} adc_reg_map;

/** ADC device type. */
typedef struct adc_dev {
    adc_reg_map *regs; /**< Register map */
    rcc_clk_id clk_id; /**< RCC clock information */
} adc_dev;

/** ADC1 device. */
extern const adc_dev *ADC1;
/** ADC2 device. */
extern const adc_dev *ADC2;
#ifdef STM32_HIGH_DENSITY
/** ADC3 device. */
extern const adc_dev *ADC3;
#endif

/*
 * ADC peripheral base addresses
 */

/** ADC1 register map base pointer. */
#define ADC1_BASE               ((adc_reg_map*)0x40012400)
/** ADC2 register map base pointer. */
#define ADC2_BASE               ((adc_reg_map*)0x40012800)
/** ADC3 register map base pointer. */
#define ADC3_BASE               ((adc_reg_map*)0x40013C00)

/*
 * Register bit definitions
 */

/* Status register */
#define ADC_SR_AWD              BIT(0)
#define ADC_SR_EOC              BIT(1)
#define ADC_SR_JEOC             BIT(2)
#define ADC_SR_JSTRT            BIT(3)
#define ADC_SR_STRT             BIT(4)

/* Control register 1 */
#define ADC_CR1_AWDCH           (0x1F)
#define ADC_CR1_EOCIE           BIT(5)
#define ADC_CR1_AWDIE           BIT(6)
#define ADC_CR1_JEOCIE          BIT(7)
#define ADC_CR1_SCAN            BIT(8)
#define ADC_CR1_AWDSGL          BIT(9)
#define ADC_CR1_JAUTO           BIT(10)
#define ADC_CR1_DISCEN          BIT(11)
#define ADC_CR1_JDISCEN         BIT(12)
#define ADC_CR1_DISCNUM         (0xE000)
#define ADC_CR1_JAWDEN          BIT(22)
#define ADC_CR1_AWDEN           BIT(23)

/* Control register 2 */
#define ADC_CR2_ADON            BIT(0)
#define ADC_CR2_CONT            BIT(1)
#define ADC_CR2_CAL             BIT(2)
#define ADC_CR2_RSTCAL          BIT(3)
#define ADC_CR2_DMA             BIT(8)
#define ADC_CR2_ALIGN           BIT(11)
#define ADC_CR2_JEXTSEL         (0x7000)
#define ADC_CR2_JEXTTRIG        BIT(15)
#define ADC_CR2_EXTSEL          (0xE0000)
#define ADC_CR2_EXTTRIG         BIT(20)
#define ADC_CR2_JSWSTART        BIT(21)
#define ADC_CR2_SWSTART         BIT(22)
#define ADC_CR2_TSEREFE         BIT(23)

void adc_init(const adc_dev *dev, uint32 flags);
void adc_set_extsel(const adc_dev *dev, uint8 trigger);

/** ADC per-sample conversion times, in ADC clock cycles */
typedef enum {
    ADC_SMPR_1_5,               ///< 1.5 ADC cycles
    ADC_SMPR_7_5,               ///< 7.5 ADC cycles
    ADC_SMPR_13_5,              ///< 13.5 ADC cycles
    ADC_SMPR_28_5,              ///< 28.5 ADC cycles
    ADC_SMPR_41_5,              ///< 41.5 ADC cycles
    ADC_SMPR_55_5,              ///< 55.5 ADC cycles
    ADC_SMPR_71_5,              ///< 71.5 ADC cycles
    ADC_SMPR_239_5              ///< 239.5 ADC cycles
} adc_smp_rate;

void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate);

/**
 * @brief Perform a single synchronous software triggered conversion on a
 * channel.
 * @param dev ADC device to use for reading.
 * @param channel channel to convert
 * @return conversion result
 */
static inline uint32 adc_read(const adc_dev *dev, uint8 channel) {
    adc_reg_map *regs = dev->regs;

    /* Set target channel */
    regs->SQR3 = channel;

    /* Start the conversion */
    regs->CR2 |= ADC_CR2_SWSTART;

    /* Wait for it to finish */
    while((regs->SR & ADC_SR_EOC) == 0)
        ;

    return regs->DR;
}

/**
 * @brief Set external trigger conversion mode event for regular channels
 * @param dev    ADC device
 * @param enable If 1, conversion on external events is enabled, 0 to disable
 */
static inline void adc_set_exttrig(const adc_dev *dev, uint8 enable) {
    *bb_perip(&dev->regs->CR2, 20) = !!enable;
}

/**
 * @brief Enable an adc peripheral
 * @param dev ADC device to enable
 */
static inline void adc_enable(const adc_dev *dev) {
    *bb_perip(&dev->regs->CR2, 0) = 1;
}

/**
 * @brief Disable an ADC peripheral
 * @param dev ADC device to disable
 */
static inline void adc_disable(const adc_dev *dev) {
    *bb_perip(&dev->regs->CR2, 0) = 0;
}

/**
 * @brief Disable all ADCs
 */
static inline void adc_disable_all(void) {
    adc_disable(ADC1);
    adc_disable(ADC2);
#ifdef STM32_HIGH_DENSITY
    adc_disable(ADC3);
#endif
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

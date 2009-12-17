#include "adc.h"
#include "gpio.h"
#include "wiring.h"
#include <stdio.h>

/* Indexed by pins A[0-15]  */
uint32_t PIN_TO_ADC[NR_ANALOG_PINS] = {
    10,                     // A0/D14    ADC10
    11,                     // A1/D15    ADC11
    12,                     // A2/D16    ADC12
    13,                     // A3/D17    ADC13
    14,                     // A4/D18    ADC14
    15,                     // A5/D19    ADC15
     3,                     // A6/D0     ADC3
     2,                     // A7/D1     ADC2
     0,                     // A8/D2     ADC0
     1,                     // A9/D3     ADC1
     4,                     // A10/D10   ADC4
     7,                     // A11/D11   ADC7
     6,                     // A12/D12   ADC6
     5,                     // A13/D13   ADC5
     8,                     // A14/D26   ADC8
     9,                     // A15/D11   ADC9
};

/* Assumes that the ADC has been initialized and
 * that the pin is set to ANALOG_INPUT */
uint32_t analogRead(uint8_t pin) {
    if (pin >= NR_ANALOG_PINS)
        return 0;

    return adc_read(PIN_TO_ADC[pin]);
}

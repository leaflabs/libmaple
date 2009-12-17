#include "wiring.h"
#include "timers.h"
#include "gpio.h"
#include "pwm.h"

#define NOT_A_TIMER 0

static const TimerCCR PIN_TO_TIMER[NR_MAPLE_PINS] = {
    TIMER2_CH4_CCR,                     // D0/A6
    TIMER2_CH3_CCR,                     // D1/A7
    TIMER2_CH1_CCR,                     // D2/A8
    TIMER2_CH2_CCR,                     // D3/A9
    NOT_A_TIMER,                        // D4
    TIMER4_CH1_CCR,                     // D5
    TIMER1_CH1_CCR,                     // D6
    TIMER1_CH2_CCR,                     // D7
    TIMER1_CH3_CCR,                     // D8
    TIMER4_CH2_CCR,                     // D9
    NOT_A_TIMER,                        // D10/A10
    TIMER3_CH2_CCR,                     // D11/A11
    TIMER3_CH1_CCR,                     // D12/A12
    NOT_A_TIMER,                        // D13/A13
};

void pwmWrite(uint8_t pin, uint16_t duty_cycle) {
    TimerCCR ccr;

    if (pin >= NR_MAPLE_PINS) {
        return;
    }

    ccr = PIN_TO_TIMER[pin];

    if (ccr == NOT_A_TIMER)
        return;

    timer_pwm_write_ccr(ccr, duty_cycle);
}



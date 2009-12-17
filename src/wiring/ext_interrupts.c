#include "wiring.h"
#include "exti.h"
#include "ext_interrupts.h"

typedef struct ExtiInfo {
    uint8_t channel;
    uint8_t port;
} ExtiInfo;

static ExtiInfo PIN_TO_EXTI_CHANNEL[NR_MAPLE_PINS] = {
    {EXTI3,  EXTI_CONFIG_PORTA},      // D0/PA3
    {EXTI2,  EXTI_CONFIG_PORTA},      // D1/PA2
    {EXTI0,  EXTI_CONFIG_PORTA},      // D2/PA0
    {EXTI1,  EXTI_CONFIG_PORTA},      // D3/PA1
    {EXTI5,  EXTI_CONFIG_PORTB},      // D4/PB5
    {EXTI6,  EXTI_CONFIG_PORTB},      // D5/PB6
    {EXTI8,  EXTI_CONFIG_PORTA},      // D6/PA8
    {EXTI9,  EXTI_CONFIG_PORTA},      // D7/PA9
    {EXTI10, EXTI_CONFIG_PORTA},      // D8/PA10
    {EXTI7,  EXTI_CONFIG_PORTB},      // D9/PB7
    {EXTI4,  EXTI_CONFIG_PORTA},      // D10/PA4
    {EXTI7,  EXTI_CONFIG_PORTA},      // D11/PA7
    {EXTI6,  EXTI_CONFIG_PORTA},      // D12/PA6
    {EXTI5,  EXTI_CONFIG_PORTA},      // D13/PA5
};



/**
 *  @brief Attach an interrupt handler to be triggered on a given
 *  transition on the pin. Runs in interrupt context
 *
 *  @param[in] pin Maple pin number
 *  @param[in] handler Function to run upon external interrupt trigger.
 *  @param[in] mode Type of transition to trigger on, eg falling, rising, etc.
 *
 *  @sideeffect Registers a handler
 */
int attachInterrupt(uint8_t pin, void (*handler)(void), uint8_t mode) {
    /* Parameter checking  */
    if (pin >= NR_MAPLE_PINS) {
        return EXT_INTERRUPT_INVALID_PIN;
    }

    if (!handler) {
        return EXT_INTERRUPT_INVALID_FUNCTION;
    }

    if (!(mode < NR_EXTI_MODES)) {
        return EXT_INTERRUPT_INVALID_MODE;
    }

    exti_attach_interrupt(PIN_TO_EXTI_CHANNEL[pin].channel, 
                          PIN_TO_EXTI_CHANNEL[pin].port,
                          handler, mode);
}

int detachInterrupt(uint8_t pin) {
    if (!(pin < NR_MAPLE_PINS)) {
        return EXT_INTERRUPT_INVALID_PIN;
    }

    exti_detach_interrupt(PIN_TO_EXTI_CHANNEL[pin].channel);
}


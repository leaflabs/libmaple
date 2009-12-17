#include "gpio.h"
#include "wiring.h"
#include "util.h"

typedef struct PinGPIOMapping {
    GPIO_Port *port;
    uint32_t pin;
} PinGPIOMapping;

static const PinGPIOMapping PIN_TO_GPIO[NR_MAPLE_PINS] = {
    {_GPIOA_BASE,  3},                          // D0/PA3
    {_GPIOA_BASE,  2},                          // D1/PA2
    {_GPIOA_BASE,  0},                          // D2/PA0
    {_GPIOA_BASE,  1},                          // D3/PA1
    {_GPIOB_BASE,  5},                          // D4/PB5
    {_GPIOB_BASE,  6},                          // D5/PB6
    {_GPIOA_BASE,  8},                          // D6/PA8
    {_GPIOA_BASE,  9},                          // D7/PA9
    {_GPIOA_BASE, 10},                          // D8/PA10
    {_GPIOB_BASE,  7},                          // D9/PB7
    {_GPIOA_BASE,  4},                          // D10/PA4
    {_GPIOA_BASE,  7},                          // D11/PA7
    {_GPIOA_BASE,  6},                          // D12/PA6
    {_GPIOA_BASE,  5},                          // D13/PA5
#if 0
    {_GPIOC_BASE,  0},                          // D14/A0/PC0
    {_GPIOC_BASE,  1},                          // D15/A1/PC1
    {_GPIOC_BASE,  2},                          // D16/A2/PC2
    {_GPIOC_BASE,  3},                          // D17/A3/PC3
    {_GPIOC_BASE,  4},                          // D18/A4/PC4
    {_GPIOC_BASE,  5},                          // D19/A5/PC5
#endif
};

void pinMode(uint8_t pin, uint8_t mode) {
    if (pin >= NR_MAPLE_PINS)
        return;

    gpio_set_mode(PIN_TO_GPIO[pin].port, PIN_TO_GPIO[pin].pin, mode);
}


uint32_t digitalRead(uint8_t pin) {
    if (pin >= NR_MAPLE_PINS)
        return 0;

    return (PIN_TO_GPIO[pin].port->IDR & BIT(PIN_TO_GPIO[pin].pin)) ? 1 : 0;
}

void digitalWrite(uint8_t pin, uint8_t val) {
    if (pin >= NR_MAPLE_PINS)
        return;

    gpio_write_bit(PIN_TO_GPIO[pin].port, PIN_TO_GPIO[pin].pin, val);
}

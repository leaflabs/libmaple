#ifndef _GPIO_H
#define _GPIO_H

#include <inttypes.h>
#include "util.h"


/* Each of the GPIO port bits can be in the following modes (STM32 138/995):
 *      Input floating
 *      Input pull-up
 *      Input pull-down
 *      Analog Input
 *      Output open-drain
 *      Output push-pull
 *      Alternate function push-pull
 *      Alternate function open-drain 
 *
 * - After reset, the alternate functions are not active and IO prts
 * are set to Input Floating mode */

#define _GPIOA_BASE               (GPIO_Port*)0x40010800
#define _GPIOB_BASE               (GPIO_Port*)0x40010C00
#define _GPIOC_BASE               (GPIO_Port*)0x40011000
#define _GPIOD_BASE               (GPIO_Port*)0x40011400

/* Pin modes are set by [CNFx[1:0] : MODEx[1:0]] */
#define GPIO_SPEED_50MHZ            (0x3) // Max output speed 50 MHz
#define GPIO_MODE_OUTPUT_PP         ((0x00 << 2) | GPIO_SPEED_50MHZ)
#define GPIO_MODE_OUTPUT_OD         ((0x01 << 2) | GPIO_SPEED_50MHZ)

#define GPIO_MODE_AF_OUTPUT_PP      ((0x02 << 2) | GPIO_SPEED_50MHZ)
#define GPIO_MODE_AF_OUTPUT_OD      ((0x03 << 2) | GPIO_SPEED_50MHZ)

/* Note: mode bits must be set to zero for input mode  */
#define GPIO_MODE_INPUT_ANALOG      (0x00 << 2)
#define GPIO_MODE_INPUT_FLOATING    (0x01 << 2)
#define GPIO_MODE_INPUT_PD          (0x02 << 2)
#define GPIO_MODE_INPUT_PU          (0x02 << 2)

#define INPUT_ANALOG                GPIO_MODE_INPUT_ANALOG
#define INPUT_DIGITAL               GPIO_MODE_INPUT_FLOATING
#define INPUT_FLOATING              GPIO_MODE_INPUT_FLOATING
#define INPUT_PULLDOWN              GPIO_MODE_INPUT_PD
#define INPUT_PULLUP                GPIO_MODE_INPUT_PU
#define INPUT                       GPIO_MODE_INPUT_FLOATING
#define OUTPUT                      GPIO_MODE_OUTPUT_PP

typedef struct {
    volatile uint32_t CRL;      // Port configuration register low
    volatile uint32_t CRH;      // Port configuration register high
    volatile uint32_t IDR;      // Port input data register
    volatile uint32_t ODR;      // Port output data register
    volatile uint32_t BSRR;     // Port bit set/reset register
    volatile uint32_t BRR;      // Port bit reset register
    volatile uint32_t LCKR;     // Port configuration lock register
} GPIO_Port;

typedef volatile uint32_t* GPIOReg;

#define POS_MASK(shift) (~(0xF << shift))
#define POS(val)        (val << 2)

#ifdef __cplusplus
extern "C"{
#endif

void gpio_init(void);

static inline void gpio_set_mode(GPIO_Port* port, uint8_t gpio_pin, uint8_t mode) {
    uint32_t tmp;
    uint32_t shift = POS(gpio_pin % 8);
    GPIOReg CR;

    ASSERT(port);
    ASSERT(gpio_pin < 16);

    CR = (gpio_pin < 8) ? &(port->CRL) : &(port->CRH);

    tmp = *CR;
    tmp &= POS_MASK(shift);
    tmp |= mode << shift;

    *CR = tmp;
}

static inline void gpio_write_bit(GPIO_Port *port, uint8_t gpio_pin, uint8_t val) {
    if (val){
        port->BSRR = BIT(gpio_pin);
    } else {
        port->BRR = BIT(gpio_pin);
    }
}

#ifdef __cplusplus
} // extern "C"
#endif


#endif


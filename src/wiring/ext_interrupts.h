#ifndef _EXT_INTERRUPTS_H_
#define _EXT_INTERRUPTS_H_

#include "exti.h"

#define RISING  EXTI_RISING
#define FALLING EXTI_FALLING
#define CHANGE  EXTI_RISING_FALLING


enum ExtInterruptError {
    EXT_INTERRUPT_INVALID_PIN =      (-1),
    EXT_INTERRUPT_INVALID_FUNCTION = (-2),
    EXT_INTERRUPT_INVALID_MODE =     (-3),

};

#ifdef __cplusplus
extern "C"{
#endif

int attachInterrupt(uint8_t, void ((*)(void)), uint8_t);
int detachInterrupt(uint8_t);

#ifdef __cplusplus
}
#endif


#endif


#ifndef _TIME_H
#define _TIME_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C"{
#endif
/* Returns time since boot in milliseconds  */
uint32_t millis(void);

/* Time in microseconds since boot  */
uint32_t micros(void);

/* Delay for ms milliseconds  */
void delay(unsigned long ms);

/* Delay for us microseconds  */
void delayMicroseconds(uint32_t us);

#ifdef __cplusplus
} // extern "C"
#endif


#endif


#ifndef _WIRING_H_
#define _WIRING_H_

#include "libmaple.h"
#include "timers.h"
#include "io.h"
#include "binary.h"
#include "bits.h"
#include "time.h"
#include "pwm.h"
#include "ext_interrupts.h"

#ifdef __cplusplus
extern "C"{
#endif


#define MAPLE 1
#define NR_MAPLE_PINS   39 // temporary

#define HIGH 0x1
#define LOW  0x0

#define true 0x1
#define false 0x0

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define USER_ADDR_ROM 0x08005000
#define USER_ADDR_RAM 0x20000C00

#define lowByte(w) ((w) & 0xff)
#define highByte(w) ((w) >> 8)
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(b) (1UL << (b))


typedef uint8 boolean;
typedef uint8 byte;

void init(void);
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, byte val);


#ifdef __cplusplus
} // extern "C"
#endif




#endif


/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created: 12/18/09 02:41:40
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file time.h
 *
 *  @brief 
 */

#ifndef _TIME_H
#define _TIME_H

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

#if 0
static inline void delay_us(uint32 us) {
    us *= 12;
    asm volatile("mov  r0, %[us]        \n\t"
                 "subs r0, #2 \n\t"
"1:                                    \n\t"
                  "subs r0, r0, #1           \n\t"
                  "bne 1b"
                 :
                 : [us] "r" (us)
                 : "r0", "cc");

}
#endif
#ifdef __cplusplus
} // extern "C"
#endif


#endif


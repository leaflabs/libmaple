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
 *  Created: 12/18/09 02:40:09
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file ext_interrupts.h
 *
 *  @brief External interrupt wiring prototypes and types
 */

#ifndef _EXT_INTERRUPTS_H_
#define _EXT_INTERRUPTS_H_

typedef enum ExtInterruptTriggerMode {
    RISING,
    FALLING,
    CHANGE
} ExtInterruptTriggerMode;


enum ExtInterruptError {
    EXT_INTERRUPT_INVALID_PIN =      (-1),
    EXT_INTERRUPT_INVALID_FUNCTION = (-2),
    EXT_INTERRUPT_INVALID_MODE =     (-3),

};

#ifdef __cplusplus
extern "C"{
#endif

int attachInterrupt(uint8_t pin, voidFuncPtr, ExtInterruptTriggerMode mode);
int detachInterrupt(uint8_t pin);

#ifdef __cplusplus
}
#endif


#endif


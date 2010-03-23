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
 *  Created: 03/23/10 01:40:50
 *  Copyright (c) 2010 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file example_main_blinky.cpp
 *
 *  @brief Example main.cpp. Blinks the LED, pin 13
 */

#ifndef _EXAMPLE_MAIN_BLINKY_H_
#define _EXAMPLE_MAIN_BLINKY_H_

#endif
#include "wiring.h"
#include "HardwareSerial.h"
#include "wiring_math.h"
#include "HardwareUsb.h"
#include "usb.h"

#define TEST_PIN 13

void setup() {
    pinMode(TEST_PIN, OUTPUT);
}

int toggle = 1;

void loop() {
    digitalWrite(TEST_PIN, toggle);
    toggle ^= 1;
    delay(100);
}

int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}

/* Required for C++ hackery */
/* TODO: This really shouldn't go here... move it later
 * */
extern "C" void __cxa_pure_virtual(void) {
    while(1)
        ;
}

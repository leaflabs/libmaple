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
 *  Created: 12/19/09 05:45:37 EST
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file HardwareSerial.h
 *
 *  @brief 
 */

#ifndef _HARDWARESERIAL_H_
#define _HARDWARESERIAL_H_

#include "Print.h"

class HardwareSerial : public Print {
    private:
        uint8 usartNum;
    public:
        HardwareSerial(uint8_t);
        void begin(uint32_t);
        uint32 available(void);
        uint8_t read(void);
        void flush(void);
        virtual void write(unsigned char);
        using Print::write;
};

extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;
#endif


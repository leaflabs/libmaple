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
 * ****************************************************************************/

/**
 *  @file HardwareUsb.h
 *
 *  @brief Wiring like serial api to USB virtual COM
 */

#ifndef _HARDWAREUSB_H_
#define _HARDWAREUSB_H_

#include "Print.h"
#include "bootVect.h"
#include "usb.h"

class HardwareUsb : public Print {
    private:
        BootVectTable* mapleVectTable;
	static void usb_rx_cb(void);
	static void usb_tx_cb(void);
	unsigned char rx_buffer[USB_SERIAL_BUF_SIZE];
	int8_t rx_buffer_offset_out;
	int8_t rx_buffer_offset_in;
    public:
        HardwareUsb(void);
	void begin();
	uint8_t available(void);
	uint8_t read(void);
	void flush(void);
	virtual void write(unsigned char);
	using Print::write;
};

#endif //_HARDWAREUSB_H

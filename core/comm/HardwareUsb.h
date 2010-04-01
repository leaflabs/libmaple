/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Andrew Meyer.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/

/**
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
	int8 rx_buffer_offset_out;
	int8 rx_buffer_offset_in;
    public:
        HardwareUsb(void);
	void begin();
	uint8 available(void);
	uint8 read(void);
	void flush(void);
	virtual void write(unsigned char);
	using Print::write;
};

#endif //_HARDWAREUSB_H

/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 *  @brief wirish usb class for easy goin communication, uses libmaple's
 *  virtual com port implementation
 */

#include <string.h>

#include "wirish.h"
#include "usb.h"

USBSerial :: USBSerial(void) {
}

void USBSerial::write(uint8 ch) {
   usbSendBytes(&ch, 1);
}

void USBSerial::write(const char *str) {
   uint32 len = strlen(str);
   usbSendBytes((uint8*)str, len);
}

void USBSerial::write(void *buf, uint32 size) {
   if (!buf) {
      return;
   }
   usbSendBytes((uint8*)buf, size);
}

uint32 USBSerial::available(void) {
   return usbBytesAvailable();
}

uint32 USBSerial::read(void *buf, uint32 len) {
   if (!buf) {
      return 0;
   }

   return usbReceiveBytes((uint8*)buf, len);
}

uint8 USBSerial::read(void) {
   uint8 ch;
   usbReceiveBytes(&ch, 1);
   return ch;
}

USBSerial SerialUSB;


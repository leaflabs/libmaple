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

#define USB_TIMEOUT 50

USBSerial :: USBSerial(void) {
}

void USBSerial::begin(void) {
    setupUSB();
}

void USBSerial::end(void) {
    disableUSB();
}

void USBSerial::write(uint8 ch) {
    if(!(usbIsConnected() && usbIsConfigured())) {
        return;
    }
    uint16 status = 0;
    uint32 start = millis();
    while(status == 0 && (millis() - start <= USB_TIMEOUT)) {
        status = usbSendBytes(&ch, 1);
    }
}

void USBSerial::write(const char *str) {
    if(!(usbIsConnected() && usbIsConfigured())) {
        return;
    }
    uint32 len = strlen(str);
    uint16 status = 0;
    uint16 oldstatus = 0;
    uint32 start = millis();
    while(status < len && (millis() - start < USB_TIMEOUT)) {
        status += usbSendBytes((uint8*)str+status, len-status);
        if(oldstatus != status) 
            start = millis();
        oldstatus = status;
    }
}

void USBSerial::write(void *buf, uint32 size) {
    if(!(usbIsConnected() && usbIsConfigured())) {
        return;
    }
    if (!buf) {
        return;
    }
    uint16 status = 0;
    uint16 oldstatus = 0;
    uint32 start = millis();
    while(status < size && (millis() - start < USB_TIMEOUT)) {
        status += usbSendBytes((uint8*)buf+status, size-status);
        if(oldstatus != status) 
            start = millis();
        oldstatus = status;
    }
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

uint8 USBSerial::pending(void) {
   return usbGetPending();
}

uint8 USBSerial::getDTR(void) {
   return usbGetDTR();
}

uint8 USBSerial::getRTS(void) {
   return usbGetRTS();
}

uint8 USBSerial::isConnected(void) {
   return (usbIsConnected() && usbIsConfigured());
}

USBSerial SerialUSB;


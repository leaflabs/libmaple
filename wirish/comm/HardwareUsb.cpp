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
 * @brief Wiring like serial api to USB virtual COM
 */

#include "wirish.h"
#include "HardwareUsb.h"
#include "usb.h"

HardwareUsb::HardwareUsb(void) {
}

uint8 HardwareUsb::read(void) {
  uint8 outVal;
  usbReceiveBytes(&outVal,1);
  return outVal;
}

uint8 HardwareUsb::available(void) {
  return usbBytesAvailable();
}

void HardwareUsb::flush(void) {
  uint8 totalBytes = usbBytesAvailable();
  uint8 recvBuf[totalBytes];
  usbReceiveBytes(recvBuf,totalBytes);
}

void HardwareUsb::write(unsigned char ch) {
  while (usbSendBytes(&ch, 1) == 0);
}

void HardwareUsb::begin(void) {
  /* placeholder for usb<->uart linking */
}

HardwareUsb Usb;

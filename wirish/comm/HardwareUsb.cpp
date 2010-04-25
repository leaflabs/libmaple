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

#include "wirish.h"
#include "HardwareUsb.h"
#include "bootVect.h"
#include "usb.h"

HardwareUsb::HardwareUsb(void) {
  mapleVectTable = (BootVectTable*)(BOOTLOADER_VECT_TABLE);
  mapleVectTable->serial_tx_cb = usb_tx_cb;
  mapleVectTable->serial_rx_cb = usb_rx_cb;
  mapleVectTable->usb_local_obj_ptr = this;
  rx_buffer_offset_in = 0;
  rx_buffer_offset_out = 0;
}

uint8 HardwareUsb::read(void) {
  uint8 outVal = rx_buffer[rx_buffer_offset_out++];

#if 1
  if (rx_buffer_offset_out == rx_buffer_offset_in) {
    flush();
  }
#endif

  return outVal;
}

uint8 HardwareUsb::available(void) {
  ASSERT(rx_buffer_offset_out >= 0);
  //  return rx_buffer_offset+1;
  //  return usb_serialGetRecvLen();
  return rx_buffer_offset_in - rx_buffer_offset_out;
}

void HardwareUsb::flush(void) {
  rx_buffer_offset_in = 0;
  rx_buffer_offset_out = 0;
}

void HardwareUsb::write(unsigned char ch) {
  usb_serialWriteChar(ch);
}

void HardwareUsb::begin(void) {
  /* placeholder for usb<->uart linking */
}

void HardwareUsb::usb_rx_cb(void) {
   BootVectTable *vectTable = (BootVectTable*)(BOOTLOADER_VECT_TABLE);
   HardwareUsb *thisPtr = (HardwareUsb*) vectTable->usb_local_obj_ptr;

   uint8 numBytes = usb_serialGetRecvLen();

#if 0
   /* ONE-SHOT-TO-READ Version (buffer cleared on next recv interrupt */
   usb_copyRecvBuffer(thisPtr->rx_buffer,numBytes);
   thisPtr->rx_buffer_offset_in = numBytes;
   thisPtr->rx_buffer_offset_out = 0;
#else 
  /* FIFO DISCARD OVERFLOW VERSION */
  if ((thisPtr->rx_buffer_offset_in + numBytes) > (USB_SERIAL_BUF_SIZE)) {
    numBytes = USB_SERIAL_BUF_SIZE - thisPtr->rx_buffer_offset_in;
  }

  if (numBytes > 0) {
    ASSERT(thisPtr->rx_buffer_offset_in <= USB_SERIAL_BUF_SIZE);
    usb_copyRecvBuffer(&(thisPtr->rx_buffer[thisPtr->rx_buffer_offset_in]),numBytes);
    thisPtr->rx_buffer_offset_in += numBytes;
  }
#endif
}

void HardwareUsb::usb_tx_cb(void) {
  /* placeholder for when serial dumps exceed buflen */
}

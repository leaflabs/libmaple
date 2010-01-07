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
 *  @file HardwareUsb.cpp
 *
 *  @brief Wiring like serial api to USB virtual COM
 */

#include "wiring.h"
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

uint8_t HardwareUsb::read(void) {
  uint8_t outVal = rx_buffer[rx_buffer_offset_out++];

#if 1
  if (rx_buffer_offset_out == rx_buffer_offset_in) {
    flush();
  }
#endif

  return outVal;
}

uint8_t HardwareUsb::available(void) {
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

   uint8_t numBytes = usb_serialGetRecvLen();

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

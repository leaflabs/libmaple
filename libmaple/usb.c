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

#include "libmaple.h"
#include "usb.h"
#include "usb_regs.h"
#include "bootVect.h"

void usb_lpIRQHandler(void)
{
  typedef void (*funcPtr)(void);
  
  const uint32 usbIsrAddr = *(uint32*)(USB_ISR_ADDR);
  void (*ptrToUsbISR)(void) = (funcPtr) usbIsrAddr;
  ptrToUsbISR();
}

void usb_userToPMABufferCopy(uint8 *pbUsrBuf, uint16 wPMABufAddr, uint16 wNBytes)
{
  uint32 n = (wNBytes + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
  uint32 i, temp1, temp2;
  uint16 *pdwVal;
  pdwVal = (uint16 *)(wPMABufAddr * 2 + PMAAddr);
  for (i = n; i != 0; i--)
    {
      temp1 = (uint16) * pbUsrBuf;
      pbUsrBuf++;
      temp2 = temp1 | (uint16) * pbUsrBuf << 8;
      *pdwVal++ = temp2;
      pdwVal++;
      pbUsrBuf++;
    }
}

void usb_PMAToUserBufferCopy(uint8 *pbUsrBuf, uint16 wPMABufAddr, uint16 wNBytes)
{
  uint32 n = (wNBytes + 1) >> 1;/* /2*/
  uint32 i;
  uint32 *pdwVal;
  pdwVal = (uint32 *)(wPMABufAddr * 2 + PMAAddr);
  for (i = n; i != 0; i--)
    {
      *(uint16*)pbUsrBuf++ = *pdwVal++;
      pbUsrBuf++;
    }
}

void usb_serialWriteStr(const char* outStr) {
  uint8 offset=0;
  BootVectTable *bootVector = ((BootVectTable*)BOOTLOADER_VECT_TABLE);

  while ((outStr[offset] != '\0')
	 && (offset < USB_SERIAL_BUF_SIZE)) {
    offset++;
  }

  delay(offset*1);

  bootVector->serial_count_in = (uint32*) &offset;
  usb_userToPMABufferCopy((uint8*)outStr,USB_SERIAL_ENDP_TXADDR,offset);
  _SetEPTxCount(USB_SERIAL_ENDP_TX,offset);
  _SetEPTxValid(USB_SERIAL_ENDP_TX);

}

void usb_serialWriteChar(unsigned char ch) {
  BootVectTable *bootVector = ((BootVectTable*)BOOTLOADER_VECT_TABLE);

  delay(1);

  *(bootVector->serial_count_in) = 1;
  usb_userToPMABufferCopy((uint8*)(&ch),USB_SERIAL_ENDP_TXADDR,1);
  _SetEPTxCount(USB_SERIAL_ENDP_TX,1);
  _SetEPTxValid(USB_SERIAL_ENDP_TX);

}

uint8 usb_serialGetRecvLen() {
  uint8 count_out =_GetEPRxCount(USB_SERIAL_ENDP_RX); 
  return count_out;
}

void usb_copyRecvBuffer(unsigned char* dest, uint8 len) {
  ASSERT(len < USB_SERIAL_BUF_SIZE);
  usb_PMAToUserBufferCopy((uint8*)(dest),USB_SERIAL_ENDP_RXADDR,len);
  _SetEPRxValid(USB_SERIAL_ENDP_RX);
}


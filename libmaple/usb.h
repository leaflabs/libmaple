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

#ifndef _USB_H_
#define _USB_H_

#define USB_ISR_ADDR              (0x08000090)
#define USB_SERIAL_ENDP_TXADDR    ((uint32) 0xC0)
#define USB_SERIAL_ENDP_RXADDR    ((uint32) 0x110)
#define USB_SERIAL_ENDP_TX        ((uint16) 0x1)
#define USB_SERIAL_ENDP_RX        ((uint16) 0x3)
#define USB_SERIAL_BUF_SIZE       (0x40)

#ifdef __cplusplus
extern "C" {
#endif

void usb_lpIRQHandler(void);
void usb_userToPMABufferCopy(uint8  *pbUsrBuf,uint16 wPMABufAddr,uint16 wNBytes);
void usb_PMAToUserBufferCopy(uint8  *pbUsrBuf,uint16 wPMABufAddr,uint16 wNBytes);
void usb_serialWriteStr(const char *outStr);
void usb_serialWriteChar(unsigned char ch);
uint8 usb_serialGetRecvLen();
void usb_copyRecvBuffer(unsigned char* dest, uint8 len);

#ifdef __cplusplus
} // extern "C"
#endif
#endif //_USB_H

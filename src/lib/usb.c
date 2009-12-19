#include <inttypes.h>
#include "usb.h"

BootVectTable* bootVect = ((BootVectTable*) BOOTLOADER_VECT_TABLE);

void usb_lpIRQHandler(void)
{
  typedef void (*funcPtr)(void);
  
  const uint32_t usbIsrAddr = *(uint32_t*)(USB_ISR_ADDR);
  void (*ptrToUsbISR)(void) = (funcPtr) usbIsrAddr;
  ptrToUsbISR();
}

void usb_userToPMABufferCopy(u8 *pbUsrBuf, u16 wPMABufAddr, u16 wNBytes)
{
  u32 n = (wNBytes + 1) >> 1;   /* n = (wNBytes + 1) / 2 */
  u32 i, temp1, temp2;
  u16 *pdwVal;
  pdwVal = (u16 *)(wPMABufAddr * 2 + PMAAddr);
  for (i = n; i != 0; i--)
    {
      temp1 = (u16) * pbUsrBuf;
      pbUsrBuf++;
      temp2 = temp1 | (u16) * pbUsrBuf << 8;
      *pdwVal++ = temp2;
      pdwVal++;
      pbUsrBuf++;
    }
}

void usb_PMAToUserBufferCopy(u8 *pbUsrBuf, u16 wPMABufAddr, u16 wNBytes)
{
  u32 n = (wNBytes + 1) >> 1;/* /2*/
  u32 i;
  u32 *pdwVal;
  pdwVal = (u32 *)(wPMABufAddr * 2 + PMAAddr);
  for (i = n; i != 0; i--)
    {
      *(u16*)pbUsrBuf++ = *pdwVal++;
      pbUsrBuf++;
    }
}

void usb_serialWriteStr(const char* outStr) {
  u8 offset=0;
  BootVectTable *bootVector = ((BootVectTable*)BOOTLOADER_VECT_TABLE);

  while ((outStr[offset] != '\0')
	 && (offset < USB_SERIAL_BUF_SIZE)) {
    offset++;
  }

  delay(offset*1);

  bootVector->serial_count_in = (u32*) &offset;
  usb_userToPMABufferCopy((u8*)outStr,USB_SERIAL_ENDP_TXADDR,offset);
  _SetEPTxCount(USB_SERIAL_ENDP_TX,offset);
  _SetEPTxValid(USB_SERIAL_ENDP_TX);

}

uint8_t usb_serialGetRecvLen() {
  uint8_t count_out = _GetEPRxCount(USB_SERIAL_ENDP_RX);
  _SetEPRxValid(USB_SERIAL_ENDP_RX);
  return count_out;
}

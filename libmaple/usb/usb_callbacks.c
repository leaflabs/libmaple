/* insert license */

#include "usb_callbacks.h"
#include "usb_lib.h"
#include "descriptors.h"
#include "usb_config.h"
#include "usb.h"

ONE_DESCRIPTOR Device_Descriptor = {
  (uint8*)&usbVcomDescriptor_Device,
  sizeof(USB_Descriptor_Device)
};

ONE_DESCRIPTOR Config_Descriptor = {
  (uint8*)&usbVcomDescriptor_Config,
  0x43//sizeof(USB_Descriptor_Config)
};

ONE_DESCRIPTOR String_Descriptor[3] = {
  {(uint8*)&usbVcomDescriptor_LangID,       USB_DESCRIPTOR_STRING_LEN(1)},
  {(uint8*)&usbVcomDescriptor_iManufacturer,USB_DESCRIPTOR_STRING_LEN(8)},
  {(uint8*)&usbVcomDescriptor_iProduct,     USB_DESCRIPTOR_STRING_LEN(8)}
};

uint8 last_request = 0;

USB_Line_Coding line_coding = {
 bitrate:     115200,
 format:      0x00, /* stop bits-1 */
 paritytype:  0x00,
 datatype:    0x08
};

uint8 vcomBufferRx[VCOM_RX_EPSIZE];
volatile uint8 countTx    = 0;
volatile uint8 recvBufIn  = 0;
volatile uint8 recvBufOut = 0;
volatile uint8 maxNewBytes   = VCOM_RX_EPSIZE;

RESET_STATE reset_state = START;

void vcomDataTxCb(void) {
  /* do whatever after data has been sent to host */

  /* allows usbSendBytes to stop blocking */


  countTx = 0;
}

/* we could get arbitrarily complicated here for speed purposes
   however, the simple scheme here is to implement a receive fifo
   and always set the maximum to new bytes to the space remaining
   in the fifo. this number will be reincremented after calls
   to usbReceiveBytes */
void vcomDataRxCb(void) {
  /* do whatever after data has been received from host */

  /* setEPRxCount on the previous cycle should garuntee
     we havnt received more bytes than we can fit */
  uint8 newBytes = GetEPRxCount(VCOM_RX_ENDP);
  /* assert (newBytes <= maxNewBytes); */

  if (recvBufIn + newBytes < VCOM_RX_EPSIZE) {
    PMAToUserBufferCopy(&vcomBufferRx[recvBufIn],VCOM_RX_ADDR,newBytes);
    recvBufIn += newBytes;
  } else {
    /* we have to copy the data in two chunks because we roll over
       the edge of the circular buffer */
    uint8 tailBytes = VCOM_RX_EPSIZE - recvBufIn;
    uint8 remaining = newBytes - tailBytes;

    PMAToUserBufferCopy(&vcomBufferRx[recvBufIn],VCOM_RX_ADDR,tailBytes);
    PMAToUserBufferCopy(&vcomBufferRx[0],        VCOM_RX_ADDR,remaining);

    recvBufIn = (recvBufIn + newBytes ) % VCOM_RX_EPSIZE;
  }
  
  maxNewBytes    -= newBytes;
  SetEPRxCount(VCOM_RX_ENDP,maxNewBytes);
  SetEPRxValid(VCOM_RX_ENDP);
}

void vcomManagementCb(void) {
/* unused. This enpoint would callback if we had sent a linestate
     changed notification */
}

u8* vcomGetSetLineCoding(uint16 length) {
  if (length == 0) {
    pInformation->Ctrl_Info.Usb_wLength = sizeof(USB_Line_Coding);
  }
  return (uint8*)&line_coding;
}

vcomSetLineState(void) {
}

void usbInit(void) {
  pInformation->Current_Configuration = 0;
  usbPowerOn();

  _SetISTR(0);
  wInterrupt_Mask = ISR_MSK;
  _SetCNTR(wInterrupt_Mask);

  usbEnbISR();
  bDeviceState = UNCONNECTED;
}

void usbReset(void) {
  pInformation->Current_Configuration = 0;

  /* current feature is current bmAttributes */
  pInformation->Current_Feature = (USB_CONFIG_ATTR_BUSPOWERED | USB_CONFIG_ATTR_SELF_POWERED);

  _SetBTABLE(USB_BTABLE_ADDRESS);

  /* setup control endpoint 0 */
  _SetEPType(ENDP0, EP_CONTROL);
  _SetEPTxStatus(ENDP0, EP_TX_STALL);
  _SetEPRxAddr(ENDP0,VCOM_CTRL_RX_ADDR);
  _SetEPTxAddr(ENDP0,VCOM_CTRL_TX_ADDR);
  Clear_Status_Out(ENDP0);
  
  SetEPRxCount(ENDP0, pProperty->MaxPacketSize);
  SetEPRxValid(ENDP0);

  /* setup management endpoint 1  */
  SetEPType     (VCOM_NOTIFICATION_ENDP,     EP_INTERRUPT);
  SetEPTxAddr   (VCOM_NOTIFICATION_ENDP,     VCOM_NOTIFICATION_ADDR);
  SetEPTxStatus (VCOM_NOTIFICATION_ENDP,     EP_TX_NAK);
  SetEPRxStatus (VCOM_NOTIFICATION_ENDP,     EP_RX_DIS);

  /* setup data endpoint OUT (rx) */
/*   SetEPType     (VCOM_RX_ENDP, EP_BULK); */
/*   SetEPRxAddr   (VCOM_RX_ENDP, VCOM_RX_ADDR); */
/*   SetEPRxCount  (VCOM_RX_ENDP, VCOM_RX_EPSIZE); */
/*   // SetEPTxStatus (VCOM_RX_ENDP, EP_TX_DIS); */
/*   SetEPRxStatus (VCOM_RX_ENDP, EP_RX_VALID); */

  SetEPType     (3, EP_BULK);
  SetEPRxAddr   (3, 0x110);
  SetEPRxCount  (3,64);
  // SetEPTxStatus (VCOM_RX_ENDP, EP_TX_DIS);
  SetEPRxStatus (3, EP_RX_VALID);

  /* setup data endpoint IN (tx)  */
  SetEPType     (VCOM_TX_ENDP, EP_BULK);
  SetEPTxAddr   (VCOM_TX_ENDP, VCOM_TX_ADDR);
  SetEPTxStatus (VCOM_TX_ENDP, EP_TX_NAK);
  SetEPRxStatus (VCOM_TX_ENDP, EP_RX_DIS);

  bDeviceState = ATTACHED;
  SetDeviceAddress(0);

  /* reset the rx fifo */
  recvBufIn   = 0;
  recvBufOut  = 0;
  maxNewBytes = VCOM_RX_EPSIZE;
  countTx     = 0;
}


void usbStatusIn(void) {
  /* adjust the usart line coding
     if we wish to couple the CDC line coding
     with the real usart port */
}

void usbStatusOut(void) {
}

RESULT usbDataSetup(uint8 request) {
  uint8 *(*CopyRoutine)(uint16);
  CopyRoutine = NULL;

  if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) {
    switch (request) {
    case (GET_LINE_CODING): 
      CopyRoutine = vcomGetSetLineCoding;
      last_request = GET_LINE_CODING;
      break;
    case (SET_LINE_CODING): 
      CopyRoutine = vcomGetSetLineCoding;
      last_request = SET_LINE_CODING;
      break;
    default: break;
    }
  }

  if (CopyRoutine == NULL) {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

RESULT usbNoDataSetup(u8 request) {
  uint8 new_signal;

  /* we support set com feature but dont handle it */
  if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) {

    switch (request) {
    case (SET_COMM_FEATURE):
      return USB_SUCCESS;
    case (SET_CONTROL_LINE_STATE):
      /* to reset the board, pull both dtr and rts low
	 then pulse dtr by itself */
      new_signal = pInformation->USBwValues.bw.bb0 & (CONTROL_LINE_DTR | CONTROL_LINE_RTS);
      switch (reset_state) {
	/* no default, covered enum */
        case START: 
	  if (new_signal == 0) {
	    reset_state = NDTR_NRTS;
	  }
	  break;

        case NDTR_NRTS: 
	  if (new_signal == CONTROL_LINE_DTR) {
	    reset_state = DTR_NRTS;
	  } else if (new_signal == 0) {
	    reset_state = NDTR_NRTS;
	  } else {
	    reset_state = START;
	  }
	  break;

        case DTR_NRTS: 
	  if (new_signal == 0) {
	    /* dont reset here, otherwise
	       well likely crash the host! */
	    reset_state = RESET_NOW;
	  } else {
	    reset_state = START;
	  }
	  break;
      case RESET_NEXT:
	reset_state = RESET_NOW;
	break;
      case RESET_NOW:
      /* do nothing, wait for reset */
	break;
      }
      return USB_SUCCESS;
    }
  }
  return USB_UNSUPPORT;
}

RESULT usbGetInterfaceSetting(uint8 interface, uint8 alt_setting) {
  if (alt_setting > 0) {
    return USB_UNSUPPORT;
  } else if (interface > 1) {
    return USB_UNSUPPORT;
  }

  return USB_SUCCESS;
}


u8* usbGetDeviceDescriptor(u16 length) {
  return Standard_GetDescriptorData(length, &Device_Descriptor);
}

u8* usbGetConfigDescriptor(u16 length) {
  return Standard_GetDescriptorData(length, &Config_Descriptor);
}

u8* usbGetStringDescriptor(u16 length) {
  uint8 wValue0 = pInformation->USBwValue0;

  if (wValue0 > 2) {
    return NULL;
  }
  return Standard_GetDescriptorData(length, &String_Descriptor[wValue0]);
}

/* internal callbacks to respond to standard requests */
void usbSetConfiguration(void) {
  if (pInformation->Current_Configuration != 0) {
    bDeviceState = CONFIGURED;
  }
}

void usbSetDeviceAddress(void) {
  bDeviceState = ADDRESSED;
}


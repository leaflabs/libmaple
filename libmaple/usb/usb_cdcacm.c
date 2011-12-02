/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file usb_cdcacm.c
 *
 * @brief USB CDC ACM (a.k.a. virtual serial terminal, VCOM) state and
 *        routines.
 */

#include "usb_cdcacm.h"

#include "nvic.h"

#include "usb.h"
#include "descriptors.h"
#include "usb_lib_globals.h"
#include "usb_reg_map.h"

#include "usb_type.h"
#include "usb_core.h"
#include "usb_def.h"

/******************************************************************************
 ******************************************************************************
 ***
 ***   HACK ALERT! FIXME FIXME FIXME FIXME!
 ***
 ***   A bunch of LeafLabs-specific configuration lives in here for
 ***   now.  This mess REALLY needs to get teased apart, with
 ***   appropriate pieces moved into Wirish.
 ***
 ******************************************************************************
 *****************************************************************************/

#if !(defined(BOARD_maple) || defined(BOARD_maple_RET6) ||      \
      defined(BOARD_maple_mini) || defined(BOARD_maple_native))

#warning ("Warning! USB VCOM relies on LeafLabs board-specific "        \
          "configuration right now.  If you want, you can pretend "     \
          "you're one of our boards; i.e., #define BOARD_maple, "       \
          "BOARD_maple_mini, etc.  according to what matches your MCU " \
          "best."
#endif

static void vcomDataTxCb(void);
static void vcomDataRxCb(void);
static uint8* vcomGetSetLineCoding(uint16);

static void usbInit(void);
static void usbReset(void);
static RESULT usbDataSetup(uint8 request);
static RESULT usbNoDataSetup(uint8 request);
static RESULT usbGetInterfaceSetting(uint8 interface, uint8 alt_setting);
static uint8* usbGetDeviceDescriptor(uint16 length);
static uint8* usbGetConfigDescriptor(uint16 length);
static uint8* usbGetStringDescriptor(uint16 length);
static void usbSetConfiguration(void);
static void usbSetDeviceAddress(void);

/*
 * VCOM config
 */

#define VCOM_CTRL_EPNUM           0x00
#define VCOM_CTRL_RX_ADDR         0x40
#define VCOM_CTRL_TX_ADDR         0x80
#define VCOM_CTRL_EPSIZE          0x40

#define VCOM_TX_ENDP              1
#define VCOM_TX_EPNUM             0x01
#define VCOM_TX_ADDR              0xC0
#define VCOM_TX_EPSIZE            0x40

#define VCOM_NOTIFICATION_ENDP    2
#define VCOM_NOTIFICATION_EPNUM   0x02
#define VCOM_NOTIFICATION_ADDR    0x100
#define VCOM_NOTIFICATION_EPSIZE  0x40

#define VCOM_RX_ENDP              3
#define VCOM_RX_EPNUM             0x03
#define VCOM_RX_ADDR              0x110
#define VCOM_RX_EPSIZE            0x40
#define VCOM_RX_BUFLEN            (VCOM_RX_EPSIZE*3)

/*
 * CDC ACM Requests
 */

#define SET_LINE_CODING        0x20
#define GET_LINE_CODING        0x21
#define SET_COMM_FEATURE       0x02
#define SET_CONTROL_LINE_STATE 0x22
#define CONTROL_LINE_DTR       (0x01)
#define CONTROL_LINE_RTS       (0x02)

/*
 * Descriptors
 */

#define USB_DEVICE_CLASS_CDC              0x02
#define USB_DEVICE_SUBCLASS_CDC           0x00
#define LEAFLABS_ID_VENDOR                0x1EAF
#define MAPLE_ID_PRODUCT                  0x0004
const USB_Descriptor_Device usbVcomDescriptor_Device = {
    .bLength            = sizeof(USB_Descriptor_Device),
    .bDescriptorType    = USB_DESCRIPTOR_TYPE_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = USB_DEVICE_CLASS_CDC,
    .bDeviceSubClass    = USB_DEVICE_SUBCLASS_CDC,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = 0x40,
    .idVendor           = LEAFLABS_ID_VENDOR,
    .idProduct          = MAPLE_ID_PRODUCT,
    .bcdDevice          = 0x0200,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x00,
    .bNumConfigurations = 0x01,
};

#define MAX_POWER (100 >> 1)
const USB_Descriptor_Config usbVcomDescriptor_Config = {
    .Config_Header = {
        .bLength              = sizeof(USB_Descriptor_Config_Header),
        .bDescriptorType      = USB_DESCRIPTOR_TYPE_CONFIGURATION,
        .wTotalLength         = sizeof(USB_Descriptor_Config),
        .bNumInterfaces       = 0x02,
        .bConfigurationValue  = 0x01,
        .iConfiguration       = 0x00,
        .bmAttributes         = (USB_CONFIG_ATTR_BUSPOWERED |
                                 USB_CONFIG_ATTR_SELF_POWERED),
        .bMaxPower            = MAX_POWER,
    },

    .CCI_Interface = {
        .bLength            = sizeof(USB_Descriptor_Interface),
        .bDescriptorType    = USB_DESCRIPTOR_TYPE_INTERFACE,
        .bInterfaceNumber   = 0x00,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 0x01,
        .bInterfaceClass    = USB_INTERFACE_CLASS_CDC,
        .bInterfaceSubClass = USB_INTERFACE_SUBCLASS_CDC_ACM,
        .bInterfaceProtocol = 0x01, /* Common AT Commands */
        .iInterface         = 0x00,
    },

    .CDC_Functional_IntHeader = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(2),
        .bDescriptorType = 0x24,
        .SubType         = 0x00,
        .Data            = {0x01, 0x10},
    },

    .CDC_Functional_CallManagement = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(2),
        .bDescriptorType = 0x24,
        .SubType         = 0x01,
        .Data            = {0x03, 0x01},
    },

    .CDC_Functional_ACM = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(1),
        .bDescriptorType = 0x24,
        .SubType         = 0x02,
        .Data            = {0x06},
    },

    .CDC_Functional_Union = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(2),
        .bDescriptorType = 0x24,
        .SubType         = 0x06,
        .Data            = {0x00, 0x01},
    },

    .ManagementEndpoint = {
        .bLength          = sizeof(USB_Descriptor_Endpoint),
        .bDescriptorType  = USB_DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = (USB_DESCRIPTOR_ENDPOINT_IN |
                             VCOM_NOTIFICATION_EPNUM),
        .bmAttributes     = EP_TYPE_INTERRUPT,
        .wMaxPacketSize   = VCOM_NOTIFICATION_EPSIZE,
        .bInterval        = 0xFF,
    },

    .DCI_Interface = {
        .bLength            = sizeof(USB_Descriptor_Interface),
        .bDescriptorType    = USB_DESCRIPTOR_TYPE_INTERFACE,
        .bInterfaceNumber   = 0x01,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 0x02,
        .bInterfaceClass    = USB_INTERFACE_CLASS_DIC,
        .bInterfaceSubClass = 0x00, /* None */
        .bInterfaceProtocol = 0x00, /* None */
        .iInterface         = 0x00,
    },

    .DataOutEndpoint = {
        .bLength          = sizeof(USB_Descriptor_Endpoint),
        .bDescriptorType  = USB_DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = (USB_DESCRIPTOR_ENDPOINT_OUT | VCOM_RX_EPNUM),
        .bmAttributes     = EP_TYPE_BULK,
        .wMaxPacketSize   = VCOM_RX_EPSIZE,
        .bInterval        = 0x00,
    },

    .DataInEndpoint = {
        .bLength          = sizeof(USB_Descriptor_Endpoint),
        .bDescriptorType  = USB_DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = (USB_DESCRIPTOR_ENDPOINT_IN | VCOM_TX_EPNUM),
        .bmAttributes     = EP_TYPE_BULK,
        .wMaxPacketSize   = VCOM_TX_EPSIZE,
        .bInterval        = 0x00,
    },
};

/*
  String Identifiers:

  we may choose to specify any or none of the following string
  identifiers:

  iManufacturer:    LeafLabs
  iProduct:         Maple
  iSerialNumber:    NONE
  iConfiguration:   NONE
  iInterface(CCI):  NONE
  iInterface(DCI):  NONE

  additionally we must provide the unicode language identifier,
  which is 0x0409 for US English
*/

const uint8 usbVcomDescriptor_LangID[USB_DESCRIPTOR_STRING_LEN(1)] = {
    USB_DESCRIPTOR_STRING_LEN(1),
    USB_DESCRIPTOR_TYPE_STRING,
    0x09,
    0x04,
};

const uint8 usbVcomDescriptor_iManufacturer[USB_DESCRIPTOR_STRING_LEN(8)] = {
    USB_DESCRIPTOR_STRING_LEN(8),
    USB_DESCRIPTOR_TYPE_STRING,
    'L', 0, 'e', 0, 'a', 0, 'f', 0,
    'L', 0, 'a', 0, 'b', 0, 's', 0,
};

const uint8 usbVcomDescriptor_iProduct[USB_DESCRIPTOR_STRING_LEN(8)] = {
    USB_DESCRIPTOR_STRING_LEN(8),
    USB_DESCRIPTOR_TYPE_STRING,
    'M', 0, 'a', 0, 'p', 0, 'l', 0,
    'e', 0, ' ', 0, ' ', 0, ' ', 0
};

ONE_DESCRIPTOR Device_Descriptor = {
    (uint8*)&usbVcomDescriptor_Device,
    sizeof(USB_Descriptor_Device)
};

ONE_DESCRIPTOR Config_Descriptor = {
    (uint8*)&usbVcomDescriptor_Config,
    sizeof(USB_Descriptor_Config)
};

ONE_DESCRIPTOR String_Descriptor[3] = {
    {(uint8*)&usbVcomDescriptor_LangID,       USB_DESCRIPTOR_STRING_LEN(1)},
    {(uint8*)&usbVcomDescriptor_iManufacturer,USB_DESCRIPTOR_STRING_LEN(8)},
    {(uint8*)&usbVcomDescriptor_iProduct,     USB_DESCRIPTOR_STRING_LEN(8)}
};

/*
 * Etc.
 */

typedef enum {
  DTR_UNSET,
  DTR_HIGH,
  DTR_NEGEDGE,
  DTR_LOW
} RESET_STATE;

typedef struct {
  uint32 bitrate;
  uint8  format;
  uint8  paritytype;
  uint8  datatype;
} USB_Line_Coding;

uint8 last_request = 0;
USB_Line_Coding line_coding = {
    .bitrate = 115200,
    .format = 0x00, /* stop bits-1 */
    .paritytype = 0x00,
    .datatype = 0x08
};
uint8 vcomBufferRx[VCOM_RX_BUFLEN];
volatile uint32 countTx    = 0;
volatile uint32 recvBufIn  = 0;
volatile uint32 recvBufOut = 0;
volatile uint32 maxNewBytes   = VCOM_RX_BUFLEN;
volatile uint32 newBytes = 0;
RESET_STATE reset_state = DTR_UNSET;
uint8       line_dtr_rts = 0;

/*
 * Endpoint callbacks
 */

static void (*ep_int_in[7])(void) =
    {vcomDataTxCb,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process};

static void (*ep_int_out[7])(void) =
    {NOP_Process,
     NOP_Process,
     vcomDataRxCb,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process};

/*
 * Globals required by usb_lib/
 */

#define NUM_ENDPTS                0x04
DEVICE Device_Table = {
    .Total_Endpoint      = NUM_ENDPTS,
    .Total_Configuration = 1
};

#define MAX_PACKET_SIZE            0x40  /* 64B, maximum for USB FS Devices */
DEVICE_PROP Device_Property = {
    .Init                        = usbInit,
    .Reset                       = usbReset,
    .Process_Status_IN           = NOP_Process,
    .Process_Status_OUT          = NOP_Process,
    .Class_Data_Setup            = usbDataSetup,
    .Class_NoData_Setup          = usbNoDataSetup,
    .Class_Get_Interface_Setting = usbGetInterfaceSetting,
    .GetDeviceDescriptor         = usbGetDeviceDescriptor,
    .GetConfigDescriptor         = usbGetConfigDescriptor,
    .GetStringDescriptor         = usbGetStringDescriptor,
    .RxEP_buffer                 = NULL,
    .MaxPacketSize               = MAX_PACKET_SIZE
};

USER_STANDARD_REQUESTS User_Standard_Requests = {
    .User_GetConfiguration   = NOP_Process,
    .User_SetConfiguration   = usbSetConfiguration,
    .User_GetInterface       = NOP_Process,
    .User_SetInterface       = NOP_Process,
    .User_GetStatus          = NOP_Process,
    .User_ClearFeature       = NOP_Process,
    .User_SetEndPointFeature = NOP_Process,
    .User_SetDeviceFeature   = NOP_Process,
    .User_SetDeviceAddress   = usbSetDeviceAddress
};

/*
 * CDC ACM interface
 */

void usb_cdcacm_enable(gpio_dev *disc_dev, uint8 disc_bit) {
    /* Present ourselves to the host */
    gpio_set_mode(disc_dev, disc_bit, GPIO_OUTPUT_PP);
    gpio_write_bit(disc_dev, disc_bit, 0); // presents us to the host

    /* initialize USB peripheral */
    usb_init_usblib(ep_int_in, ep_int_out);
}

void usb_cdcacm_disable(gpio_dev *disc_dev, uint8 disc_bit) {
    // These are just guesses about how to do this, but it seems to work.
    // TODO: verify this with USB spec
    nvic_irq_disable(NVIC_USB_LP_CAN_RX0);
    gpio_write_bit(disc_dev, disc_bit, 1);
}

void usb_cdcacm_putc(char ch) {
    while (!usb_cdcacm_tx((uint8*)&ch, 1))
        ;
}

/* This function is non-blocking.
 *
 * It copies data from a usercode buffer into the USB peripheral TX
 * buffer and return the number placed in that buffer.
 */
uint32 usb_cdcacm_tx(const uint8* buf, uint32 len) {
    /* Last transmission hasn't finished, abort */
    if (countTx) {
        return 0;
    }

    // We can only put VCOM_TX_EPSIZE bytes in the buffer
    /* FIXME then why are we only copying half as many? */
    if (len > VCOM_TX_EPSIZE / 2) {
        len = VCOM_TX_EPSIZE / 2;
    }

    // Try to load some bytes if we can
    if (len) {
        usb_copy_to_pma(buf, len, VCOM_TX_ADDR);
        usb_set_ep_tx_count(VCOM_TX_ENDP, len);
        countTx += len;
        usb_set_ep_tx_stat(VCOM_TX_ENDP, USB_EP_STAT_TX_VALID);
    }

    return len;
}

/* returns the number of available bytes are in the recv FIFO */
uint32 usb_cdcacm_data_available(void) {
    return newBytes;
}

uint16 usb_cdcacm_get_pending() {
    return countTx;
}

/* Nonblocking byte receive.
 *
 * Copies up to len bytes from our private data buffer (*NOT* the PMA)
 * into buf and deq's the FIFO. */
uint32 usb_cdcacm_rx(uint8* buf, uint32 len) {
    static int offset = 0;
    int i;

    if (len > newBytes) {
        len = newBytes;
    }

    for (i = 0; i < len; i++) {
        buf[i] = vcomBufferRx[i + offset];
    }

    newBytes -= len;
    offset += len;

    /* Re-enable the RX endpoint, which we had set to receive 0 bytes */
    if (newBytes == 0) {
        usb_set_ep_rx_count(VCOM_RX_ENDP, VCOM_RX_EPSIZE);
        usb_set_ep_rx_stat(VCOM_RX_ENDP, USB_EP_STAT_RX_VALID);
        offset = 0;
    }

    return len;
}

uint8 usb_cdcacm_get_dtr() {
    return ((line_dtr_rts & CONTROL_LINE_DTR) != 0);
}

uint8 usb_cdcacm_get_rts() {
    return ((line_dtr_rts & CONTROL_LINE_RTS) != 0);
}

/*
 * Callbacks
 */

static void vcomDataTxCb(void) {
    /* assumes tx transactions are atomic 64 bytes (nearly certain they are) */
    countTx = 0;
}

#define EXC_RETURN 0xFFFFFFF9
#define DEFAULT_CPSR 0x61000000
static void vcomDataRxCb(void) {
    /* FIXME this is mad buggy */

    /* setEPRxCount on the previous cycle should garuntee
       we havnt received more bytes than we can fit */
    newBytes = usb_get_ep_rx_count(VCOM_RX_ENDP);
    usb_set_ep_rx_stat(VCOM_RX_ENDP, USB_EP_STAT_RX_NAK);

    /* magic number, {0x31, 0x45, 0x41, 0x46} is "1EAF" */
    uint8 chkBuf[4];
    uint8 cmpBuf[4] = {0x31, 0x45, 0x41, 0x46};
    if (reset_state == DTR_NEGEDGE) {
        reset_state = DTR_LOW;

        if  (newBytes >= 4) {
            unsigned int target = (unsigned int)usbWaitReset | 0x1;

            usb_copy_from_pma(chkBuf, 4, VCOM_RX_ADDR);

            int i;
            USB_Bool cmpMatch = TRUE;
            for (i = 0; i < 4; i++) {
                if (chkBuf[i] != cmpBuf[i]) {
                    cmpMatch = FALSE;
                }
            }

            if (cmpMatch) {
                asm volatile("mov r0, %[stack_top]      \n\t" // Reset stack
                             "mov sp, r0                \n\t"
                             "mov r0, #1                \n\t"
                             "mov r1, %[target_addr]    \n\t"
                             "mov r2, %[cpsr]           \n\t"
                             "push {r2}                 \n\t" // Fake xPSR
                             "push {r1}                 \n\t" // PC target addr
                             "push {r0}                 \n\t" // Fake LR
                             "push {r0}                 \n\t" // Fake R12
                             "push {r0}                 \n\t" // Fake R3
                             "push {r0}                 \n\t" // Fake R2
                             "push {r0}                 \n\t" // Fake R1
                             "push {r0}                 \n\t" // Fake R0
                             "mov lr, %[exc_return]     \n\t"
                             "bx lr"
                             :
                             : [stack_top] "r" (STACK_TOP),
                               [target_addr] "r" (target),
                               [exc_return] "r" (EXC_RETURN),
                               [cpsr] "r" (DEFAULT_CPSR)
                             : "r0", "r1", "r2");
                /* should never get here */
            }
        }
    }

    usb_copy_from_pma(vcomBufferRx, newBytes, VCOM_RX_ADDR);
}

static uint8* vcomGetSetLineCoding(uint16 length) {
    if (length == 0) {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(USB_Line_Coding);
    }
    return (uint8*)&line_coding;
}

static void usbInit(void) {
    pInformation->Current_Configuration = 0;

    USB_BASE->CNTR = USB_CNTR_FRES;

    USBLIB->irq_mask = 0;
    USB_BASE->CNTR = USBLIB->irq_mask;
    USB_BASE->ISTR = 0;
    USBLIB->irq_mask = USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM;
    USB_BASE->CNTR = USBLIB->irq_mask;

    USB_BASE->ISTR = 0;
    USBLIB->irq_mask = USB_ISR_MSK;
    USB_BASE->CNTR = USBLIB->irq_mask;

    nvic_irq_enable(NVIC_USB_LP_CAN_RX0);
    USBLIB->state = USB_UNCONNECTED;
}

/* choose addresses to give endpoints the max 64 byte buffers */
#define BTABLE_ADDRESS        0x00
static void usbReset(void) {
    pInformation->Current_Configuration = 0;

    /* current feature is current bmAttributes */
    pInformation->Current_Feature = (USB_CONFIG_ATTR_BUSPOWERED |
                                     USB_CONFIG_ATTR_SELF_POWERED);

    USB_BASE->BTABLE = BTABLE_ADDRESS;

    /* setup control endpoint 0 */
    usb_set_ep_type(USB_EP0, USB_EP_EP_TYPE_CONTROL);
    usb_set_ep_tx_stat(USB_EP0, USB_EP_STAT_TX_STALL);
    usb_set_ep_rx_addr(USB_EP0, VCOM_CTRL_RX_ADDR);
    usb_set_ep_tx_addr(USB_EP0, VCOM_CTRL_TX_ADDR);
    usb_clear_status_out(USB_EP0);

    usb_set_ep_rx_count(USB_EP0, pProperty->MaxPacketSize);
    usb_set_ep_rx_stat(USB_EP0, USB_EP_STAT_RX_VALID);

    /* setup management endpoint 1  */
    usb_set_ep_type(VCOM_NOTIFICATION_ENDP, USB_EP_EP_TYPE_INTERRUPT);
    usb_set_ep_tx_addr(VCOM_NOTIFICATION_ENDP, VCOM_NOTIFICATION_ADDR);
    usb_set_ep_tx_stat(VCOM_NOTIFICATION_ENDP, USB_EP_STAT_TX_NAK);
    usb_set_ep_rx_stat(VCOM_NOTIFICATION_ENDP, USB_EP_STAT_RX_DISABLED);

    /* TODO figure out differences in style between RX/TX EP setup */

    /* set up data endpoint OUT (RX) */
    usb_set_ep_type(VCOM_RX_ENDP, USB_EP_EP_TYPE_BULK);
    usb_set_ep_rx_addr(VCOM_RX_ENDP, 0x110);
    usb_set_ep_rx_count(VCOM_RX_ENDP, 64);
    usb_set_ep_rx_stat(VCOM_RX_ENDP, USB_EP_STAT_RX_VALID);

    /* set up data endpoint IN (TX)  */
    usb_set_ep_type(VCOM_TX_ENDP, USB_EP_EP_TYPE_BULK);
    usb_set_ep_tx_addr(VCOM_TX_ENDP, VCOM_TX_ADDR);
    usb_set_ep_tx_stat(VCOM_TX_ENDP, USB_EP_STAT_TX_NAK);
    usb_set_ep_rx_stat(VCOM_TX_ENDP, USB_EP_STAT_RX_DISABLED);

    USBLIB->state = USB_ATTACHED;
    SetDeviceAddress(0);

    /* reset the rx fifo */
    recvBufIn   = 0;
    recvBufOut  = 0;
    maxNewBytes = VCOM_RX_EPSIZE;
    countTx     = 0;
}

static RESULT usbDataSetup(uint8 request) {
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
        default:
            break;
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

static RESULT usbNoDataSetup(uint8 request) {
    uint8 new_signal;

    /* we support set com feature but dont handle it */
    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) {

        switch (request) {
        case (SET_COMM_FEATURE):
            return USB_SUCCESS;
        case (SET_CONTROL_LINE_STATE):
            /* to reset the board, pull both dtr and rts low
               then pulse dtr by itself */
            new_signal = (pInformation->USBwValues.bw.bb0 &
                          (CONTROL_LINE_DTR | CONTROL_LINE_RTS));
            line_dtr_rts = new_signal & 0x03;

            switch (reset_state) {
                /* no default, covered enum */
            case DTR_UNSET:
                if ((new_signal & CONTROL_LINE_DTR) == 0 ) {
                    reset_state = DTR_LOW;
                } else {
                    reset_state = DTR_HIGH;
                }
                break;

            case DTR_HIGH:
                if ((new_signal & CONTROL_LINE_DTR) == 0 ) {
                    reset_state = DTR_NEGEDGE;
                } else {
                    reset_state = DTR_HIGH;
                }
                break;

            case DTR_NEGEDGE:
                if ((new_signal & CONTROL_LINE_DTR) == 0 ) {
                    reset_state = DTR_LOW;
                } else {
                    reset_state = DTR_HIGH;
                }
                break;

            case DTR_LOW:
                if ((new_signal & CONTROL_LINE_DTR) == 0 ) {
                    reset_state = DTR_LOW;
                } else {
                    reset_state = DTR_HIGH;
                }
                break;
            }

            return USB_SUCCESS;
        }
    }
    return USB_UNSUPPORT;
}

static RESULT usbGetInterfaceSetting(uint8 interface, uint8 alt_setting) {
    if (alt_setting > 0) {
        return USB_UNSUPPORT;
    } else if (interface > 1) {
        return USB_UNSUPPORT;
    }

    return USB_SUCCESS;
}

static uint8* usbGetDeviceDescriptor(uint16 length) {
    return Standard_GetDescriptorData(length, &Device_Descriptor);
}

static uint8* usbGetConfigDescriptor(uint16 length) {
    return Standard_GetDescriptorData(length, &Config_Descriptor);
}

static uint8* usbGetStringDescriptor(uint16 length) {
    uint8 wValue0 = pInformation->USBwValue0;

    if (wValue0 > 2) {
        return NULL;
    }
    return Standard_GetDescriptorData(length, &String_Descriptor[wValue0]);
}

static void usbSetConfiguration(void) {
    if (pInformation->Current_Configuration != 0) {
        USBLIB->state = USB_CONFIGURED;
    }
}

static void usbSetDeviceAddress(void) {
    USBLIB->state = USB_ADDRESSED;
}

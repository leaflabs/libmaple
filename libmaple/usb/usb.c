/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
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
 * @file usb.c
 * @brief USB support.
 */

#include "usb.h"

#include "libmaple.h"
#include "gpio.h"
#include "delay.h"
#include "nvic.h"
#include "rcc.h"

#include "usb_reg_map.h"
#include "usb_config.h"
#include "usb_callbacks.h"

#include "usb_type.h"
#include "usb_core.h"

static void usb_init(void);
static void dispatch_ctr_lp(void);

/*
 * Globals required by usb_lib/
 */

DEVICE Device_Table =
    {NUM_ENDPTS,
     1};

DEVICE_PROP Device_Property =
    {usbInit,
     usbReset,
     usbStatusIn,
     usbStatusOut,
     usbDataSetup,
     usbNoDataSetup,
     usbGetInterfaceSetting,
     usbGetDeviceDescriptor,
     usbGetConfigDescriptor,
     usbGetStringDescriptor,
     0,
     bMaxPacketSize};

USER_STANDARD_REQUESTS User_Standard_Requests =
    {NOP_Process,
     usbSetConfiguration,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     usbSetDeviceAddress};

void (*pEpInt_IN[7])(void) =
    {vcomDataTxCb,
     vcomManagementCb,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process};

void (*pEpInt_OUT[7])(void) =
    {NOP_Process,
     NOP_Process,
     vcomDataRxCb,
     NOP_Process,
     NOP_Process,
     NOP_Process,
     NOP_Process};

volatile uint16 wIstr = 0;
uint8 EPindex;                  /* current endpoint */
DEVICE_INFO *pInformation;
DEVICE_PROP *pProperty;
uint16 SaveTState;              /* caches TX status for later use */
uint16 SaveRState;              /* caches RX status for later use */
uint16 wInterrupt_Mask;
DEVICE_INFO Device_Info;
USER_STANDARD_REQUESTS *pUser_Standard_Requests;

/*
 * Other state
 */

volatile uint32 bDeviceState = UNCONNECTED;
volatile uint32 bIntPackSOF = 0;

struct {
  volatile RESUME_STATE eState;
  volatile uint8 bESOFcnt;
} ResumeS;

/*
 * Routines
 */

void usb_cdcacm_enable(gpio_dev *disc_dev, uint8 disc_bit) {
  /* Present ourselves to the host */
  gpio_set_mode(disc_dev, disc_bit, GPIO_OUTPUT_PP);
  gpio_write_bit(disc_dev, disc_bit, 0); // presents us to the host

  /* initialize USB peripheral */
  usb_init();
}

void usb_cdcacm_disable(gpio_dev *disc_dev, uint8 disc_bit) {
  // These are just guesses about how to do this, but it seems to work.
  // TODO: verify this with USB spec
  nvic_irq_disable(NVIC_USB_LP_CAN_RX0);
  gpio_write_bit(disc_dev, disc_bit, 1);
}

void usbSuspend(void) {
  uint16 cntr;

  /* TODO decide if read/modify/write is really what we want
   * (e.g. usbResumeInit() reconfigures CNTR). */
  cntr = USB_BASE->CNTR;
  cntr |= USB_CNTR_FSUSP;
  USB_BASE->CNTR = cntr;
  cntr |= USB_CNTR_LP_MODE;
  USB_BASE->CNTR = cntr;

  bDeviceState = SUSPENDED;
}

void usbResumeInit(void) {
  uint16 cntr;

  cntr = USB_BASE->CNTR;
  cntr &= ~USB_CNTR_LP_MODE;
  USB_BASE->CNTR = cntr;

  /* Enable interrupt lines */
  USB_BASE->CNTR = ISR_MSK;
}

void usbResume(RESUME_STATE eResumeSetVal) {
  uint16 cntr;

  if (eResumeSetVal != RESUME_ESOF)
    ResumeS.eState = eResumeSetVal;

  switch (ResumeS.eState)
    {
    case RESUME_EXTERNAL:
      usbResumeInit();
      ResumeS.eState = RESUME_OFF;
      break;
    case RESUME_INTERNAL:
      usbResumeInit();
      ResumeS.eState = RESUME_START;
      break;
    case RESUME_LATER:
      ResumeS.bESOFcnt = 2;
      ResumeS.eState = RESUME_WAIT;
      break;
    case RESUME_WAIT:
      ResumeS.bESOFcnt--;
      if (ResumeS.bESOFcnt == 0)
        ResumeS.eState = RESUME_START;
      break;
    case RESUME_START:
      cntr = USB_BASE->CNTR;
      cntr |= USB_CNTR_RESUME;
      USB_BASE->CNTR = cntr;
      ResumeS.eState = RESUME_ON;
      ResumeS.bESOFcnt = 10;
      break;
    case RESUME_ON:
      ResumeS.bESOFcnt--;
      if (ResumeS.bESOFcnt == 0) {
          cntr = USB_BASE->CNTR;
          cntr &= ~USB_CNTR_RESUME;
          USB_BASE->CNTR = cntr;
          ResumeS.eState = RESUME_OFF;
      }
      break;
    case RESUME_OFF:
    case RESUME_ESOF:
    default:
      ResumeS.eState = RESUME_OFF;
      break;
    }
}

void __irq_usb_lp_can_rx0(void) {
  wIstr = USB_BASE->ISTR;

  /* Use ISR_MSK to only include code for bits we care about. */

#if (ISR_MSK & USB_ISTR_RESET)
  if (wIstr & USB_ISTR_RESET & wInterrupt_Mask) {
    USB_BASE->ISTR = ~USB_ISTR_RESET;
    Device_Property.Reset();
  }
#endif

#if (ISR_MSK & USB_ISTR_PMAOVR)
  if (wIstr & ISTR_PMAOVR & wInterrupt_Mask) {
    USB_BASE->ISTR = ~USB_ISTR_PMAOVR;
  }
#endif

#if (ISR_MSK & USB_ISTR_ERR)
  if (wIstr & USB_ISTR_ERR & wInterrupt_Mask) {
    USB_BASE->ISTR = ~USB_ISTR_ERR;
  }
#endif

#if (ISR_MSK & USB_ISTR_WKUP)
  if (wIstr & USB_ISTR_WKUP & wInterrupt_Mask) {
    USB_BASE->ISTR = ~USB_ISTR_WKUP;
    usbResume(RESUME_EXTERNAL);
  }
#endif

#if (ISR_MSK & USB_ISTR_SUSP)
  if (wIstr & USB_ISTR_SUSP & wInterrupt_Mask) {
    /* check if SUSPEND is possible */
    if (F_SUSPEND_ENABLED) {
        usbSuspend();
    } else {
        /* if not possible then resume after xx ms */
        usbResume(RESUME_LATER);
    }
    /* clear of the ISTR bit must be done after setting of CNTR_FSUSP */
    USB_BASE->ISTR = ~USB_ISTR_SUSP;
}
#endif

#if (ISR_MSK & USB_ISTR_SOF)
  if (wIstr & USB_ISTR_SOF & wInterrupt_Mask) {
    USB_BASE->ISTR = ~USB_ISTR_SOF;
    bIntPackSOF++;
  }
#endif

#if (ISR_MSK & USB_ISTR_ESOF)
  if (wIstr & USB_ISTR_ESOF & wInterrupt_Mask) {
    USB_BASE->ISTR = ~USB_ISTR_ESOF;
    /* resume handling timing is made with ESOFs */
    usbResume(RESUME_ESOF); /* request without change of the machine state */
  }
#endif

  /*
   * Service the correct transfer interrupt.
   */

#if (ISR_MSK & USB_ISTR_CTR)
  if (wIstr & USB_ISTR_CTR & wInterrupt_Mask) {
    dispatch_ctr_lp();
  }
#endif
}

void usbWaitReset(void) {
  delay_us(RESET_DELAY);
  nvic_sys_reset();
}

/* This low-level send bytes function is NON-BLOCKING; blocking behavior, with
 * a timeout, is implemented in usercode (or in the Wirish C++ high level
 * implementation).
 *
 * This function will quickly copy up to 64 bytes of data (out of an
 * arbitrarily large buffer) into the USB peripheral TX buffer and return the
 * number placed in that buffer. It is up to usercode to divide larger packets
 * into 64-byte chunks to guarantee delivery.
 *
 *
 */
void usbBlockingSendByte(char ch) {
    while (countTx);
    UserToPMABufferCopy((uint8*)&ch,VCOM_TX_ADDR,1);
    _SetEPTxCount(VCOM_TX_ENDP,1);
    _SetEPTxValid(VCOM_TX_ENDP);
    countTx = 1;
    while (countTx);
}

uint32 usbSendBytes(const uint8* sendBuf, uint32 len) {
  /* Last transmission hasn't finished, abort */
  if (countTx) {
    return 0;
  }

  // We can only put VCOM_TX_EPSIZE bytes in the buffer
  /* FIXME XXX then why are we only copying half as many? */
  if (len > VCOM_TX_EPSIZE / 2) {
    len = VCOM_TX_EPSIZE / 2;
  }

  // Try to load some bytes if we can
  if (len) {
    usb_copy_to_pma(sendBuf, len, VCOM_TX_ADDR);
    usb_set_ep_tx_count(VCOM_TX_ENDP, len);
    countTx += len;
    usb_set_ep_tx_stat(VCOM_TX_ENDP, USB_EP_STAT_TX_VALID);
  }

  return len;
}

/* returns the number of available bytes are in the recv FIFO */
uint32 usbBytesAvailable(void) {
  return newBytes;
}

/* Nonblocking byte receive.
 *
 * Copies up to len bytes from the local recieve FIFO (*NOT* the PMA)
 * into recvBuf and deq's the FIFO. */
uint32 usbReceiveBytes(uint8* recvBuf, uint32 len) {
  static int offset = 0;

  if (len > newBytes) {
      len = newBytes;
  }

  int i;
  for (i=0;i<len;i++) {
      recvBuf[i] = (uint8)(vcomBufferRx[i+offset]);
  }

  newBytes -= len;
  offset += len;

  /* Re-enable the RX endpoint, which we had set to receive 0 bytes */
  if (newBytes == 0) {
    usb_set_ep_rx_count(VCOM_RX_ENDP,VCOM_RX_EPSIZE);
    usb_set_ep_rx_stat(VCOM_RX_ENDP, USB_EP_STAT_RX_VALID);
    offset = 0;
  }

  return len;
}

uint8 usbGetDTR() {
  return ((line_dtr_rts & CONTROL_LINE_DTR) != 0);
}

uint8 usbGetRTS() {
  return ((line_dtr_rts & CONTROL_LINE_RTS) != 0);
}

uint8 usbIsConfigured() {
  return (bDeviceState == CONFIGURED);
}

uint8 usbIsConnected() {
  return (bDeviceState != UNCONNECTED);
}

uint16 usbGetPending() {
  return countTx;
}

/*
 * Auxiliary routines
 */

static void usb_init(void) {    /* TODO make a public, improved version */
    rcc_clk_enable(RCC_USB);

    pInformation = &Device_Info;
    pInformation->ControlState = 2;
    pProperty = &Device_Property;
    pUser_Standard_Requests = &User_Standard_Requests;
    pProperty->Init();
}

static inline uint8 dispatch_endpt_zero(void);
static inline void dispatch_endpt(uint8 ep);
static inline void set_rx_tx_status0(uint16 rx, uint16 tx);

static void handle_setup0(void);
static void handle_in0(void);
static void handle_out0(void);

static void dispatch_ctr_lp(void) {
    while (((wIstr = USB_BASE->ISTR) & USB_ISTR_CTR) != 0) {
        /* TODO WTF, figure this out: RM0008 says CTR is read-only,
         * but ST's firmware claims it's clear-only, and emphasizes
         * the importance of clearing it in more than one place. */
        USB_BASE->ISTR = ~USB_ISTR_CTR;
        uint8 ep_id = wIstr & USB_ISTR_EP_ID;
        if (ep_id == 0) {
            /* TODO figure out why it's OK to break out of the loop
             * once we're done serving endpoint zero, but not okay if
             * there are multiple nonzero endpoint transfers to
             * handle. */
            if (dispatch_endpt_zero())
                return;
        } else {
            dispatch_endpt(ep_id);
        }
    }
}

/* FIXME Dataflow on endpoint 0 RX/TX status is based off of ST's
 * code, and is ugly/confusing in its use of SaveRState/SaveTState.
 * Fixing this requires filling in handle_in0(), handle_setup0(),
 * handle_out0(). */
static inline uint8 dispatch_endpt_zero(void) {
    uint32 epr = (uint16)USB_BASE->EP[0];

    if (!(epr & (USB_EP_CTR_TX | USB_EP_SETUP | USB_EP_CTR_RX))) {
        return 0;
    }

    /* Cache RX/TX statuses in SaveRState/SaveTState, respectively.
     * The various handle_foo0() may clobber these values
     * before we reset them at the end of this routine. */
    SaveRState = epr & USB_EP_STAT_RX;
    SaveTState = epr & USB_EP_STAT_TX;

    /* Set actual RX/TX statuses to NAK while we're thinking */
    set_rx_tx_status0(USB_EP_STAT_RX_NAK, USB_EP_STAT_TX_NAK);

    if ((wIstr & USB_ISTR_DIR) == 0) {
        /* ST RM0008: "If DIR bit=0, CTR_TX bit is set in the USB_EPnR
         * register related to the interrupting endpoint.  The
         * interrupting transaction is of IN type (data transmitted by
         * the USB peripheral to the host PC)." */
        ASSERT_FAULT(epr & USB_EP_CTR_TX);
        usb_clear_ctr_tx(USB_EP0);
        handle_in0();
    } else {
        /* RM0008: "If DIR bit=1, CTR_RX bit or both CTR_TX/CTR_RX
         * are set in the USB_EPnR register related to the
         * interrupting endpoint. The interrupting transaction is of
         * OUT type (data received by the USB peripheral from the host
         * PC) or two pending transactions are waiting to be
         * processed."
         *
         * [mbolivar] Note how the following control flow (which
         * replicates ST's) doesn't seem to actually handle both
         * interrupts that are ostensibly pending when both CTR_RX and
         * CTR_TX are set.
         *
         * TODO sort this mess out.
         */
        if (epr & USB_EP_CTR_TX) {
            usb_clear_ctr_tx(USB_EP0);
            handle_in0();
        } else {                /* SETUP or CTR_RX */
            /* SETUP is held constant while CTR_RX is set, so clear it
             * either way */
            usb_clear_ctr_rx(USB_EP0);
            if (epr & USB_EP_SETUP) {
                handle_setup0();
            } else {            /* CTR_RX */
                handle_out0();
            }
        }
    }

    set_rx_tx_status0(SaveRState, SaveTState);
    return 1;
}

static inline void dispatch_endpt(uint8 ep) {
    uint32 epr = USB_BASE->EP[ep];
    /* If ISTR_CTR is set and the ISTR gave us this EP_ID to handle,
     * then presumably at least one of CTR_RX and CTR_TX is set, but
     * again, ST's control flow allows for the possibility of neither.
     *
     * TODO try to find out if neither being set is possible. */
    if (epr & USB_EP_CTR_RX) {
        usb_clear_ctr_rx(ep);
        (pEpInt_OUT[ep - 1])();
    }
    if (epr & USB_EP_CTR_TX) {
        usb_clear_ctr_tx(ep);
        (pEpInt_IN[ep - 1])();
    }
}

static inline void set_rx_tx_status0(uint16 rx, uint16 tx) {
    usb_set_ep_rx_stat(USB_EP0, rx);
    usb_set_ep_tx_stat(USB_EP0, tx);
}

/* TODO Rip out usb_lib/ dependency from the following functions: */

static void handle_setup0(void) {
    Setup0_Process();
}

static void handle_in0(void) {
    In0_Process();
}

static void handle_out0(void) {
    Out0_Process();
}

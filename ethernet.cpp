/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
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
 *  @file example_main.cpp
 *
 *  @brief Sample main.cpp file. Blinks an LED, sends a message out USART2
 *  and turns on PWM on pin 2
 */

#include "wirish.h"
#include "HardwareSerial.h"
#include "HardwareSPI.h"
#include "ethernet.h"

#define w5100_write(addr, data)         w5100_send_cmd(OPCODE_WRITE, addr, data)
#define w5100_read(addr)                w5100_send_cmd(OPCODE_READ, addr, 0xFF)

#define ETHERNET_DEBUG
//#define SPI_DEBUG

#ifdef ETHERNET_DEBUG
   #define ETH_DBG(...) iprintf(__VA_ARGS__)
#else
   #define ETH_DBG(...)
#endif

#define SS 10

HardwareSPI spi(1);

static void  ethernet(void);
static uint8 w5100_send_cmd(uint8 opcode, uint16 addr, uint8 data);
static void  w5100_reset(void);
static void  w5100_get_info(void);
static void  w5100_write_buf(uint16 addr, uint8 *buf, uint8 len);
static void  w5100_read_buf(uint16 addr, uint8 *buf, uint8 len);
static void  setup_socket(void);

void setup()
{
   pinMode(SS, OUTPUT);
   digitalWrite(SS, HIGH);
   spi.begin();

   Serial2.begin(115200);
   iprintf("Wiznet initialization...\n");
}

void loop() {
   ethernet();
}

uint8 GATEWAY[] = {192, 168,   1,   1};
uint8 IP[]      = {192, 168,   1,  28};
uint8 SUBNET[]  = {255, 255, 255,   0};
uint8 MAC[]     = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE};

/* 1. Mode Register MR
 * 2. Interrupt Mask Register (IMR)
 * 3. Retry Time-value Register (RTR)
 * 4. Retry Count Register (RCR)
 *
 * Settings network information:
 * 1. Gateway Adress Register (GAR)
 * 2. Source Hardware Address Register (SHAR)
 * 3. Subnet Mask Register (SUBR)
 * 4. Source IP Address Register (SIPR) 
 *
 * Set socket memory information.*/

void ethernet(void) {
   w5100_reset();

   /* Set gateway, subnet, ip, mac address  */
   w5100_write_buf(GAR, GATEWAY, 4);
   w5100_write_buf(SUBR, SUBNET, 4);
   w5100_write_buf(SIPR, IP, 4);
   w5100_write_buf(SHAR, MAC, 6);

   /* set socket memory information  */
   w5100_send_cmd(OPCODE_WRITE, RMSR, 0x55);
   w5100_send_cmd(OPCODE_WRITE, TMSR, 0x55);


   w5100_get_info();

   setup_socket();
   while (1) {
      delay(1000);
   }
}

static void setup_socket(void) {
   uint8 rc;
   uint16 bytesAvailable = 0;

   ETH_DBG("setup_socket()\n");
   /* In order to initalize a socket, set the operation mode and port of the socket
    * and provide OPEN command to teh comnand register of the socket.
    * Set Sn_MR
    * Set Source Port Register
    * Set Command register
    *
    * Initialize a socket as TCP:
    * START:
    * Sn_MR = 0x01;
    * Sn_PORT = port
    * Sn_CR = OPEN
    * if (Sn_SR != SOCK_INIT) 
    *   SnCR = CLOSE
    *   goto START
    *
    * LISTEN:
    * Sn_CR = listen
    * if Sn_SR != SOCK_LISTEN)
    *   SnCR = CLOSE
    *   goto LISTEN
    *
    * ESTABLISHED?:
    * if (sn_SR == SOCK_ESTABLISHED)
    *   goto ESTABLISHED stage*/

   /* set tcp, port 80 */
   w5100_write(SOCKET0_BASE + SN_MR, 0x01);
   w5100_write(SOCKET0_BASE + SN_PORT0, 0x00);
   w5100_write(SOCKET0_BASE + SN_PORT1, 80);  // low byte

   /* open */
   ETH_DBG("open()\n");
   w5100_write(SOCKET0_BASE + SN_CR, CR_OPEN);
   rc = w5100_read(SOCKET0_BASE + SN_SR);
   ETH_DBG("SR: 0x%0x\n", rc);

   /* listen  */
   ETH_DBG("listen()\n");
   w5100_write(SOCKET0_BASE + SN_CR, CR_LISTEN);
   rc = w5100_read(SOCK_ADDR(0, SN_SR));
   ETH_DBG("SR: 0x%0x\n", rc);

   /* wait for connection  */
   while(1) {
      if (w5100_read(SOCK_ADDR(0, SN_SR)) == SOCK_ESTABLISHED) {
         ETH_DBG("Connection received\n");
         break;
      }
   }
   /* wait for data  */
   while (!bytesAvailable) {
      bytesAvailable += (w5100_read(SOCK_ADDR(0, SN_RX_RSR0)) << 8);
      bytesAvailable += w5100_read(SOCK_ADDR(0, SN_RX_RSR1));
   }

   ETH_DBG("recv: %u bytes\n", bytesAvailable);
}

static void w5100_get_info(void) {
   uint8 gw[4];
   uint8 ip[4];
   uint8 subnet[4];
   uint8 mac[6];

   w5100_read_buf(GAR0, gw, 4);
   w5100_read_buf(SIPR0, ip, 4);
   w5100_read_buf(SUBR0, subnet, 4);
   w5100_read_buf(SHAR0, mac, 6);

   ETH_DBG("IP: %u.%u.%u.%u\n", ip[0], ip[1], ip[2], ip[3]);
   ETH_DBG("Gateway: %u.%u.%u.%u\n", gw[0], gw[1], gw[2], gw[3]);
   ETH_DBG("Subnet: %u.%u.%u.%u\n", subnet[0], subnet[1], subnet[2], subnet[3]);
   ETH_DBG("MAC: %X:%X:%X:%X:%X:%X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static void w5100_reset(void) {
   w5100_write(MR, MR_RST);
}

static void w5100_write_buf(uint16 addr, uint8 *buf, uint8 len) {
   uint32 i;
   for (i = 0; i < len; i++) {
      w5100_write(addr + i, buf[i]);
   }
}

static void w5100_read_buf(uint16 addr, uint8 *buf, uint8 len) {
   uint32 i;
   for (i = 0; i < len; i++) {
      buf[i] = w5100_read(addr + i);
   }
}

static uint8 w5100_send_cmd(uint8 opcode, uint16 addr, uint8 data) {
   uint8 buf[4];
   uint8 rc = 0;

   buf[0] = opcode;
   buf[1] = (addr >> 8);
   buf[2] = (addr & 0xFF);
   buf[3] = data;

   digitalWrite(SS, LOW);
   rc = spi.send(buf, 4);
   digitalWrite(SS, HIGH);

#ifdef SPI_DEBUG
   if (opcode == OPCODE_WRITE) {
      iprintf("\tWrite: 0x%04x = 0x%x\n", addr, data);
   } else {
      iprintf("\tRead: 0x%04x = 0x%x\n", addr, rc);
   }
#endif

   return rc;
}


int main(void) {
   init();
   setup();

   while (1) {
      loop();
   }
   return 0;
}

/* Required for C++ hackery */
/* TODO: This really shouldn't go here... move it later
 * */
extern "C" void __cxa_pure_virtual(void) {
   while(1)
      ;
}

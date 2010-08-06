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
 *  @brief Sample main.cpp file. Sends "Hello world!" out SPI1.
 *
 *  SPI1 is set up to be a master transmitter at 4.5MHz, little endianness,
 *  and SPI mode 0.
 *
 *  Pin 10 is used as Chip Select
 *
 */

#include "wirish.h"
#include "fsmc.h"
#include "rcc.h"
#include "gpio.h"

#define LED_PIN 23
#define DISC_PIN 14

// System control block registers
#define SCB_BASE    (SCB_Reg*)(0xE000ED00)

typedef struct {
    volatile uint32 CPUID;
    volatile uint32 ICSR;
    volatile uint32 VTOR;
    volatile uint32 AIRCR;
    volatile uint32 SCR;
    volatile uint32 CCR;
    volatile uint32 SHPR1;
    volatile uint32 SHPR2;
    volatile uint32 SHPR3;
    volatile uint32 SHCRS;
    volatile uint32 CFSR;
    volatile uint32 HFSR;
    uint32 pad1;   
    volatile uint32 MMAR;
    volatile uint32 BFAR;
} SCB_Reg;

SCB_Reg *scb; 

uint16 *ptr;
int toggle = 0;

void setup() {
   uint32 id;
   scb = (SCB_Reg*)SCB_BASE;

   rcc_enable_clk_fsmc();

   pinMode(LED_PIN, OUTPUT);
   pinMode(DISC_PIN, OUTPUT);
   digitalWrite(DISC_PIN,1);
   digitalWrite(LED_PIN,1);

   Serial1.begin(9600);
   Serial1.println("Hello World!");

   Serial1.print("Init... ");
   fsmc_native_sram_init();
   Serial1.println("Done.");


   ptr = (uint16*)(0x60000000);
   //ptr = (uint16*)(0x68000000);
   //ptr = (uint16*)(0x80000000);
   Serial1.print("Writing... ");

   *ptr = 0xFFFF;
   Serial1.println("Done.");

   Serial1.print("Reading... ");
   id = *ptr;
   Serial1.print("Done: ");
   Serial1.println(id,BIN);

   /*
   Serial1.print("CPUID is at: ");
   id = (uint32)(&(scb->CPUID));
   Serial1.println(id,BIN);
   */

   Serial1.print("CPUID: ");
   id = scb->CPUID;
   Serial1.println(id,BIN);
   Serial1.print("ICSR:  ");
   id = scb->ICSR;
   Serial1.println(id,BIN);
   Serial1.print("CFSR:  ");
   id = scb->CFSR;
   Serial1.println(id,BIN);
   Serial1.print("HFSR:  ");
   id = scb->HFSR;
   Serial1.println(id,BIN);
   Serial1.print("MMAR:  ");
   id = scb->MMAR;
   Serial1.println(id,BIN);
   Serial1.print("BFAR:  ");
   id = scb->BFAR;
   Serial1.println(id,BIN);

}

void loop() {
   digitalWrite(LED_PIN, toggle);
   toggle ^= 1;
   delay(100);

   *ptr = 0xFFFF;
   /*
   Serial1.print((uint32)(ptr),HEX);
   Serial1.print(": ");
   Serial1.println(*ptr,BIN);
   */
}

int main(void) {
   init();
   setup();

   while (1) {
      loop();
   }
   return 0;
}

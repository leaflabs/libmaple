
#include "wirish.h"
#include "fsmc.h"

#define LED_PIN  23 // hack for maple native
#define DISC_PIN 14 // hack for USB on native

// System control block registers
#define SCB_BASE    (SCB_Reg*)(0xE000ED00)

// This stuff should ultimately get moved to util.h or scb.h or w/e. 
// Also in interactive test program and the HardFault IRQ handler.
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
int count = 0;

void setup() {
   uint32 id;
   scb = (SCB_Reg*)SCB_BASE;

   pinMode(LED_PIN, OUTPUT);
   pinMode(DISC_PIN, OUTPUT);
   digitalWrite(DISC_PIN,1);
   digitalWrite(LED_PIN,1);

   Serial1.begin(9600);
   Serial1.println("Hello World!");

   Serial1.print("Init... ");
   fsmc_native_sram_init();
   Serial1.println("Done.");

   // Start of channel1 SRAM bank (through to 0x63FFFFFF, though only a chunk
   // of this is valid)
   ptr = (uint16*)(0x60000000);

   Serial1.print("Writing... ");
   *ptr = 0x1234;
   Serial1.println("Done.");

   Serial1.print("Reading... ");
   id = *ptr;
   Serial1.print("Done: ");     // shouldn't be 0xFFFFFFFF
   Serial1.println(id,BIN);

   Serial1.println("Dumping System Control Block Registers");
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
    
   Serial1.println("Now testing all memory addresses... (will hardfault at the end)");
   delay(3000);
}

void loop() {
   digitalWrite(LED_PIN, toggle);
   toggle ^= 1;
   delay(1);

   for(int i = 0; i<100; i++) {   // modify this to speed things up
        count++;
        ptr++;
        //delay(10);    // tweak this to test SRAM resiliance over time
        *ptr = (0x0000FFFF & count);
        if(*ptr != (0x0000FFFF & count)) {
                Serial1.println("ERROR: mismatch, halting");
                while(1) { }
        }
   }
   
   Serial1.print((uint32)(ptr),HEX);
   Serial1.print(": ");
   Serial1.println(*ptr,BIN);
}

int main(void) {
   init();
   setup();

   while (1) {
      loop();
   }
   return 0;
}

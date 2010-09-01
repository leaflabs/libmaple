
#include "wirish.h"
#include "fsmc.h"
#include "rcc.h"
#include "gpio.h"
#include "dac.h"

#define LED_PIN  23 // hack for maple native
#define DISC_PIN 14 // hack for USB on native

int toggle = 0;
uint16 count = 0;

void setup() {

   pinMode(LED_PIN, OUTPUT);
   pinMode(DISC_PIN, OUTPUT);
   digitalWrite(DISC_PIN,1);
   digitalWrite(LED_PIN,1);

   Serial1.begin(9600);
   Serial1.println("Hello World!");

   Serial1.print("Init... ");
   dac_init();
   Serial1.println("Done.");
}

void loop() {
   digitalWrite(LED_PIN, toggle);
   toggle ^= 1;
   delay(100);

   count += 100;

   if(count > 4095) {
      count = 0;
   }

   dac_write(1, 2048);
   dac_write(2, count);
}

int main(void) {
   init();
   setup();

   while (1) {
      loop();
   }
   return 0;
}


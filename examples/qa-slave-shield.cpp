// slave mode for QA shield

#include "wirish.h"

#define LED_PIN 13
#define NUM_GPIO 38 // not the number of the max...

int i;

void setup()
{
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 1);

    for(i=0; i<NUM_GPIO; i++) {
        if(i==13) { continue; }
        pinMode(i, OUTPUT);
        digitalWrite(i,0);
    }
    //delay(5000);
    SerialUSB.println("OK, starting...");

}

void loop() {
    digitalWrite(LED_PIN,1);
    delay(100);
    digitalWrite(LED_PIN,0);

    for(i=0; i<NUM_GPIO; i++) {
        if(i==13) { continue; }
        digitalWrite(i,1);
        delay(5);
        digitalWrite(i,0);
        delay(5);
    }
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated object that need libmaple may fail.
 __attribute__(( constructor )) void premain() {
    init();
}

int main(void)
{
    setup();

    while (1) {
        loop();
    }
    return 0;
}


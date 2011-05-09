// Blinks the LED, pin 13

#include "wirish.h"

// Use the pin attached to the built-in LED
#define PIN BOARD_LED_PIN

void setup() {
    pinMode(PIN, OUTPUT);
}

int toggle = 1;

void loop() {
    // You could just use toggleLED() instead, but this illustrates
    // the use of digitalWrite():
    digitalWrite(PIN, toggle);
    toggle ^= 1;
    delay(100);
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated object that need libmaple may fail.
 __attribute__(( constructor )) void premain() {
    init();
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}

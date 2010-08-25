// Blinks the LED, pin 13

#include "wirish.h"

#define TEST_PIN 13

void setup() {
    pinMode(TEST_PIN, OUTPUT);
}

int toggle = 1;

void loop() {
    digitalWrite(TEST_PIN, toggle);
    toggle ^= 1;
    delay(100);
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

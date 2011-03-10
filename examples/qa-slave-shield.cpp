// Slave mode for QA shield

#include "wirish.h"

// FIXME generalize for Maple Native, Maple Mini (NUM_GPIO, Mini USB
// breakout pins, etc.)

#define LED_PIN BOARD_LED_PIN
#define NUM_GPIO 38 // Ignore JTAG pins.

void setup() {
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    for(int i = 0; i < NUM_GPIO; i++) {
        if (i == BOARD_LED_PIN) {
            continue;
        }
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    SerialUSB.println("OK, starting...");
}

void loop() {
    toggleLED();
    delay(100);
    toggleLED();

    for(int i = 0; i < NUM_GPIO; i++) {
        if (i == BOARD_LED_PIN) {
            continue;
        }
        togglePin(i);
        delay(5);
        togglePin(i);
        delay(5);
    }
}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}


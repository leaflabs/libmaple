// Slave mode for QA shield

#include "wirish.h"

#define LED_PIN BOARD_LED_PIN

#if defined(BOARD_maple) || defined(BOARD_maple_RET6)
const uint8 pins_to_skip[] = {LED_PIN};

#elif defined(BOARD_maple_mini)
#define USB_DP 23
#define USB_DM 24
const uint8 pins_to_skip[] = {LED_PIN, USB_DP, USB_DM};

#elif defined(BOARD_maple_native)
const uint8 pins_to_skip[] = {LED_PIN};

#else
#error "Board type has not been selected correctly."
#endif

bool skip_pin_p(uint8 pin);

void setup() {
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    for(int i = 0; i < NR_GPIO_PINS; i++) {
        if (skip_pin_p(i)) {
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

    for(int i = 0; i < NR_GPIO_PINS; i++) {
        if (skip_pin_p(i)) {
            continue;
        }
        togglePin(i);
        delay(5);
        togglePin(i);
        delay(5);
    }
}

bool skip_pin_p(uint8 pin) {
    for (uint8 i = 0; i < sizeof(pins_to_skip); i++) {
        if (pin == pins_to_skip[i])
            return true;
    }
    return false;
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


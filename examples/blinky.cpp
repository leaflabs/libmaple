// Blinks the built-in LED

#include <wirish/wirish.h>

void setup() {
    pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop() {
    togglePin(BOARD_LED_PIN);
    delay(100);
}

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }
    return 0;
}

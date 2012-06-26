// Simple serial port "echo". Send back any received data.

#include <wirish/wirish.h>

// Note: you can change "Serial1" to any other serial port you have on
// your board.

void setup() {
    Serial1.begin(115200);
}

void loop() {
    while (Serial1.available()) {
        Serial1.write(Serial1.read());
    }
}

// Force init() to be called before anything else.
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

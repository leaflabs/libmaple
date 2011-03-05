#include "wirish.h"
#include "dac.h"

uint16 count = 0;

void setup() {

    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN,1);

    Serial1.begin(9600);
    Serial1.println("**** Beginning DAC test");

    Serial1.print("Init... ");
    dac_init();
    Serial1.println("Done.");
}

void loop() {
    toggleLED();
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


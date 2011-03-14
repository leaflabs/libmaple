// Sample i2c master example for development i2c branch. Writes 0-63 to
// addresses 0-63 on a 24LC256 EEPROM, then reads them back.

#include <string.h>
#include "wirish.h"
#include "i2c.h"

static const uint8 slave_address = 0b1010001;

#define NR_ELEMENTS 64
uint8 buf0[NR_ELEMENTS + 2] = {0x0, 0x0};
uint8 buf1[] = {0x0, 0x0};
uint8 buf2[NR_ELEMENTS];

i2c_msg msgs[3];

void toggle(void) {
    digitalWrite(2, HIGH);
    digitalWrite(2, LOW);
}

void setup() {
    uint32 bytes = 1;
    uint32 i;
    int32 rc = -1;

    pinMode(BOARD_LED_PIN, OUTPUT);
    Serial2.begin(9600);
    Serial2.println("Hello!");

    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);

    for (i = 2; i < sizeof buf0; i++) {
        buf0[i] = i - 2;
    }

    i2c_master_enable(I2C1, 0);

    while (bytes < 64) {
        Serial2.print("Writing ");
        Serial2.print(bytes);
        Serial2.print(" bytes...");

        /* Write test pattern  */
        msgs[0].addr = slave_address;
        msgs[0].flags = 0;
        msgs[0].length = 2+ bytes;
        msgs[0].data = buf0;
        i2c_master_xfer(I2C1, msgs, 1);
        delay(5);

        /* Read it back */
        msgs[1].addr = slave_address;
        msgs[1].flags = 0;
        msgs[1].length = 2;
        msgs[1].data = buf1;
        /* Repeated start condition */
        msgs[2].addr = slave_address;
        msgs[2].flags = I2C_MSG_READ;
        msgs[2].length = bytes;
        msgs[2].data = buf2;
        i2c_master_xfer(I2C1, msgs + 1, 2);

        /* Compare */
        rc = memcmp(&buf0[2], buf2, bytes);
        if (rc == 0) {
            Serial2.println("good!");
        } else {
            Serial2.println("failed!");
        }

        delay(5);
        bytes++;
    }
}

int32 rc;

void loop() {
    toggleLED();
    delay(100);
    rc = i2c_master_xfer(I2C1, msgs + 1, 2);
    if (rc < 0) {
        Serial2.println("Failed transfer!");
        i2c_master_enable(I2C1, 0);
    }
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

#include <stdio.h>

#include "wirish.h"
#include "bkp.h"
#include "iwdg.h"

void print_bkp_contents();
void write_to_bkp(uint16 val);

void setup() {
    pinMode(BOARD_BUTTON_PIN, INPUT);

    Serial2.begin(9600);
    Serial2.println("*** Beginning BKP test");

    Serial2.println("Init...");
    bkp_init();
    Serial2.println("Done.");

    print_bkp_contents();
    write_to_bkp(10);
    print_bkp_contents();

    Serial2.println("Enabling backup writes.");
    bkp_enable_writes();
    write_to_bkp(20);
    print_bkp_contents();

    Serial2.println("Disabling backup writes.");
    bkp_disable_writes();
    write_to_bkp(30);
    print_bkp_contents();

    Serial2.println("Done testing backup registers; press button to enable "
                    "independent watchdog (in order to cause a reset).");
    waitForButtonPress(0);
    iwdg_init(IWDG_PRE_4, 1);
    Serial2.println();
}

void loop() {
}

void print_bkp_contents() {
    Serial2.println("Backup data register contents:");
    char buf[100];
    for (int i = 1; i <= NR_BKP_REGS; i++) {
        snprintf(buf, sizeof buf, "DR%d: %d ", i, bkp_read(i));
        Serial2.print(buf);
        if (i % 5 == 0) Serial2.println();
    }
    Serial2.println();
}

void write_to_bkp(uint16 val) {
    Serial2.print("Attempting to write ");
    Serial2.print(val);
    Serial2.println(" to backup registers...");
    for (int i = 1; i <= NR_BKP_REGS; i++) {
        bkp_write(i, val);
    }
    Serial2.println("Done.");
}

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}


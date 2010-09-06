// Tests the SysTick enable/disable functions
//
#include "wirish.h"
#include "systick.h"

#define LED_PIN 13
#define PWM_PIN  2
#define BUT     38

void setup()
{
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);

    /* Turn on PWM on pin PWM_PIN */
    pinMode(PWM_PIN, PWM);
    pwmWrite(PWM_PIN, 0x8000);

    pinMode(BUT, INPUT_PULLDOWN);
}

int toggle = 0;
long time = 0;

void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);

    // An artificial delay
    int16 i = 1;
    float j = 1;
    for(i=0; i<6553; i++) {
        j = sqrt(j) + 1; 
    }
        
    if(digitalRead(BUT)) {
        systick_disable();
    } else {
        systick_resume();
    }

    //SerialUSB.println(micros());      // there is a bug with this
    SerialUSB.println(millis());
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

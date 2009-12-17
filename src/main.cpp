#include "stm32f10x_map.h"
#include "stm32f10x_lib.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_usart.h"
#include "Serial.h"
#include "timers.h"
#include "wiring.h"
#include "util.h"
#include "systick.h"
#include "adc.h"
#include "gpio.h"
#include "pwm.h"
#include "ext_interrupts.h"
#include "usart.h"

void setup();
void loop();

int ledPin = 13;

void setup()
{
//    Serial1.begin(9600);
//    Serial1.println("setup start");

//    pinMode(ledPin, OUTPUT);
    pinMode(1, GPIO_MODE_AF_OUTPUT_PP);
    pinMode(0, INPUT);

    pinMode(ledPin, OUTPUT);

//    usart_init(2);


//    Serial1.println("setup end");
}

int toggle = 0;

void loop() {
    toggle ^= 1;
    digitalWrite(ledPin, toggle);
    delay(100);
}


int main(void)
{
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}


/* Implemented:
 * void pinMode(pin, mode) 
 * void digitalWrite(pin, value)
 * uint32_t digitalRead(pin)
 * uint32_t analogRead(pin)
 * void randomSeed(seed)
 * long random(max)
 * long random(min, max)
 * */

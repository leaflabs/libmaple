// Sample main.cpp file. Blinks an LED, sends a message out USART2
// and turns on PWM on pin 2

#include "wirish.h"

#define LED_PIN 13
#define PWM_PIN  2

void handler1(void);
void handler2(void);
void handler3(void);
void handler4(void);

int toggle = 0;
int t;

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
uint16 rate1 = 1000;
uint16 rate2 = 2000;
uint16 rate3 = 4000;
uint16 rate4 = 8000;
uint16 val1 = 10000;
uint16 val2 = 10000;
uint16 val3 = 10000;
uint16 val4 = 10000;

HardwareTimer Timers[] = {Timer1, Timer2, Timer3, Timer4};

void setup()
{
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);

    pinMode(38, INPUT);

    /* Send a message out USART2  */
    //SerialUSB.begin(9600);
    SerialUSB.println("Begining timer test...");
    for(int t=0; t<4; t++) {
        Timers[t].setChannel1Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel2Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel3Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel4Mode(TIMER_OUTPUTCOMPARE);
    }
}

void loop() {
    for(t=0; t<4; t++) {
        toggle ^= 1; digitalWrite(LED_PIN, toggle);
        delay(1000);
        SerialUSB.println("-----------------------------------------------------");
        SerialUSB.print("Testing Timer "); SerialUSB.println(t+1);
        count1 = count2 = count3 = count4 = 0;
        Timers[t].setChannel1Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel2Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel3Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel4Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].attachCompare1Interrupt(handler1);
        Timers[t].attachCompare2Interrupt(handler2);
        Timers[t].attachCompare3Interrupt(handler3);
        Timers[t].attachCompare4Interrupt(handler4);
        delay(5000);
        Timers[t].setChannel1Mode(TIMER_DISABLED);
        Timers[t].setChannel2Mode(TIMER_DISABLED);
        Timers[t].setChannel3Mode(TIMER_DISABLED);
        Timers[t].setChannel4Mode(TIMER_DISABLED);
        SerialUSB.print("Count1: "); SerialUSB.println(count1);
        SerialUSB.print("Count2: "); SerialUSB.println(count2);
        SerialUSB.print("Count3: "); SerialUSB.println(count3);
        SerialUSB.print("Count4: "); SerialUSB.println(count4);
    }
}

void handler1(void) {
    val1 += rate1;
    Timers[t].setCompare1(val1);
    count1++;
} 
void handler2(void) {
    val2 += rate2;
    Timers[t].setCompare2(val2);
    count2++;
} 
void handler3(void) {
    val3 += rate3;
    Timers[t].setCompare3(val3);
    count3++;
} 
void handler4(void) {
    val4 += rate4;
    Timers[t].setCompare4(val4);
    count4++;
} 


int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}

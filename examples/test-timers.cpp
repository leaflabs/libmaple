// Program to test the wirish timers implementation

#include "wirish.h"

#define LED_PIN 13

void handler1(void);
void handler2(void);
void handler3(void);
void handler4(void);

void handler3b(void);
void handler4b(void);

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

    // Setup the button as input
    pinMode(38, INPUT_PULLUP);

    /* Send a message out USART2  */
    //SerialUSB.begin(9600);
    SerialUSB.println("Begining timer test...");
    for(int t=0; t<4; t++) {
        Timers[t].setChannel1Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel2Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel3Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel4Mode(TIMER_OUTPUTCOMPARE);
    }
    
    // Wait for user to attach...
    delay(2000);
}

void loop() {
    SerialUSB.println("-----------------------------------------------------");
    SerialUSB.println("Testing setCount/getCount"); 
    SerialUSB.print("Timer1.getCount() = "); SerialUSB.println(Timer1.getCount());
    SerialUSB.println("Timer1.setCount(1234)");
    Timer1.setCount(1234);
    SerialUSB.print("Timer1.getCount() = "); SerialUSB.println(Timer1.getCount());
    // This tests whether the pause/resume functions work; when BUT is held
    // down Timer4 is in the "pause" state and the timer doesn't increment, so
    // the final counts should reflect the ratio of time that BUT was held down
    SerialUSB.println("-----------------------------------------------------");
    SerialUSB.println("Testing Pause/Resume; button roughly controls Timer4"); 
    count3 = 0;
    count4 = 0;
    Timer3.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer3.pause();
    Timer4.pause();
    Timer3.setCount(0);
    Timer4.setCount(0);
    Timer3.setOverflow(30000);
    Timer4.setOverflow(30000);
    Timer3.setCompare1(1000);
    Timer4.setCompare1(1000);
    Timer3.attachCompare1Interrupt(handler3b);
    Timer4.attachCompare1Interrupt(handler4b);
    Timer3.resume();
    Timer4.resume();
    SerialUSB.println("~4 seconds..."); 
    for(int i = 0; i<4000; i++) {
        if(digitalRead(38)) {
            Timer4.pause();
        } else {
            Timer4.resume();
        }
        delay(1);
    }
    Timer3.setChannel1Mode(TIMER_DISABLED);
    Timer4.setChannel1Mode(TIMER_DISABLED);
    SerialUSB.print("Count3: "); SerialUSB.println(count3);
    SerialUSB.print("Count4: "); SerialUSB.println(count4);

    // These test the setPeriod auto-configure functionality
    SerialUSB.println("-----------------------------------------------------");
    SerialUSB.println("Testing setPeriod"); 
    Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setCompare1(1);
    Timer4.setPeriod(10); 
    Timer4.pause();
    Timer4.setCount(0);
    Timer4.attachCompare1Interrupt(handler4b);
    SerialUSB.println("Period 10ms, wait 2 seconds..."); 
    count4 = 0;
    Timer4.resume();
    delay(2000);
    Timer4.pause();
    Timer4.setChannel1Mode(TIMER_DISABLED);
    SerialUSB.print("Count4: "); SerialUSB.println(count4);
    SerialUSB.println("(should be around 2sec/10ms = 200000)");
    Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setCompare1(1);
    Timer4.pause();
    Timer4.setPeriod(30000); 
    Timer4.setCount(0);
    Timer4.attachCompare1Interrupt(handler4b);
    SerialUSB.println("Period 30000ms, wait 2 seconds..."); 
    count4 = 0;
    Timer4.resume();
    delay(2000);
    Timer4.pause();
    Timer4.setChannel1Mode(TIMER_DISABLED);
    SerialUSB.print("Count4: "); SerialUSB.println(count4);
    SerialUSB.println("(should be around 2sec/30000ms ~ 67)");

    Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setPeriod(300000); 
    Timer4.setCompare1(1);
    Timer4.pause();
    Timer4.setCount(0);
    Timer4.attachCompare1Interrupt(handler4b);
    SerialUSB.println("Period 300000ms, wait 2 seconds..."); 
    count4 = 0;
    Timer4.resume();
    delay(2000);
    Timer4.pause();
    Timer4.setChannel1Mode(TIMER_DISABLED);
    SerialUSB.print("Count4: "); SerialUSB.println(count4);
    SerialUSB.println("(should be around 2sec/300000ms ~ 6.7)");

    Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setPrescaleFactor(33);
    Timer4.setOverflow(65454);
    Timer4.pause();
    Timer4.setCount(0);
    Timer4.setCompare1(1); 
    Timer4.attachCompare1Interrupt(handler4b);
    SerialUSB.println("Period 30000ms, wait 2 seconds..."); 
    count4 = 0;
    Timer4.resume();
    delay(2000);
    Timer4.pause();
    Timer4.setChannel1Mode(TIMER_DISABLED);
    SerialUSB.print("Count4: "); SerialUSB.println(count4);
    SerialUSB.println("(should be around 2sec/30000ms ~ 67)");

    Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer4.setCompare1(1);
    Timer4.setPeriod(30000); 
    Timer4.pause();
    Timer4.setCount(0);
    Timer4.attachCompare1Interrupt(handler4b);
    SerialUSB.println("Period 30000ms, wait 2 seconds..."); 
    count4 = 0;
    Timer4.resume();
    delay(2000);
    Timer4.pause();
    Timer4.setChannel1Mode(TIMER_DISABLED);
    SerialUSB.print("Count4: "); SerialUSB.println(count4);
    SerialUSB.println("(should be around 2sec/30000ms ~ 67)");

    // This section is to touch every channel of every timer. The output
    // ratios should reflect the ratios of the rate variables. Demonstrates
    // that over time the actual timing rates get blown away by other system
    // interrupts.
    for(t=0; t<4; t++) {
        toggle ^= 1; digitalWrite(LED_PIN, toggle);
        delay(100);
        SerialUSB.println("-----------------------------------------------------");
        SerialUSB.print("Testing Timer "); SerialUSB.println(t+1);
        count1 = count2 = count3 = count4 = 0;
        Timers[t].setOverflow(0xFFFF);
        Timers[t].setPrescaleFactor(1);
        Timers[t].setCompare1(65535);
        Timers[t].setCompare2(65535);
        Timers[t].setCompare3(65535);
        Timers[t].setCompare4(65535);
        Timers[t].setChannel1Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel2Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel3Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].setChannel4Mode(TIMER_OUTPUTCOMPARE);
        Timers[t].attachCompare1Interrupt(handler1);
        Timers[t].attachCompare2Interrupt(handler2);
        Timers[t].attachCompare3Interrupt(handler3);
        Timers[t].attachCompare4Interrupt(handler4);
        Timers[t].resume();
        delay(3000);
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

void handler3b(void) {
    count3++;
} 
void handler4b(void) {
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

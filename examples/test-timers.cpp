// Sample main.cpp file. Blinks an LED, sends a message out USART2
// and turns on PWM on pin 2

#include "wirish.h"
#include "timers.h"

#define LED_PIN 13
#define PWM_PIN  2

void handler1(void);
void handler2(void);
void handler3(void);
void handler4(void);

void setup_test_timer(void);

int toggle = 0;
int timer = 1;
int state = 3;
int last_but = 0;

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
uint16 rate1 = 1000;
uint16 rate2 = 2000;
uint16 rate3 = 3000;
uint16 rate4 = 4000;
uint16 val1 = 10000;
uint16 val2 = 10000;
uint16 val3 = 10000;
uint16 val4 = 10000;

void setup()
{
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);

    pinMode(38, INPUT);

    /* Send a message out USART2  */
    //SerialUSB.begin(9600);
    SerialUSB.println("Begining timer test...");

    /* Send a message out the usb virtual serial port  */
    //SerialUSB.println("Hello!");
    
    timer = 1;
    setup_test_timer();

}


void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(800);

    
    if(digitalRead(38) && !last_but) {
        state++;
        switch(state){
        case 1: 
            SerialUSB.println("Testing Timer1 ---------------------------");
            timer = 1;
            setup_test_timer();
            break;
        case 2:
            SerialUSB.println("Testing Timer2 ---------------------------");
            timer_set_mode(timer,1,TIMER_DISABLED);
            timer_set_mode(timer,2,TIMER_DISABLED);
            timer_set_mode(timer,3,TIMER_DISABLED);
            timer_set_mode(timer,4,TIMER_DISABLED);
            timer_set_count(1,0);
            timer_set_count(2,0);
            timer_set_count(3,0);
            timer_set_count(4,0);
            timer = 2;
            setup_test_timer();
            break;
        case 3:
            SerialUSB.println("Testing Timer3 ---------------------------");
            timer_set_mode(timer,1,TIMER_DISABLED);
            timer_set_mode(timer,2,TIMER_DISABLED);
            timer_set_mode(timer,3,TIMER_DISABLED);
            timer_set_mode(timer,4,TIMER_DISABLED);
            timer = 3;
            setup_test_timer();
            break;
        case 4:
            SerialUSB.println("Testing Timer4 ---------------------------");
            timer_set_mode(timer,1,TIMER_DISABLED);
            timer_set_mode(timer,2,TIMER_DISABLED);
            timer_set_mode(timer,3,TIMER_DISABLED);
            timer_set_mode(timer,4,TIMER_DISABLED);
            timer = 4;
            setup_test_timer();
            break;
        default:
            state = 0;
            timer_set_mode(timer,1,TIMER_DISABLED);
            timer_set_mode(timer,2,TIMER_DISABLED);
            timer_set_mode(timer,3,TIMER_DISABLED);
            timer_set_mode(timer,4,TIMER_DISABLED);
            timer = 0;
            SerialUSB.println("Restarting -------------------------------");
        }
    }
    
    SerialUSB.print("Doing ------------------ "); SerialUSB.println(timer,DEC);
    if(timer!=0) { SerialUSB.print("CNT: "); SerialUSB.println(timer_get_count(timer),DEC); }
    SerialUSB.print("Count1 : "); SerialUSB.println(count1,DEC);
    SerialUSB.print("Count2 : "); SerialUSB.println(count2,DEC);
    SerialUSB.print("Count3 : "); SerialUSB.println(count3,DEC);
    SerialUSB.print("Count4 : "); SerialUSB.println(count4,DEC);
    SerialUSB.println();
    /*
    SerialUSB.print("Status  : "); SerialUSB.println(get_sr(),HEX);
    */
    last_but = digitalRead(38);
}

void setup_test_timer(void) {
    timer_set_prescaler(timer,10000);
    timer_set_mode(timer,1,TIMER_OUTPUTCOMPARE);
    timer_set_mode(timer,2,TIMER_OUTPUTCOMPARE);
    timer_set_mode(timer,3,TIMER_OUTPUTCOMPARE);
    timer_set_mode(timer,4,TIMER_OUTPUTCOMPARE);
    val1 = val2 = val3 = val4 = 10000;
    timer_set_compare_value(timer,1,val1);
    timer_set_compare_value(timer,2,val2);
    timer_set_compare_value(timer,3,val3);
    timer_set_compare_value(timer,4,val4);
    timer_attach_interrupt(timer,1,handler1);
    timer_attach_interrupt(timer,2,handler2);
    timer_attach_interrupt(timer,3,handler3);
    timer_attach_interrupt(timer,4,handler4);
    count1 = count2 = count3 = count4 = 0;
}

void handler1(void) {
    val1 += rate1;
    timer_set_compare_value(timer,1,val1);
    count1++;
    //SerialUSB.print("CC3 Inter: "); SerialUSB.print(get_sr(),HEX);
    //    SerialUSB.print(", "); SerialUSB.println(get_sr_buff(),HEX);
} 
void handler2(void) {
    val2 += rate2;
    timer_set_compare_value(timer,2,val2);
    count2++;
} 
void handler3(void) {
    val3 += rate3;
    timer_set_compare_value(timer,3,val3);
    count3++;
} 
void handler4(void) {
    val4 += rate4;
    timer_set_compare_value(timer,4,val4);
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

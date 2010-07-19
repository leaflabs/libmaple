// Sample main.cpp file. Blinks an LED, sends a message out USART2
// and turns on PWM on pin 2

#include "wirish.h"
#include "usb.h"

#define LED_PIN 13
#define BUT_PIN 38

uint32 state = 0;
#define QUICKPRINT  0
#define BIGSTUFF    1
#define NUMBERS     2
#define SIMPLE      3
#define ONOFF       4


void setup()
{
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);

    /* Set up the Button */
    pinMode(BUT_PIN, INPUT_PULLUP);

    Serial2.begin(9600);
    Serial2.println("Hello world! This is the debug channel.");
}

int toggle = 0;

uint8 c1 = '-';

void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(1000);

    if(digitalRead(BUT_PIN)) {
        while(digitalRead(BUT_PIN)) {};
        state++;
    }
    
    switch(state) {
        case QUICKPRINT:
            for(int i = 0; i<30; i++) {
                usbSendBytes(&c1,1);
                SerialUSB.print('.');
                SerialUSB.print('|');
            }
            Serial2.println(SerialUSB.pending(),DEC);
            SerialUSB.println();
            break;
        case BIGSTUFF:
            SerialUSB.println("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
            SerialUSB.println((uint32)123456789,DEC);
            SerialUSB.println(3.1415926535);
            Serial2.println(SerialUSB.pending(),DEC);
            break;
        case NUMBERS:
            SerialUSB.println("Numbers! -----------------------------");
            Serial2.println("Numbers! -----------------------------");
            SerialUSB.println('1');
            Serial2.println('1');
            SerialUSB.println(1,DEC);
            Serial2.println(1,DEC);
            SerialUSB.println(-1,DEC);
            Serial2.println(-1,DEC);
            SerialUSB.println(3.14159265);
            Serial2.println(3.14159265);
            SerialUSB.println(3.14159265,9);
            Serial2.println(3.14159265,9);
            SerialUSB.println(123456789,DEC);
            Serial2.println(123456789,DEC);
            SerialUSB.println(-123456789,DEC);
            Serial2.println(-123456789,DEC);
            SerialUSB.println(65535,HEX);
            Serial2.println(65535,HEX);
            break;
        case SIMPLE:
            Serial2.println("Trying write('a')");
            SerialUSB.write('a');
            Serial2.println("Trying write(\"b\")");
            SerialUSB.write("b");
            Serial2.println("Trying print('c')");
            SerialUSB.print('c');
            Serial2.println("Trying print(\"d\")");
            SerialUSB.print("d");
            Serial2.println("Trying print(\"efg\")");
            SerialUSB.print("efg");
            Serial2.println("Trying println(\"hij\\n\\r\")");
            SerialUSB.print("hij\n\r");
            SerialUSB.write(' ');
            SerialUSB.println();
            Serial2.println("Trying println(123456789,DEC)");
            SerialUSB.println(123456789);
            Serial2.println("Trying println(3.141592)");
            SerialUSB.println(3.141592);
            Serial2.println("Trying println(\"DONE\")");
            SerialUSB.println("DONE");
            break;
        case ONOFF:
            Serial2.println("Shutting down...");
            SerialUSB.println("Shutting down...");
            SerialUSB.end();
            Serial2.println("Waiting 4seconds...");
            delay(4000);
            Serial2.println("Starting up...");
            SerialUSB.begin();
            SerialUSB.println("Hello World!");
            Serial2.println("Waiting 4seconds...");
            delay(4000);
            state++;
            break;
        default:
            state = 0;
    }
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


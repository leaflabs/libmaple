/* *****************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * ****************************************************************************/

#include "wirish.h"
#include "HardwareSerial.h"
#include "HardwareUsb.h"
#include <math.h>
#include "usb.h"

#define LED_PIN 13
#define PWM_PIN  2

HardwareUsb Usb;

uint8 input = 0;
uint8 tiddle = 0;
int toggle = 0;
int rate = 0;
int sample = 0;

// read these off maple board rev3
const uint8 pwm_pins[] = {0,1,2,3,5,6,7,8,9,11,12,14,24,25,27,28};
// note that 38 is just a button and 39+ aren't functional as of 04/22/2010
const uint8 adc_pins[] = {0,1,2,10,11,12,13,15,16,17,18,19,20,27,28};
#define NUM_GPIO        44      // 43 is the MAX
uint8 gpio_state[NUM_GPIO];

#define DUMMY_DAT "qwertyuiopasdfghjklzxcvbnmmmmmm,./1234567890-=qwertyuiopasdfghjklzxcvbnm,./1234567890"

void print_help(void);
void do_noise(uint8 pin);
void do_everything(void);
void do_fast_gpio(void);

void setup() {
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);

    /* Send a message out over USART2  */
    //Serial2.begin(115200);    // 9600 is more compatible
    Serial2.begin(9600);
    Serial2.println("");
    Serial2.println("    __  __             _      _");
    Serial2.println("   |  \\/  | __ _ _ __ | | ___| |"); 
    Serial2.println("   | |\\/| |/ _` | '_ \\| |/ _ \\ |");
    Serial2.println("   | |  | | (_| | |_) | |  __/_|");
    Serial2.println("   |_|  |_|\\__,_| .__/|_|\\___(_)");
    Serial2.println("               |_|");
    Serial2.println("                              by leaflabs");
    Serial2.println("");
    Serial2.println("");
    Serial2.println("Maple interactive test program (type '?' for help)");
    Serial2.println("------------------------------------------------------------");
    Serial2.print("> ");

    /* Send a message out the USB virtual com port  */
    // TODO: this should all be over usb as well
    //Usb.println("Maple test program starting; use serial port for interactivity");
}

void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(100);

    while(Serial2.available()) {
        input = Serial2.read();
        Serial2.println(input);
        switch(input) {
            case 13:  // Carriage Return
                break;
            case 32:  // ' '
                Serial2.println("spacebar, nice!");
                break;
            case 63:  // '?'
            case 104: // 'h'
                print_help();
                break;
            case 117: // 'u'
                Usb.println("Hello World!");
                break;
            case 119: // 'w'
                Serial1.println("Hello World!");
                Serial2.println("Hello World!");
                Serial3.println("Hello World!");
                break;
            case 109: // 'm'
                Serial2.println("Testing 57600 baud on USART1 and USART3. Press enter.");
                Serial1.begin(57600);
                Serial3.begin(57600);
                while(!Serial2.available()) {
                    Serial1.println(DUMMY_DAT);
                    Serial3.println(DUMMY_DAT);
                    if(Serial1.available()) {
                        Serial1.println(Serial1.read());
                        delay(1000);
                    }
                    if(Serial3.available()) {
                        Serial3.println(Serial3.read());
                        delay(1000);
                    }
                }
                Serial2.read();
                Serial2.println("Testing 115200 baud on USART1 and USART3. Press enter.");
                Serial1.begin(115200);
                Serial3.begin(115200);
                while(!Serial2.available()) {
                    Serial1.println(DUMMY_DAT);
                    Serial3.println(DUMMY_DAT);
                    if(Serial1.available()) {
                        Serial1.println(Serial1.read());
                        delay(1000);
                    }
                    if(Serial3.available()) {
                        Serial3.println(Serial3.read());
                        delay(1000);
                    }
                }
                Serial2.read();
                Serial2.println("Testing 9600 baud on USART1 and USART3. Press enter.");
                Serial1.begin(9600);
                Serial3.begin(9600);
                while(!Serial2.available()) {
                    Serial1.println(DUMMY_DAT);
                    Serial3.println(DUMMY_DAT);
                    if(Serial1.available()) {
                        Serial1.println(Serial1.read());
                        delay(1000);
                    }
                    if(Serial3.available()) {
                        Serial3.println(Serial3.read());
                        delay(1000);
                    }
                }
                Serial2.read();
                Serial2.println("Resetting USART1 and USART3...");
                Serial1.begin(9600);
                Serial3.begin(9600);
                break;
            case 46:  // '.'
                while(!Serial2.available()) {
                    Serial2.print(".");
                    Usb.print(".");
                }
                //Serial2.flush();
                break;
            case 110: // 'n'
                Serial2.println("Taking ADC noise stats...");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(adc_pins); i++) {
                    delay(5);
                    do_noise(adc_pins[i]);
                }
                break;
            case 78: // 'N'
                Serial2.println("Taking ADC noise stats under duress...");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(adc_pins); i++) {
                    // spool up PWM
                    for(uint32 j = 2; j<(uint32)sizeof(pwm_pins); j++) {
                        if(adc_pins[i] != pwm_pins[j]) {
                            pinMode(pwm_pins[j],PWM);
                            pwmWrite(pwm_pins[j], 1000 + i);
                        }
                    }
                    Usb.print(DUMMY_DAT);
                    Usb.print(DUMMY_DAT);
                    do_noise(adc_pins[i]);
                    for(uint32 j = 2; j<(uint32)sizeof(pwm_pins); j++) {
                        if(adc_pins[i] != pwm_pins[j]) {
                            pinMode(pwm_pins[j],OUTPUT);
                            digitalWrite(pwm_pins[j],0);
                        }
                    }
                }
                break;
            case 101: // 'e'
                do_everything();
                break;
            case 87:  // 'W'
                while(!Serial2.available()) {
                    Serial1.print(DUMMY_DAT);
                    Serial2.print(DUMMY_DAT);
                    Serial3.print(DUMMY_DAT);
                }
                break;
            case 85:  // 'U'
                Serial2.println("Dumping data to USB. Press enter.");
                while(!Serial2.available()) {
                    Usb.print(DUMMY_DAT);
                }
                break;
            case 103:  // 'g'
                Serial2.print("Sequentially testing GPIO write on all possible headers except D0 and D1.");
                Serial2.println("Anything for next, ESC to stop.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<NUM_GPIO; i++) {
                    Serial2.print("GPIO write out on header D");
                    Serial2.print(i, DEC);
                    Serial2.println("...");
                    pinMode(i, OUTPUT);
                    digitalWrite(i, tiddle);
                    while(!Serial2.available()) { 
                        tiddle ^= 1;
                        digitalWrite(i, tiddle);
                    }
                    digitalWrite(i, 0);
                    if((uint8)Serial2.read() == (uint8)27) break;      // ESC
                }
                break;
            case 71:  // 'G'
                Serial2.println("Flipping all GPIOs at the same time. Press enter.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<NUM_GPIO; i++) {
                    pinMode(i, OUTPUT);
                }
                while(!Serial2.available()) { 
                    tiddle ^= 1;
                    for(uint32 i = 2; i<NUM_GPIO; i++) {
                        digitalWrite(i, tiddle);
                    }
                }
                for(uint32 i = 2; i<NUM_GPIO; i++) {
                    digitalWrite(i, 0);
                }
                if((uint8)Serial2.read() == (uint8)27) break;      // ESC
                break;
            case 102:  // 'f'
                Serial2.println("Wiggling GPIO header D4 as fast as possible in bursts. Press enter.");
                pinMode(4,OUTPUT);
                while(!Serial2.available()) {
                    do_fast_gpio();
                    delay(1);
                }
                break;
            case 112:  // 'p'
                Serial2.println("Sequentially testing PWM on all possible headers except D0 and D1. ");
                Serial2.println("Anything for next, ESC to stop.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                    Serial2.print("PWM out on header D");
                    Serial2.print(pwm_pins[i], DEC);
                    Serial2.println("...");
                    pinMode(pwm_pins[i], PWM);
                    pwmWrite(pwm_pins[i], 16000);
                    while(!Serial2.available()) { delay(10); }
                    pinMode(pwm_pins[i], OUTPUT);
                    digitalWrite(pwm_pins[i], 0);
                    if((uint8)Serial2.read() == (uint8)27) break;      // ESC
                }
                break;
            case 80:  // 'P'
                Serial2.println("Testing all PWM ports with a sweep. Press enter.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX pins
                for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                    pinMode(pwm_pins[i], PWM);
                    pwmWrite(pwm_pins[i], 4000);
                }
                while(!Serial2.available()) { 
                    rate += 20;
                    if(rate > 65500) rate = 0;
                    for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                        pwmWrite(pwm_pins[i], rate);
                    }
                    delay(1);
                }
                for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                    pinMode(pwm_pins[i], OUTPUT);
                }
                break;
            case 95:  // '_'
                Serial2.println("Delaying for 5 seconds...");
                delay(5000);
                break;
            case 116:  // 't'
                break;
            case 84:  // 'T'
                break;
            case 115:  // 's'
                Serial2.println("Testing all PWM headers with a servo sweep. Press enter.");
                Serial2.println("");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                timer_init(1, 21);
                timer_init(2, 21);
                timer_init(3, 21);
                timer_init(4, 21);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                    pinMode(pwm_pins[i], PWM);
                    pwmWrite(pwm_pins[i], 4000);
                }
                // 1.25ms = 4096counts = 0deg
                // 1.50ms = 4915counts = 90deg
                // 1.75ms = 5734counts = 180deg
                rate = 4096;
                while(!Serial2.available()) { 
                    rate += 20;
                    if(rate > 5734) rate = 4096;
                    for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                        pwmWrite(pwm_pins[i], rate);
                    }
                    delay(20);
                }
                for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                    pinMode(pwm_pins[i], OUTPUT);
                }
                timer_init(1, 1);
                timer_init(2, 1);
                timer_init(3, 1);
                timer_init(4, 1);
                Serial2.begin(9600);
                Serial2.println("(reset serial port)");
                break;
            case 100:  // 'd'
                Serial2.println("Pulling down D4, D22");
                pinMode(22,INPUT_PULLDOWN);
                pinMode(4,INPUT_PULLDOWN);
                while(!Serial2.available()) {
                    delay(1);
                }
                Serial2.read();
                Serial2.println("Pulling up D4, D22");
                pinMode(22,INPUT_PULLUP);
                pinMode(4,INPUT_PULLUP);
                while(!Serial2.available()) {
                    delay(1);
                }
                Serial2.read();
                pinMode(4,OUTPUT); 
                break;
            case 105:  // 'i'
                break;
            case 73:  // 'I'
                break;
            case 114:  // 'r'
                Serial2.println("Monitoring GPIO read state changes. Press enter.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(int i = 2; i<NUM_GPIO; i++) {
                    pinMode(i, INPUT);
                    gpio_state[i] = (uint8)digitalRead(i);
                }
                while(!Serial2.available()) { 
                    for(int i = 2; i<NUM_GPIO; i++) {
                        tiddle = (uint8)digitalRead(i);
                        if(tiddle != gpio_state[i]) {
                            Serial2.print("State change on header D");
                            Serial2.print(i,DEC);
                            if(tiddle) Serial2.println(":\tHIGH");
                            else Serial2.println(":\tLOW");
                            gpio_state[i] = tiddle;
                        }
                    }
                }
                for(int i = 2; i<NUM_GPIO; i++) {
                    pinMode(i, OUTPUT);
                }
                break;
            case 97: // 'a'
                Serial2.print("Sequentially reading each ADC port.");
                Serial2.println("Anything for next, ESC to stop.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(adc_pins); i++) {
                    Serial2.print("Reading on header D");
                    Serial2.print(adc_pins[i], DEC);
                    Serial2.println("...");
                    pinMode(adc_pins[i], INPUT_ANALOG);
                    while(!Serial2.available()) { 
                        sample = analogRead(adc_pins[i]);
                        Serial2.print(adc_pins[i],DEC);
                        Serial2.print("\t");
                        Serial2.print(sample,DEC);
                        Serial2.print("\t");
                        Serial2.print("|");
                        for(int j = 0; j<4096; j+= 100) {
                            if(sample >= j) Serial2.print("#");
                            else Serial2.print(" ");
                        } 
                        Serial2.print("| ");
                        for(int j = 0; j<12; j++) {
                            if(sample & (1 << (11-j))) Serial2.print("1");
                            else Serial2.print("0");
                        }
                        Serial2.println("");
                    }
                    pinMode(adc_pins[i], OUTPUT);
                    digitalWrite(adc_pins[i], 0);
                    if((uint8)Serial2.read() == (uint8)27) break;      // ESC
                }
                break;
            default:
                Serial2.print("Unexpected: ");
                Serial2.println(input);
        }
        Serial2.print("> ");
    }
}

void print_help(void) {
    Serial2.println("");
    //Serial2.println("Command Listing\t(# means any digit)");
    Serial2.println("Command Listing");
    Serial2.println("\t?: print this menu");
    Serial2.println("\th: print this menu");
    Serial2.println("\tw: print Hello World on all 3 USARTS");
    Serial2.println("\tn: measure noise and do statistics");
    Serial2.println("\tN: measure noise and do statistics with background stuff");
    Serial2.println("\ta: show realtime ADC info");
    Serial2.println("\t.: echo '.' until new input");
    Serial2.println("\tu: print Hello World on USB");
    Serial2.println("\t_: try to do as little as possible for a couple seconds (delay)");
    Serial2.println("\tp: test all PWM channels sequentially");
    Serial2.println("\tW: dump data as fast as possible on all 3 USARTS");
    Serial2.println("\tU: dump data as fast as possible on USB");
    Serial2.println("\tg: toggle all GPIOs sequentialy");
    Serial2.println("\tG: toggle all GPIOs at the same time");
    Serial2.println("\tf: toggle GPIO D4 as fast as possible in bursts");
    Serial2.println("\tP: test all PWM channels at the same time with different speeds/sweeps");
    Serial2.println("\tr: read in GPIO status changes and print them in realtime");
    Serial2.println("\ts: output a sweeping SERVO PWM on all PWM channels");
    Serial2.println("\tm: output serial data dumps on USART1 and USART3 with various rates");

    Serial2.println("Unimplemented:");
    Serial2.println("\te: do everything all at once until new input");
    Serial2.println("\tt: output a 1khz squarewave on all GPIOs as well as possible");
    Serial2.println("\tT: output a 1hz squarewave on all GPIOs as well as possible");
    Serial2.println("\ti: print out a bunch of info about system state");
    Serial2.println("\tI: print out status of all headers");
}

void do_noise(uint8 pin) { // TODO    
    uint16 data[100];
    float mean = 0;
    //float stddev = 0;
    float delta = 0;
    float M2 = 0;
    pinMode(pin, INPUT_ANALOG);

    // variance algorithm from knuth; see wikipedia
    // checked against python
    for(int i = 0; i<100; i++) {
        data[i] = analogRead(pin);
        delta = data[i] - mean;
        mean = mean + delta/(i+1);
        M2 = M2 + delta*(data[i] - mean);
    }

    //sqrt is broken?
    //stddev = sqrt(variance);
    Serial2.print("header: D"); Serial2.print(pin,DEC);
    Serial2.print("\tn: "); Serial2.print(100,DEC);
    Serial2.print("\tmean: "); Serial2.print(mean);
    Serial2.print("\tvar: "); Serial2.println(M2/99.0);
    pinMode(pin, OUTPUT);
}

void do_everything(void) { // TODO    
    // TODO
    // print to usart
    // print to usb
    // toggle gpios
    // enable pwm
    Serial2.println("(unimplemented)");
}

void do_fast_gpio(void) {
    // header D4 is on port B and is pin 5 on the uC
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
    gpio_write_bit(GPIOB_BASE, 5, 1); gpio_write_bit(GPIOB_BASE, 5, 0); 
}

int main(void) {
    init();
    setup();

    while (1) {
        loop();
    }
    return 0;
}


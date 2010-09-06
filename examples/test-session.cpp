// Interactive Test Session for LeafLabs Maple
// Copyright (c) 2010 LeafLabs LLC.
//
//  Useful for testing Maple features and troubleshooting. Select a COMM port
//  (SerialUSB or Serial2) before compiling and then enter 'h' at the prompt
//  for a list of commands.

#include "wirish.h"

#define LED_PIN 13
#define PWM_PIN  2

// choose your weapon
#define COMM SerialUSB
//#define COMM Serial2

uint8 input = 0;
uint8 tiddle = 0;
int toggle = 0;
int rate = 0;
int sample = 0;

// read these off maple board rev3
// note that 38 is just a button and 39+ aren't functional as of 04/22/2010
const uint8 pwm_pins[] = {0,1,2,3,5,6,7,8,9,11,12,14,24,25,27,28};
const uint8 adc_pins[] = {0,1,2,10,11,12,13,15,16,17,18,19,20,27,28};
#define NUM_GPIO        44      // 44 is the MAX
uint8 gpio_state[NUM_GPIO];

#define DUMMY_DAT "qwertyuiopasdfghjklzxcvbnmmmmmm,./1234567890-=qwertyuiopasdfghjklzxcvbnm,./1234567890"

void print_help(void);
void do_noise(uint8 pin);
void do_everything(void);
void do_fast_gpio(void);

void setup() {
    /* Set up the LED to blink  */
    pinMode(LED_PIN, OUTPUT);

    /* Start up the serial ports */
    Serial1.begin(9600);
    Serial2.begin(9600);
    Serial3.begin(9600);

    /* Send a message out over COMM interface */
    COMM.println(" ");
    COMM.println("    __   __             _      _");
    COMM.println("   |  \\/  | __ _ _ __ | | ___| |"); 
    COMM.println("   | |\\/| |/ _` | '_ \\| |/ _ \\ |");
    COMM.println("   | |  | | (_| | |_) | |  __/_|");
    COMM.println("   |_|  |_|\\__,_| .__/|_|\\___(_)");
    COMM.println("                 |_|");
    COMM.println("                              by leaflabs");
    COMM.println("");
    COMM.println("");
    COMM.println("Maple interactive test program (type '?' for help)");
    COMM.println("------------------------------------------------------------");
    COMM.print("> ");

}

void loop() {
    toggle ^= 1;
    digitalWrite(LED_PIN, toggle);
    delay(100);

    while(COMM.available()) {
        input = COMM.read();
        COMM.println(input);
        switch(input) {
            case 13:  // Carriage Return
                break;
            case 32:  // ' '
                COMM.println("spacebar, nice!");
                break;
            case 63:  // '?'
            case 104: // 'h'
                print_help();
                break;
            case 117: // 'u'
                SerialUSB.println("Hello World!");
                break;
            case 119: // 'w'
                Serial1.println("Hello World!");
                Serial2.println("Hello World!");
                Serial3.println("Hello World!");
                break;
            case 109: // 'm'
                COMM.println("Testing 57600 baud on USART1 and USART3. Press enter.");
                Serial1.begin(57600);
                Serial3.begin(57600);
                while(!COMM.available()) {
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
                COMM.read();
                COMM.println("Testing 115200 baud on USART1 and USART3. Press enter.");
                Serial1.begin(115200);
                Serial3.begin(115200);
                while(!COMM.available()) {
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
                COMM.read();
                COMM.println("Testing 9600 baud on USART1 and USART3. Press enter.");
                Serial1.begin(9600);
                Serial3.begin(9600);
                while(!COMM.available()) {
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
                COMM.read();
                COMM.println("Resetting USART1 and USART3...");
                Serial1.begin(9600);
                Serial3.begin(9600);
                break;
            case 46:  // '.'
                while(!COMM.available()) {
                    Serial1.print(".");
                    Serial2.print(".");
                    Serial3.print(".");
                    SerialUSB.print(".");
                }
                break;
            case 110: // 'n'
                COMM.println("Taking ADC noise stats...");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(adc_pins); i++) {
                    delay(5);
                    do_noise(adc_pins[i]);
                }
                break;
            case 78: // 'N'
                COMM.println("Taking ADC noise stats under duress...");
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
                    SerialUSB.print(DUMMY_DAT);
                    SerialUSB.print(DUMMY_DAT);
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
                while(!COMM.available()) {
                    Serial1.print(DUMMY_DAT);
                    Serial2.print(DUMMY_DAT);
                    Serial3.print(DUMMY_DAT);
                }
                break;
            case 85:  // 'U'
                COMM.println("Dumping data to USB. Press enter.");
                while(!COMM.available()) {
                    SerialUSB.print(DUMMY_DAT);
                }
                break;
            case 103:  // 'g'
                COMM.print("Sequentially testing GPIO write on all possible headers except D0 and D1.");
                COMM.println("Anything for next, ESC to stop.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<NUM_GPIO; i++) {
                    COMM.print("GPIO write out on header D");
                    COMM.print(i, DEC);
                    COMM.println("...");
                    pinMode(i, OUTPUT);
                    digitalWrite(i, tiddle);
                    while(!COMM.available()) { 
                        tiddle ^= 1;
                        digitalWrite(i, tiddle);
                    }
                    digitalWrite(i, 0);
                    if((uint8)COMM.read() == (uint8)27) break;      // ESC
                }
                break;
            case 71:  // 'G'
                COMM.println("Flipping all GPIOs at the same time. Press enter.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<NUM_GPIO; i++) {
                    pinMode(i, OUTPUT);
                }
                while(!COMM.available()) { 
                    tiddle ^= 1;
                    for(uint32 i = 2; i<NUM_GPIO; i++) {
                        digitalWrite(i, tiddle);
                    }
                }
                for(uint32 i = 2; i<NUM_GPIO; i++) {
                    digitalWrite(i, 0);
                }
                if((uint8)COMM.read() == (uint8)27) break;      // ESC
                break;
            case 102:  // 'f'
                COMM.println("Wiggling GPIO header D4 as fast as possible in bursts. Press enter.");
                pinMode(4,OUTPUT);
                while(!COMM.available()) {
                    do_fast_gpio();
                    delay(1);
                }
                break;
            case 112:  // 'p'
                COMM.println("Sequentially testing PWM on all possible headers except D0 and D1. ");
                COMM.println("Anything for next, ESC to stop.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                    COMM.print("PWM out on header D");
                    COMM.print(pwm_pins[i], DEC);
                    COMM.println("...");
                    pinMode(pwm_pins[i], PWM);
                    pwmWrite(pwm_pins[i], 16000);
                    while(!COMM.available()) { delay(10); }
                    pinMode(pwm_pins[i], OUTPUT);
                    digitalWrite(pwm_pins[i], 0);
                    if((uint8)COMM.read() == (uint8)27) break;      // ESC
                }
                break;
            case 80:  // 'P'
                COMM.println("Testing all PWM ports with a sweep. Press enter.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX pins
                for(uint32 i = 2; i<sizeof(pwm_pins); i++) {
                    pinMode(pwm_pins[i], PWM);
                    pwmWrite(pwm_pins[i], 4000);
                }
                while(!COMM.available()) { 
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
                COMM.println("Delaying for 5 seconds...");
                delay(5000);
                break;
            case 116:  // 't'
                break;
            case 84:  // 'T'
                break;
            case 115:  // 's'
                COMM.println("Testing all PWM headers with a servo sweep. Press enter.");
                COMM.println("");
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
                while(!COMM.available()) { 
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
                COMM.println("(reset serial port)");
                break;
            case 100:  // 'd'
                COMM.println("Pulling down D4, D22");
                pinMode(22,INPUT_PULLDOWN);
                pinMode(4,INPUT_PULLDOWN);
                while(!COMM.available()) {
                    delay(1);
                }
                COMM.read();
                COMM.println("Pulling up D4, D22");
                pinMode(22,INPUT_PULLUP);
                pinMode(4,INPUT_PULLUP);
                while(!COMM.available()) {
                    delay(1);
                }
                COMM.read();
                pinMode(4,OUTPUT); 
                break;
            case 105:  // 'i'
                break;
            case 73:  // 'I'
                break;
            case 114:  // 'r'
                COMM.println("Monitoring GPIO read state changes. Press enter.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(int i = 2; i<NUM_GPIO; i++) {
                    pinMode(i, INPUT_PULLDOWN);
                    gpio_state[i] = (uint8)digitalRead(i);
                }
                while(!COMM.available()) { 
                    for(int i = 2; i<NUM_GPIO; i++) {
                        tiddle = (uint8)digitalRead(i);
                        if(tiddle != gpio_state[i]) {
                            COMM.print("State change on header D");
                            COMM.print(i,DEC);
                            if(tiddle) COMM.println(":\tHIGH");
                            else COMM.println(":\tLOW");
                            gpio_state[i] = tiddle;
                        }
                    }
                }
                for(int i = 2; i<NUM_GPIO; i++) {
                    pinMode(i, OUTPUT);
                }
                break;
            case 97: // 'a'
                COMM.print("Sequentially reading each ADC port.");
                COMM.println("Anything for next, ESC to stop.");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                // make sure to skip the TX/RX headers
                for(uint32 i = 2; i<sizeof(adc_pins); i++) {
                    COMM.print("Reading on header D");
                    COMM.print(adc_pins[i], DEC);
                    COMM.println("...");
                    pinMode(adc_pins[i], INPUT_ANALOG);
                    while(!COMM.available()) { 
                        sample = analogRead(adc_pins[i]);
                        COMM.print(adc_pins[i],DEC);
                        COMM.print("\t");
                        COMM.print(sample,DEC);
                        COMM.print("\t");
                        COMM.print("|");
                        for(int j = 0; j<4096; j+= 100) {
                            if(sample >= j) COMM.print("#");
                            else COMM.print(" ");
                        } 
                        COMM.print("| ");
                        for(int j = 0; j<12; j++) {
                            if(sample & (1 << (11-j))) COMM.print("1");
                            else COMM.print("0");
                        }
                        COMM.println("");
                    }
                    pinMode(adc_pins[i], OUTPUT);
                    digitalWrite(adc_pins[i], 0);
                    if((uint8)COMM.read() == (uint8)27) break;      // ESC
                }
                break;
            case 43:  // '+'
                COMM.println("Doing QA testing for 37 GPIO pins...");
                // turn off LED
                digitalWrite(LED_PIN, 0);
                for(int i = 0; i<NUM_GPIO; i++) {
                    pinMode(i, INPUT);
                    gpio_state[i] = 0; //(uint8)digitalRead(i);
                }
                COMM.println("Waiting to start...");
                while(digitalRead(0) != 1 && !COMM.available()) {
                    continue;
                }
                for(int i=0; i<38; i++) {
                    if(i==13) {
                        COMM.println("Not Checking D13 (LED)");
                        continue;
                    }
                    COMM.print("Checking D");
                    COMM.print(i,DEC);
                    while(digitalRead(i) == 0) continue;
                    for(int j=0; j<NUM_GPIO; j++) {
                        if(digitalRead(j) && j!=i) {
                            COMM.print(": FAIL ########################### D");
                            COMM.println(j, DEC);
                            break;
                        }
                    }
                    while(digitalRead(i) == 1) continue;
                    for(int j=0; j<NUM_GPIO; j++) {
                        if(digitalRead(j) && j!=i) {
                            COMM.print(": FAIL ########################### D");
                            COMM.println(j, DEC);
                            break;
                        }
                    }
                    COMM.println(": Ok!");
                }
                for(int i = 0; i<NUM_GPIO; i++) {
                    pinMode(i, OUTPUT);
                    digitalWrite(i, 0);
                }
                break;
            default:
                COMM.print("Unexpected: ");
                COMM.println(input);
        }
        COMM.print("> ");
    }
}

void print_help(void) {
    COMM.println("");
    //COMM.println("Command Listing\t(# means any digit)");
    COMM.println("Command Listing");
    COMM.println("\t?: print this menu");
    COMM.println("\th: print this menu");
    COMM.println("\tw: print Hello World on all 3 USARTS");
    COMM.println("\tn: measure noise and do statistics");
    COMM.println("\tN: measure noise and do statistics with background stuff");
    COMM.println("\ta: show realtime ADC info");
    COMM.println("\t.: echo '.' until new input");
    COMM.println("\tu: print Hello World on USB");
    COMM.println("\t_: try to do as little as possible for a couple seconds (delay)");
    COMM.println("\tp: test all PWM channels sequentially");
    COMM.println("\tW: dump data as fast as possible on all 3 USARTS");
    COMM.println("\tU: dump data as fast as possible on USB");
    COMM.println("\tg: toggle all GPIOs sequentialy");
    COMM.println("\tG: toggle all GPIOs at the same time");
    COMM.println("\tf: toggle GPIO D4 as fast as possible in bursts");
    COMM.println("\tP: test all PWM channels at the same time with different speeds/sweeps");
    COMM.println("\tr: read in GPIO status changes and print them in realtime");
    COMM.println("\ts: output a sweeping SERVO PWM on all PWM channels");
    COMM.println("\tm: output serial data dumps on USART1 and USART3 with various rates");
    COMM.println("\t+: test shield mode (for QA, will disrupt Serial2!)");

    COMM.println("Unimplemented:");
    COMM.println("\te: do everything all at once until new input");
    COMM.println("\tt: output a 1khz squarewave on all GPIOs as well as possible");
    COMM.println("\tT: output a 1hz squarewave on all GPIOs as well as possible");
    COMM.println("\ti: print out a bunch of info about system state");
    COMM.println("\tI: print out status of all headers");
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
    COMM.print("header: D"); COMM.print(pin,DEC);
    COMM.print("\tn: "); COMM.print(100,DEC);
    COMM.print("\tmean: "); COMM.print(mean);
    COMM.print("\tvar: "); COMM.println(M2/99.0);
    pinMode(pin, OUTPUT);
}

void do_everything(void) { // TODO    
    // TODO
    // print to usart
    // print to usb
    // toggle gpios
    // enable pwm
    COMM.println("(unimplemented)");
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

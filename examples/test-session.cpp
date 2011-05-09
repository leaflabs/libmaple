// Interactive Test Session for LeafLabs Maple
// Copyright (c) 2010 LeafLabs LLC.
//
//  Useful for testing Maple features and troubleshooting. Select a COMM port
//  (SerialUSB or Serial2) before compiling and then enter 'h' at the prompt
//  for a list of commands.

#include "wirish.h"

#define LED_PIN BOARD_LED_PIN
#define PWM_PIN 3

// choose your weapon
#define COMM SerialUSB
//#define COMM Serial2
//#define COMM Serial3


#define ESC       ((uint8)27)

int rate = 0;

#if defined(BOARD_maple)
const uint8 pwm_pins[] =
    {0, 1, 2, 3, 5, 6, 7, 8, 9, 11, 12, 14, 24, 25, 27, 28};
const uint8 adc_pins[] =
    {0, 1, 2, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 27, 28};

#elif defined(BOARD_maple_mini)
const uint8 pwm_pins[] = {3, 4, 5, 8, 9, 10, 11, 15, 16, 25, 26, 27};
const uint8 adc_pins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 33}; // NB: 33 is LED

#elif defined(BOARD_maple_native)
const uint8 pwm_pins[] = {12, 13, 14, 15, 22, 23, 24, 25, 37, 38, 45,
                          46, 47, 48, 49, 50, 53, 54};
const uint8 adc_pins[] = {6, 7, 8, 9, 10, 11,
                          /* the following are on ADC3, which lacks support:
                             39, 40, 41, 42, 43, 45, */
                          46, 47, 48, 49, 50, 51, 52, 53, 54};

#else
#error "Board type has not been selected correctly"

#endif

uint8 gpio_state[NR_GPIO_PINS];

const char* const dummy_dat = ("qwertyuiopasdfghjklzxcvbnmmmmmm,./1234567890-="
                               "qwertyuiopasdfghjklzxcvbnm,./1234567890");

void cmd_print_help(void);
void cmd_adc_stats(void);
void cmd_stressful_adc_stats(void);
void cmd_everything(void);
void cmd_serial1_serial3(void);
void cmd_gpio_monitoring(void);
void cmd_sequential_adc_reads(void);
void cmd_gpio_qa(void);
void cmd_sequential_gpio_writes(void);
void cmd_gpio_toggling(void);
void cmd_sequential_pwm_test(void);
void cmd_pwm_sweep(void);
void cmd_servo_sweep(void);

void measure_adc_noise(uint8 pin);
void fast_gpio(int pin);
void do_serials(HardwareSerial **serials, int n, unsigned baud);
void init_all_timers(uint16 prescale);

void setup() {
    // Set up the LED to blink
    pinMode(BOARD_LED_PIN, OUTPUT);

    // Start up the serial ports
    Serial1.begin(9600);
    Serial2.begin(9600);
    Serial3.begin(9600);

    // Send a message out over COMM interface
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
    COMM.println("----------------------------------------------------------");
    COMM.print("> ");

}

void loop () {
    toggleLED();
    delay(100);

    while(COMM.available()) {
        uint8 input = COMM.read();
        COMM.println(input);

        switch(input) {
        case '\r':
            break;

        case ' ':
            COMM.println("spacebar, nice!");
            break;

        case '?':
        case 'h':
            cmd_print_help();
            break;

        case 'u':
            SerialUSB.println("Hello World!");
            break;

        case 'w':
            Serial1.println("Hello World!");
            Serial2.println("Hello World!");
            Serial3.println("Hello World!");
            break;

        case 'm':
            cmd_serial1_serial3();
            break;

        case '.':
            while(!COMM.available()) {
                Serial1.print(".");
                Serial2.print(".");
                Serial3.print(".");
                SerialUSB.print(".");
            }
            break;

        case 'n':
            cmd_adc_stats();
            break;

        case 'N':
            cmd_stressful_adc_stats();
            break;

        case 'e':
            cmd_everything();
            break;

        case 'W':
            while(!COMM.available()) {
                Serial1.print(dummy_dat);
                Serial2.print(dummy_dat);
                Serial3.print(dummy_dat);
            }
            break;

        case 'U':
            COMM.println("Dumping data to USB. Press any key.");
            while(!COMM.available()) {
                SerialUSB.print(dummy_dat);
            }
            break;

        case 'g':
            cmd_sequential_gpio_writes();
            break;

        case 'G':
            cmd_gpio_toggling();
            break;

        case 'f':
            COMM.println("Wiggling D4 as fast as possible in bursts. "
                         "Press any key.");
            pinMode(4,OUTPUT);
            while(!COMM.available()) {
                fast_gpio(4);
                delay(1);
            }
            break;

        case 'p':
            cmd_sequential_pwm_test();
            break;

        case 'P':
            cmd_pwm_sweep();
            break;

        case '_':
            COMM.println("Delaying for 5 seconds...");
            delay(5000);
            break;

        case 't':               // TODO
            break;

        case 'T':               // TODO
            break;

        case 's':
            cmd_servo_sweep();
            break;

        case 'd':
            COMM.println("Pulling down D4, D22. Press any key.");
            pinMode(22,INPUT_PULLDOWN);
            pinMode(4,INPUT_PULLDOWN);
            while(!COMM.available()) {
                continue;
            }
            COMM.println("Pulling up D4, D22. Press any key.");
            pinMode(22,INPUT_PULLUP);
            pinMode(4,INPUT_PULLUP);
            while(!COMM.available()) {
                continue;
            }
            COMM.read();
            pinMode(4,OUTPUT);
            break;

        case 'i':               // TODO
            break;

        case 'I':               // TODO
            break;

        case 'r':
            cmd_gpio_monitoring();
            break;

        case 'a':
            cmd_sequential_adc_reads();
            break;

        case '+':
            cmd_gpio_qa();
            break;

        default: // -------------------------------
            COMM.print("Unexpected: ");
            COMM.print(input);
            COMM.println(", press h for help.");
        }

        COMM.print("> ");
    }
}

void cmd_print_help(void) {
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
    COMM.println("\t_: do as little as possible for a couple seconds (delay)");
    COMM.println("\tp: test all PWM channels sequentially");
    COMM.println("\tW: dump data as fast as possible on all 3 USARTS");
    COMM.println("\tU: dump data as fast as possible on USB");
    COMM.println("\tg: toggle all GPIOs sequentialy");
    COMM.println("\tG: toggle all GPIOs at the same time");
    COMM.println("\tf: toggle GPIO D4 as fast as possible in bursts");
    COMM.println("\tP: simultaneously test all PWM channels with different "
                 "speeds/sweeps");
    COMM.println("\tr: Monitor and print GPIO status changes");
    COMM.println("\ts: output a sweeping servo PWM on all PWM channels");
    COMM.println("\tm: output data on USART1 and USART3 with various rates");
    COMM.println("\t+: test shield mode (for QA, will disrupt Serial2!)");

    COMM.println("Unimplemented:");
    COMM.println("\te: do everything all at once until new input");
    COMM.println("\tt: output a 1khz squarewave on all GPIOs");
    COMM.println("\tT: output a 1hz squarewave on all GPIOs");
    COMM.println("\ti: print out a bunch of info about system state");
    COMM.println("\tI: print out status of all headers");
}

void measure_adc_noise(uint8 pin) { // TODO
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
    COMM.print("\tvariance: "); COMM.println(M2/99.0);
    pinMode(pin, OUTPUT);
}

void cmd_adc_stats(void) {
    COMM.println("Taking ADC noise stats...");
    digitalWrite(BOARD_LED_PIN, 0);
    for(uint32 i = 0; i<sizeof(adc_pins); i++) {
        delay(5);
        measure_adc_noise(adc_pins[i]);
    }
}

void cmd_stressful_adc_stats(void) {
    COMM.println("Taking ADC noise stats under duress...");
    digitalWrite(BOARD_LED_PIN, 0);
    for(uint32 i = 0; i<sizeof(adc_pins); i++) {
        // spool up PWM
        for(uint32 j = 2; j<(uint32)sizeof(pwm_pins); j++) {
            if(adc_pins[i] != pwm_pins[j]) {
                pinMode(pwm_pins[j],PWM);
                pwmWrite(pwm_pins[j], 1000 + i);
            }
        }
        SerialUSB.print(dummy_dat);
        SerialUSB.print(dummy_dat);
        measure_adc_noise(adc_pins[i]);
        for(uint32 j = 2; j<(uint32)sizeof(pwm_pins); j++) {
            if(adc_pins[i] != pwm_pins[j]) {
                pinMode(pwm_pins[j],OUTPUT);
                digitalWrite(pwm_pins[j],0);
            }
        }
    }
}

void cmd_everything(void) { // TODO
    // print to usart
    // print to usb
    // toggle gpios
    // enable pwm
    COMM.println("(unimplemented)");
}

void fast_gpio(int maple_pin) {
    GPIO_Port *port = PIN_MAP[maple_pin].port;
    uint32 pin = PIN_MAP[maple_pin].pin;

    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
    gpio_write_bit(port, pin, 1); gpio_write_bit(port, pin, 0);
}

void cmd_serial1_serial3(void) {
    HardwareSerial *serial_1_and_3[] = {&Serial1, &Serial3};

    COMM.println("Testing 57600 baud on USART1 and USART3. Press any key.");
    do_serials(serial_1_and_3, 2, 57600);
    COMM.read();

    COMM.println("Testing 115200 baud on USART1 and USART3. Press any key.");
    do_serials(serial_1_and_3, 2, 115200);
    COMM.read();

    COMM.println("Testing 9600 baud on USART1 and USART3. Press any key.");
    do_serials(serial_1_and_3, 2, 9600);
    COMM.read();

    COMM.println("Resetting USART1 and USART3...");
    Serial1.begin(9600);
    Serial3.begin(9600);
}

void do_serials(HardwareSerial **serials, int n, unsigned baud) {
    for (int i = 0; i < n; i++) {
        serials[i]->begin(9600);
    }
    while (!COMM.available()) {
        for (int i = 0; i < n; i++) {
            serials[i]->println(dummy_dat);
            if (serials[i]->available()) {
                serials[i]->println(serials[i]->read());
                delay(1000);
            }
        }
    }
}

void cmd_gpio_monitoring(void) {
    COMM.println("Monitoring GPIO read state changes. Press any key.");
    digitalWrite(BOARD_LED_PIN, 0);
    // make sure to skip the TX/RX headers
    for(int i = 2; i<NR_GPIO_PINS; i++) {
        pinMode(i, INPUT_PULLDOWN);
        gpio_state[i] = (uint8)digitalRead(i);
    }
    while(!COMM.available()) {
        for(int i = 2; i<NR_GPIO_PINS; i++) {
            uint8 current_state = (uint8)digitalRead(i);
            if(current_state != gpio_state[i]) {
                COMM.print("State change on header D");
                COMM.print(i,DEC);
                if(current_state) COMM.println(":\tHIGH");
                else COMM.println(":\tLOW");
                gpio_state[i] = current_state;
            }
        }
    }
    for(int i = 2; i<NR_GPIO_PINS; i++) {
        pinMode(i, OUTPUT);
    }
}

void cmd_sequential_adc_reads(void) {
    COMM.print("Sequentially reading each ADC port.");
    COMM.println("Press any key for next port, or ESC to stop.");
    digitalWrite(LED_PIN, 0);
    // make sure to skip the TX/RX headers
    for(uint32 i = 2; i<sizeof(adc_pins); i++) {
        COMM.print("Reading on header D");
        COMM.print(adc_pins[i], DEC);
        COMM.println("...");
        pinMode(adc_pins[i], INPUT_ANALOG);
        while(!COMM.available()) {
            int sample = analogRead(adc_pins[i]);
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
        if((uint8)COMM.read() == ESC) break;
    }
}

void cmd_gpio_qa(void) {
    COMM.println("Doing QA testing for most GPIO pins...");
    digitalWrite(BOARD_LED_PIN, 0);
    for(int i = 0; i<NR_GPIO_PINS; i++) {
        pinMode(i, INPUT);
        gpio_state[i] = 0;
    }
    COMM.println("Waiting to start...");
    while(digitalRead(0) != 1 && !COMM.available()) {
        continue;
    }
    for(int i=0; i<38; i++) {
        if(i == BOARD_LED_PIN) {
            COMM.println("Not checking LED");
            continue;
        }
        COMM.print("Checking D");
        COMM.print(i,DEC);
        while(digitalRead(i) == 0) continue;
        for(int j=0; j<NR_GPIO_PINS; j++) {
            if(digitalRead(j) && j!=i) {
                COMM.print(": FAIL ########################### D");
                COMM.println(j, DEC);
                break;
            }
        }
        while(digitalRead(i) == 1) continue;
        for(int j=0; j<NR_GPIO_PINS; j++) {
            if(digitalRead(j) && j!=i) {
                COMM.print(": FAIL ########################### D");
                COMM.println(j, DEC);
                break;
            }
        }
        COMM.println(": Ok!");
    }
    for(int i = 0; i<NR_GPIO_PINS; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, 0);
    }
}

void cmd_sequential_gpio_writes(void) {
    COMM.print("Sequentially toggling all pins except D0, D1. ");
    COMM.println("Anything for next, ESC to stop.");
    digitalWrite(BOARD_LED_PIN, 0);
    // make sure to skip the TX/RX headers
    for(uint32 i = 2; i<NR_GPIO_PINS; i++) {
        COMM.print("GPIO write out on header D");
        COMM.print(i, DEC);
        COMM.println("...");
        pinMode(i, OUTPUT);
        do {
            togglePin(i);
        } while(!COMM.available());
        digitalWrite(i, 0);
        if((uint8)COMM.read() == ESC) break;
    }
}

void cmd_gpio_toggling(void) {
    COMM.println("Toggling all GPIOs simultaneously. Press any key.");
    digitalWrite(BOARD_LED_PIN, 0);
    // make sure to skip the TX/RX headers
    for(uint32 i = 2; i<NR_GPIO_PINS; i++) {
        pinMode(i, OUTPUT);
    }
    while(!COMM.available()) {
        for(uint32 i = 2; i<NR_GPIO_PINS; i++) {
            togglePin(i);
        }
    }
    for(uint32 i = 2; i<NR_GPIO_PINS; i++) {
        digitalWrite(i, 0);
    }
}

void cmd_sequential_pwm_test(void) {
    COMM.println("Sequentially testing PWM on all possible headers "
                 "except D0 and D1.");
    COMM.println("Press any key for next, ESC to stop.");
    digitalWrite(BOARD_LED_PIN, 0);
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
        if((uint8)COMM.read() == ESC) break;
    }
}

void cmd_pwm_sweep(void) {
    COMM.println("Testing all PWM ports with a sweep. Press any key.");
    digitalWrite(BOARD_LED_PIN, 0);
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
}

void cmd_servo_sweep(void) {
    COMM.println("Testing all PWM headers with a servo sweep. Press any key.");
    COMM.println();
    digitalWrite(BOARD_LED_PIN, 0);
    init_all_timers(21);
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
    init_all_timers(1);
    Serial2.begin(9600);
    COMM.println("(reset serial port)");
}

void init_all_timers(uint16 prescale) {
    timer_init(TIMER1, prescale);
    timer_init(TIMER2, prescale);
    timer_init(TIMER3, prescale);
#if NR_TIMERS >= 4
    timer_init(TIMER4, prescale);
#elif NR_TIMERS >= 8 // TODO test this on maple native
    timer_init(TIMER5, prescale);
    timer_init(TIMER6, prescale);
    timer_init(TIMER7, prescale);
    timer_init(TIMER8, prescale);
#endif
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

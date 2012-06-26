//
// This is a mostly Wirish-free timer test. Wirish usage is minimized
// because this is a test of the C timer interface in
// <libmaple/timer.h>, so it's good if it can be made to work even
// when most or all of Wirish is missing. Because of that, you may
// need to customize the following output configuration:
//
// Output is printed:
// - on COMM_USART,
// - via TX pin on port COMM_USART_PORT, bit COMM_USART_TX_BIT
// - via RX pin on port COMM_USART_PORT, bit COMM_USART_RX_BIT
// - at COMM_USART_BAUD baud.
#define COMM_USART USART6
#define COMM_USART_BAUD 115200
#define COMM_USART_PORT GPIOG
#define COMM_USART_TX_BIT 14
#define COMM_USART_RX_BIT 9
// Other optional configuration below.

#include <libmaple/libmaple.h>
#include <libmaple/gpio.h>
#include <libmaple/usart.h>
#include <libmaple/systick.h>
#include <libmaple/timer.h>
#include <wirish/boards.h>

//
// Configuration
//

// More output if true
static bool verbose = true;

// Timers to test
// FIXME use feature test macros for smaller MCUs
static timer_dev *timers[] = {
    // Available on all currently supported MCUs
    TIMER1, TIMER2, TIMER3, TIMER4,
    // Available on F1 (HD and up), F2
    TIMER5, TIMER6, TIMER7, TIMER8,
    // Available on F1 (XL), F2
    TIMER9, TIMER10, TIMER11, TIMER12, TIMER13, TIMER14,
};

//
// Test routines
//

typedef void (*timer_test_t)(timer_dev *);

static void runTest(const char description[], timer_test_t test);
static void runTests(void);

static void testGetAndSetCount(timer_dev*);
static void testPauseAndResume(timer_dev*);
static void testTimerChannels(timer_dev*);

//
// Helpers
//

static void initTimer(timer_dev *dev);
static int timerNumber(timer_dev *dev);
// Hack: a systick-based delay, useful until delay_us() is fixed
static void _delay(uint32 msec);
// Wirish-less USART initialization routine
static void init_usart(usart_dev *dev, gpio_dev *gdev, uint8 tx, uint8 rx);
// Return whether or not the timer has capture/compare channel `ch'.
// TODO: does something like this belong in the standard timer library?
static bool timer_has_cc_ch(timer_dev *dev, int ch);

// Printing routines and variants for verbose mode
static void putstr(const char str[]);
static void println(void);
static void putstrln(const char str[]);
static void putudec(uint32 val);
static void puttimn(timer_dev *dev);
static void v_putstr(const char str[]);
static void v_println();
static void v_putstrln(const char str[]);
static void v_putudec(uint32 val);
static void v_puttimn(timer_dev *dev);
// Used to visually separate output from different tests
static void printBanner(void);

//
// Handler state
//

static int count1 = 0;
static int count2 = 0;
static int count3 = 0;
static int count4 = 0;
static int timer_num; // Current timer we're considering

//
// Timer capture/compare interrupt handlers
//
// These are shared between timers. The global variable timer_num
// controls which timer they affect.
//

static void handler1(void);
static void handler2(void);
static void handler3(void);
static void handler4(void);
static voidFuncPtr handlers[] = {handler1, handler2, handler3, handler4};

//
// setup() and loop()
//

void setup() {
    init_usart(COMM_USART, COMM_USART_PORT,
               COMM_USART_TX_BIT, COMM_USART_RX_BIT);
    _delay(5);
    println();
    printBanner();
    putstr("Initializing timers...\r\n");
    timer_foreach(initTimer);
    putstr("Done. Running tests.\r\n");
    runTests();
    printBanner();
    putstr("Done testing timers.\r\n");
}

void loop() {
}

//
// Test routine implementations
//

static void runTests(void) {
    runTest("timer_get_count()/timer_set_count()", testGetAndSetCount);
    runTest("timer_pause()/timer_resume()", testPauseAndResume);
    runTest("capture/compare channels and interrupts",
            testTimerChannels);
}

static void runTest(const char description[], timer_test_t test) {
    printBanner();
    putstr("Testing ");
    putstr(description);
    putstrln(".");
    timer_foreach(test);
}

static void testGetAndSetCount(timer_dev *dev) {
    unsigned before, after;
    unsigned val_to_set = 1234;

    timer_pause(dev);
    before = timer_get_count(dev);
    timer_set_count(dev, val_to_set);
    after = timer_get_count(dev);
    timer_resume(dev);

    if (after != val_to_set) {
        puttimn(dev);
        putstr(": ");
        putstr("*** FAIL: get/set count for ");
        puttimn(dev);
        putstr(".");
        putstr("Start count = ");
        putudec(before);
        putstr(". Count set to ");
        putudec(val_to_set);
        putstr(", and now count is = ");
        putudec(after);
        println();
    } else if (verbose) {
        puttimn(dev);
        putstr(": ");
        putstrln("[ok]");
    }
}

// This hack works on all currently supported STM32 series, but you
// may need to do something smarter in the future. The assertions
// ensure that our assumptions hold for your target.
static timer_dev *getDifferentTimerOnSameBusAs(timer_dev *dev) {
    rcc_clk_domain dev_domain = rcc_dev_clk(dev->clk_id);
    ASSERT(RCC_APB1 == dev_domain || RCC_APB2 == dev_domain);
    ASSERT(rcc_dev_clk(TIMER1->clk_id) == RCC_APB2);
    ASSERT(rcc_dev_clk(TIMER2->clk_id) == RCC_APB1);
    ASSERT(rcc_dev_clk(TIMER8->clk_id) == RCC_APB2);
    ASSERT(rcc_dev_clk(TIMER3->clk_id) == RCC_APB1);

    if (dev->clk_id == RCC_TIMER1) {
        return TIMER8;
    }
    if (dev->clk_id == RCC_TIMER2) {
        return TIMER3;
    }
    return dev_domain == RCC_APB2 ? TIMER1 : TIMER2;
}

// Rough test of pause and resume.
//
// Approximately half the time, dev is in the "pause" state and the
// timer doesn't increment, while another timer (`base_dev') on the
// same bus continues. dev and base_dev have identical start counts
// and prescalers.
//
// Since dev and base_dev share a bus (and thus a base clock), and we
// configure them to have the same prescaler and start count, the
// ratio of their end counts should be approximately 1 : 2. We check
// to make sure this is true, up to tolerance `epsilon'.
static void testPauseAndResume(timer_dev *dev) {
    timer_dev *base_dev = getDifferentTimerOnSameBusAs(dev);
    unsigned start_count = 0, reload = 65535;
    // This prescaler should be enough to ensure that we don't
    // overflow, while still giving us a reasonably large number of
    // timer ticks.
    uint16 prescaler = CYCLES_PER_MICROSECOND * 50;
    double epsilon = .02;

    if (rcc_dev_clk(base_dev->clk_id) != rcc_dev_clk(dev->clk_id)) {
        putstrln("*** ERROR: cannot run test. Bus info is messed up.");
        return;
    }

    // Pause and set up timers
    timer_pause(base_dev);
    timer_pause(dev);
    timer_set_count(base_dev, start_count);
    timer_set_count(dev, start_count);
    timer_set_reload(base_dev, reload);
    timer_set_reload(dev, reload);
    timer_set_prescaler(base_dev, prescaler);
    timer_set_prescaler(dev, prescaler);
    timer_generate_update(base_dev);
    timer_generate_update(dev);

    // Resume the timers and run the test
    ASSERT(timer_get_count(base_dev) == start_count);
    ASSERT(timer_get_count(dev) == start_count);
    timer_resume(base_dev);
    timer_resume(dev);
    _delay(1000);
    timer_pause(dev);
    _delay(1000);
    timer_pause(base_dev);

    // Check the results
    unsigned dev_count = timer_get_count(dev);
    unsigned base_count = timer_get_count(base_dev);
    double count_ratio = ((double)dev_count / base_count);
    bool fail = false;
    if (count_ratio > 0.5 + epsilon || count_ratio < 0.5 - epsilon) {
        fail = true;
    }
    if (fail || verbose) {
        puttimn(dev);
        putstr(" vs. ");
        puttimn(base_dev);
        putstr(": ");
        if (fail) putstr("*** FAIL: ");
        else putstr("[ok] ");
        putstr("(dev = ");
        putudec(dev_count);
        putstr(") / (base = ");
        putudec(base_count);
        putstr(") = ");
        // hack hack hack
        putudec((int)count_ratio);
        count_ratio -= (int)count_ratio;
        putstr(".");
        int cr_x_100 = (int)(count_ratio * 100);
        int hundredths = cr_x_100 % 10;
        cr_x_100 /= 10;
        int tenths = cr_x_100 % 10;
        putudec(tenths);
        putudec(hundredths);
        println();
    }
}

// This function touches every capture/compare channel of a given
// timer.  The channel counts should be equal within a timer
// regardless of other interrupts on the system (note that this
// doesn't really test timers with only a single capture/compare
// channel; for that, you'll want to do visual inspection of timers
// that share a bus, in verbose mode).
static void testTimerChannels(timer_dev *dev) {
    switch (dev->type) {
    case TIMER_BASIC:
        v_putstr("Skipping basic timer ");
        v_puttimn(dev);
        v_println();
        return;
    case TIMER_ADVANCED:
    case TIMER_GENERAL:
        // Set up
        v_puttimn(dev);
        v_println();
        v_putstr("\tchannels: ");

        timer_num = timerNumber(dev);
        timer_pause(dev);
        count1 = 0;
        count2 = 0;
        count3 = 0;
        count4 = 0;
        timer_set_reload(dev, 0xFFFF);
        timer_set_prescaler(dev, 1);
        for (int c = 1; c <= 4; c++) {
            if (timer_has_cc_ch(dev, c)) {
                v_putudec(c);
                v_putstr("\t");
                timer_set_compare(dev, c, 0xFFFF);
                timer_set_mode(dev, c, TIMER_OUTPUT_COMPARE);
                timer_attach_interrupt(dev, c, handlers[c - 1]);
            }
        }
        v_println();

        // Run test
        timer_generate_update(dev);
        timer_resume(dev);
        _delay(250);
        timer_pause(dev);

        // Print results
        v_putstr("\tcounts:   ");
        bool fail = false;
        bool mismatched[4] = {false, false, false, false};
        int counts[4];
        counts[0] = count1;
        counts[1] = count2;
        counts[2] = count3;
        counts[3] = count4;
        bool first = true;
        int first_count = -1;
        for (int c = 1; c <= 4; c++) {
            if (timer_has_cc_ch(dev, c)) {
                if (first) {
                    first_count = counts[c - 1];
                    first = false;
                }
                if (!first && (counts[c - 1] != first_count)) {
                    mismatched[c - 1] = true;
                    fail = true;
                }
                v_putudec(counts[c - 1]);
                v_putstr("\t");
            }
        }
        v_println();
        if (fail) {
            for (int i = 0; i < 4; i++) {
                if (mismatched[i]) {
                    putstr("*** FAIL: mismatch on ");
                    puttimn(dev);
                    putstr(", channel ");
                    putudec(i + 1);
                    putstr(": expected ");
                    putudec(first_count);
                    putstr(", got ");
                    putudec(counts[i]);
                    println();
                }
            }
        } else {
            puttimn(dev);
            putstrln(" [ok]");
        }
        v_println();

        // Clean up
        for (int c = 1; c <= 4; c++) {
            if (timer_has_cc_ch(dev, c)) {
                timer_set_mode(dev, c, TIMER_DISABLED);
            }
        }
        break;
    }
}

//
// Helper implementations
//

static void _delay(uint32 msec) {
    uint32 end = systick_uptime() + msec;
    while (systick_uptime() < end)
        ;
}

static void init_usart(usart_dev *dev, gpio_dev *gdev, uint8 tx, uint8 rx) {
    usart_config_gpios_async(dev, gdev, rx, gdev, tx, 0);
    usart_init(dev);
    usart_set_baud_rate(dev, USART_USE_PCLK, COMM_USART_BAUD);
    usart_enable(dev);
}

static bool timer_has_cc_ch(timer_dev *dev, int ch) {
    ASSERT(1 <= ch && ch <= 4);
    if (dev->type == TIMER_BASIC)
        return false;
    int tn = timerNumber(dev);
    return  (// TIM1-5 and 8 have all four channels
             (tn <= 5 || tn == 8) ||
             // TIM9 and 12 only have channels 1 and 2
             ((tn == 9 || tn == 12) && ch <= 2) ||
             // All other general purpose timers only have channel 1
             (ch == 1));
}

static void putstr(const char str[]) {
    usart_putstr(COMM_USART, str);
}

static void println(void) {
    putstr("\r\n");
}

static void putstrln(const char str[]) {
    putstr(str);
    println();
}

static void putudec(uint32 val) {
    usart_putudec(COMM_USART, val);
}

static void puttimn(timer_dev *dev) {
    putstr("TIM");
    putudec(timerNumber(dev));
}

static void v_putstr(const char str[]) {
    if (verbose) putstr(str);
}

static void v_println() {
    if (verbose) println();
}

__attribute__((unused)) /* (shut up, gcc) */
static void v_putstrln(const char str[]) {
    if (verbose) putstrln(str);
}

static void v_putudec(uint32 val) {
    if (verbose) putudec(val);
}

static void v_puttimn(timer_dev *dev) {
    if (verbose) puttimn(dev);
}

// Used to visually separate output from different tests
static void printBanner(void) {
    putstrln("-----------------------------------------------------");
}

static void initTimer(timer_dev *dev) {
    v_puttimn(dev);
    timer_init(dev);
    switch (dev->type) {
    case TIMER_ADVANCED:
    case TIMER_GENERAL:
        v_putstr(" channels ");
        for (int c = 1; c <= 4; c++) {
            if (timer_has_cc_ch(dev, c)) {
                v_putudec(c);
                v_putstr(" ");
                timer_set_mode(dev, c, TIMER_OUTPUT_COMPARE);
            }
        }
        break;
    case TIMER_BASIC:
        break;
    }
    v_println();
}

static int timerNumber(timer_dev *dev) {
    switch (dev->clk_id) {
    case RCC_TIMER1: return 1;
    case RCC_TIMER2: return 2;
    case RCC_TIMER3: return 3;
    case RCC_TIMER4: return 4;
    case RCC_TIMER5: return 5;
    case RCC_TIMER6: return 6;
    case RCC_TIMER7: return 7;
    case RCC_TIMER8: return 8;
    case RCC_TIMER9: return 9;
    case RCC_TIMER10: return 10;
    case RCC_TIMER11: return 11;
    case RCC_TIMER12: return 12;
    case RCC_TIMER13: return 13;
    case RCC_TIMER14: return 14;
    default:
        ASSERT(0);
        return 0;
    }
}

//
// IRQ Handlers
//

static void handler1(void) {
    count1++;
}

static void handler2(void) {
    count2++;
}

static void handler3(void) {
    count3++;
}

static void handler4(void) {
    count4++;
}

//
// init() and main()
//

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }
    return 0;
}

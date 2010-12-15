.. highlight:: cpp

.. _timers:

Timers
======

There are four general purpose timers in the Maple microcontroller
that can be configured to generate periodic or delayed events with
minimal work done by the microcontroller. For example, the :ref:`PWM
<pwm>` channels can generate regular square-wave signals on specific
output pins without consuming extra clock cycles. By attaching
interrupt handlers to these channels (instead of just changing the
voltage on an external pin), more complex events can be scheduled.

.. contents:: Contents
   :local:

Introduction
------------

.. _timers-prescale:

The four timers each have four separate compare channels. Each channel
has an associated 16-bit counter that can be configured with a 16-bit
prescaler and a 16-bit overflow value.  The prescaler determines how
fast the counter changes, while the overflow value determines when it
gets reset.

The prescaler acts as a divider of the 72MHz system clock.  That is,
with a prescaler of 1, the channel's counter increments with a
frequency of 72MHz, rolling over (passing the maximum 16-bit unsigned
integer value of 65,535) more than a thousand times a second.  With a
prescaler of 7200, it has a frequency of (72/7200) MHz = 10 KHz,
rolling over approximately every 6.55 seconds.

The overflow value is the maximum value the counter will go up to. It
defaults to the full 65,535; smaller values will cause the counter to
reset to zero more frequently.

Whenever a channel's counter reaches its overflow value, an "update
event" interrupt is generated.  You can configure the Maple to notify
you when this takes place, by registering an interrupt handler, which
is a function that will be called when the update event occurs.

libmaple Reference
------------------

The libmaple API for interacting with timers is documented at the
:ref:`HardwareTimer reference <lang-hardwaretimer>`.

Caveats
-------

.. _timers-pwm-conflicts:

**PWM Conflicts:** Because PWM functionality on a given pin depends on
the configuration of the timer and channel, you must chose your
channels carefully if you want to use both timer interrupts and PWM in
the same program. Refer to the following table to match up timer
channels and Maple header pin numbers:

.. _timers-pin-channel-map:

.. csv-table::
   :header: Timer, Ch. 1 pin, Ch. 2 pin, Ch. 3 pin, Ch. 4 pin

   ``Timer1``,  6,  7,  8, --
   ``Timer2``,  2,  3,  1,  0
   ``Timer3``, 12, 11, 27, 28
   ``Timer4``,  5,  9, 14, 24

**Overhead:** there is some overhead associated with function and
interrupt calls (loading and unloading the stack, preparing state,
etc.) and this overhead can fudge your timing. Imperfect code
branching also means that, e.g., channel 1 interrupts may get called a
couple clock cycles sooner than a channel 4 interrupt, all other
configuration being the same.

.. compound::

   **Jitter:** other interrupts (USB, Serial, SysTick, or other
   timers) can and will get called before or during the timer
   interrupt routines, causing pseudorandom delays and other
   frustrations.

   Disabling the USB port (by calling ``SerialUSB.end()``, or just
   running off a battery) helps a lot, but then you lose the
   auto-reset and communications functionality.  This will require
   that you put your Maple into :ref:`perpetual bootloader mode
   <troubleshooting-perpetual-bootloader>` before uploading a new
   program to it (or somehow causing your program to re-enable serial
   over USB using :ref:`SerialUSB.begin() <lang-serialusb-begin>`).

   Disabling SysTick with ``systick_disable()`` helps as well.
   However, calling this function will break the ``micros()`` and
   ``millis()`` functions.

**General:** working with timers and interrupts can be tricky and hard
to debug; they are a somewhat "advanced" topic. Start simple, test
with :ref:`ASSERT() <language-assert>`, and don't try to do too much
in your interrupt handlers! Make sure that what you're trying to do in
a handler isn't going to block other interrupts from firing (e.g. USB,
Serial, SysTick) if those other interrupts are important for your
program.

SysTick Peripheral
------------------

The SysTick peripheral allows another, simple way to perform periodic
or delayed events. This separate timer does not conflict with any
other peripherals, but the associated 1kHz interrupt can jitter the
general purpose timer interrupts; this is clearly seen when running
VGA code, where the timing jitters are transformed into visual jags in
the image.  The SysTick peripheral can be disabled by calling
``systick_disable()``, and re-enabled using ``systick_resume()``.

Code Examples
-------------

LED blink
^^^^^^^^^

::

    #define LED_RATE 500000    // in microseconds; should give 0.5Hz toggles

    void handler_led(void);

    void setup()
    {
        // Set up the LED to blink
        pinMode(BOARD_LED_PIN, OUTPUT);

        // Setup Timer
        Timer2.setChannel1Mode(TIMER_OUTPUTCOMPARE);
        Timer2.setPeriod(LED_RATE); // in microseconds
        Timer2.setCompare1(1);      // overflow might be small
        Timer2.attachCompare1Interrupt(handler_led);
    }

    void loop() {
        // Nothing! It's all in the interrupts
    }

    void handler_led(void) {
        toggleLED();
    }

Racing Counters
^^^^^^^^^^^^^^^

::

    void handler_count1(void);
    void handler_count2(void);

    int count1 = 0;
    int count2 = 0;

    void setup()
    {
        // Set up BUT for input
        pinMode(BOARD_BUTTON_PIN, INPUT_PULLUP);

        // Setup Counting Timers
        Timer3.setChannel1Mode(TIMER_OUTPUTCOMPARE);
        Timer4.setChannel1Mode(TIMER_OUTPUTCOMPARE);
        Timer3.pause();
        Timer4.pause();
        Timer3.setCount(0);
        Timer4.setCount(0);
        Timer3.setOverflow(30000);
        Timer4.setOverflow(30000);
        Timer3.setCompare1(1000);   // somewhere in the middle
        Timer4.setCompare1(1000);
        Timer3.attachCompare1Interrupt(handler1);
        Timer4.attachCompare1Interrupt(handler2);
        Timer3.resume();
        Timer4.resume();
    }

    void loop() {
        // Display the running counts
        SerialUSB.print("Count 1: ");
        SerialUSB.print(count1);
        SerialUSB.print("\t\tCount 2: ");
        SerialUSB.println(count2);

        // Run... while BUT is held, pause Count2
        for(int i = 0; i<1000; i++) {
            if(digitalRead(BOARD_BUTTON_PIN)) {
                Timer4.pause();
            } else {
                Timer4.resume();
            }
            delay(1);
        }
    }

    void handler1(void) {
        count1++;
    }
    void handler2(void) {
        count2++;
    }

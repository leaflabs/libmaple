.. highlight:: cpp

.. _timers:

========
 Timers
========

There are four general purpose timers in the Maple microcontroller
that can be configured to generate periodic or delayed events with
minimal work done by the microcontroller. For example, the :ref:`PWM
<pwm>` channels, once enabled, generate regular square-wave signals on
specific output pins that will continue even if the microcontroller is
busy crunching numbers or handling communications interrupts. By
attaching interrupt handlers to these channels (instead of just
changing the voltage on an external pin), more complex events like
printing to a serial port, updating a variable, or emitting a whale
mating call can be scheduled. You can even modify the configuration of
the timer itself at a regular interval; the possibilities are endless!

The four timers each have four separate compare channels. Each timer
is a single 16-bit counter that can be configured with both a
prescaler and an overflow value. The prescaler acts as a divider of
the 72MHz system clock; without prescaling the counter would get up to
65536 (2 to the 16th power) and roll over more than a thousand times a
second; even with the full prescaler it rolls over about once a
minute. The overflow value is the maximum value the counter will go up
to. It defaults to the full 65535; smaller values will cause the
counter to reset to zero more frequently.


Caveats
-------

**PWM Conflicts:** Because PWM functionality on a given pin depends on
the configuration of the timer and channel, you must chose your
channels carefully if you want to use both timer interrupts and PWM in
the same program. Refer to the full :ref:`pin mapping table
<pin-mapping-mega-table>` to match up timer channels and Maple header
pin numbers.

**Overhead:** there is some overhead associated with function and
interrupt calls (loading and unloading the stack, preparing state,
etc.) and this overhead can fudge your timing. Imperfect code
branching also means that, e.g., channel 1 interrupts may get called a
couple clock cycles sooner than a channel 4 interrupt, all other
configuration being the same.

.. compound::

   **Jitter:** other interrupts (USB, Serial, SysTick, or other
   timers) can and will get called before or during the timer
   interrupt routines, causing pseudo-random delays and other
   frustrations.

   Disabling the USB port (by calling ``SerialUSB.end()``, or just
   running off a battery) helps a lot, but then you lose the
   auto-reset and communications functionality.  This will require
   that you put your Maple into :ref:`perpetual bootloader mode
   <troubleshooting-perpetual-bootloader>` before uploading a new
   program to it.

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

.. _timers-modes:

General Timer Modes
-------------------

``TIMER_DISABLED``

    Exactly what it sounds like: the timer stops counting, interrupts
    are not called, and no state changes are output.

``TIMER_PWM``

    This is the default mode for pins after initialization. See the
    :ref:`PWM docs <pwm>` for more information on this mode.

    .. note::
    
       ``Timer1.setChannel1Mode(TIMER_PWM)`` may not work as expected;
       if you want PWM functionality on a channel, make sure you don't
       set it to something else.

``TIMER_OUTPUTCOMPARE``

    In this mode, the timer counts from 0 to the overflow value
    repeatedly; every time the counter value reaches one of the
    channel compare values, the corresponding interrupt is fired.

SysTick Peripheral
------------------

The SysTick peripheral allows another, simple way to perform periodic
or delayed events. This separate timer does not conflict with any
other peripherals, but the associated 1kHz interrupt can jitter the
general purpose timer interrupts; this is clearly seen when running
VGA code, where the timing jitters are transformed into visual jags in
the image.  The SysTick peripheral can be disabled by calling
``systick_disable()``, and re-enabled using ``systick_resume()``.

Function Reference
------------------

For all of these functions, ``Timer1`` can be replaced with
``Timer2``, ``Timer3``, or ``Timer4``; the channel numbers also range
from 1 to 4.

``Timer1.pause()``/\ ``Timer1.resume()``

    These functions start and stop the counter without affecting the
    rest of the configuration. These functions can be used during the
    setup period to prevent interrupts from firing before they are
    completely configured. Note that there is some function call
    overhead with these functions, so they are not a perfect way to
    align multiple timers to the same count value.

``Timer1.setOverflow(val)``

    Sets the overflow (or "reload") value for the whole timer; when
    the counter reaches this value it resets to zero. Defaults to
    65535 (the largest unsigned 16bit integer); setting it to anything
    lower will cause interrupts to be called more frequently (see the
    setPeriod function below for a shortcut). This number sets the
    maximum value for the channel compare values.

``Timer1.setPrescaleFactor(val)``

    The prescaler acts as a clock divider to slow down the rate at
    which the counter increments. For example, the system clock rate
    is 72MHz, so the counter will reach 65535 in (13.89 nanoseconds) *
    (65535 counts) = (910.22 microseconds), or about a thousand times
    a second. If you set the prescaler to 1098, then the clock rate is
    effectively 65.56KHz, and the counter will reach 65536 in (15.25
    microseconds) * (65536 counts) = (0.999 seconds), or just about
    once a second. Use the :ref:`setPeriod <timers-set-period>`
    function below if you are allergic to math!

.. _timers-set-period:

``Timer1.setPeriod(val)``

    This tricky trick will configure the prescaler and overflow values
    to generate a timer reload with a period as close to val
    microseconds as possible. It returns the chosen overflow value,
    which you can then use to set the channel compare values
    appropriately: if you just want the interrupts to fire when the
    clock rolls over and you don't care about the relative "phase",
    you can always set the channel compare values to 1.

    Remember: a microsecond is 1/1,000,000th of a second, or 1/1,000
    of a millisecond. The prescaler itself is 16bit, so the longest
    period that can be configured is 1/(72MHz) * (2^32) = (59.65
    seconds) or about a minute. You can get around this by creating an
    interrupt that increments a 32-bit variable, by using the
    ``millis()`` function, or by interfacing with an external
    real-time-clock chip.

``Timer1.setCount(val)``/\ ``Timer1.getCount()``

    These functions let you mess with the counter's brains
    directly. You can probably make it not work if you try! The timer
    is 16bit, so ``val`` and the return value of ``getCount`` are
    ``uint16``.

``Timer1.setChannel1Mode(MODE)``

    This sets the given channel (here 1) of the given timer (here 1)
    to the given mode. See the :ref:`list above <timers-modes>` for
    possible values; for interrupts you want ``TIMER_OUTPUTCOMPARE``.

``Timer1.setCompare1(val)``

    Sets the compare value for the given channel; when the counter
    reaches this value the interrupt for this channel will fire if the
    channel is in output compare mode and an interrupt is attached.

    By default this only changes the relative offsets between events
    on a single timer ("phase"); they don't control the frequency with
    which they occur. However, a common trick is to increment the
    compare value manually in the interrupt handler so that the event
    will fire again after the increment period. There can be a
    different increment value for each channel, so this trick allows
    events to be programmed at 4 different rates on a single timer!
    Note that function call overhead means that the smallest increment
    rate is a couple microseconds.

``Timer1.attachCompare1Interrupt(function)``/\ ``Timer1.detachCompare1Interrupt()``

    This is how to attach or disable an interrupt handlers to timer
    channels; this what will get called when the counter reaches the
    compare value set with ``setCompareN(val)``. ``function``
    (sometimes referred to as an ISR: "interrupt service routine")
    should be of a type that does not accept or return any values
    (C/C++ programmers: ``void (function*)(void)``). They are just
    like any other function in your sketch/program and must be
    initialized at the top of the file and defined below.

    ``function`` should try to do what it has to do as fast as
    possible. Blinking the LED, some logic, PWM updates, and Serial
    writes are fine; writing to SerialUSB or waiting for user input
    can take a long time and other compare interrupts won't fire. Tip:
    if you have a ``delay()`` in your ISR, you're probably doing it
    wrong.

    Stay vigilant here... function pointers are serious business, and
    once you go down that path you'll find yourself in a `forest of
    parentheses <http://mitpress.mit.edu/sicp/>`_ before you know it.

Code Examples
-------------

LED blink
^^^^^^^^^

\  ::

    #define LED_PIN 13
    #define LED_RATE 500000    // in microseconds; should give 0.5Hz toggles

    void handler_led(void);

    int toggle = 0;

    void setup()
    {
        // Set up the LED to blink 
        pinMode(LED_PIN, OUTPUT);

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
        toggle ^= 1;
        digitalWrite(LED_PIN, toggle);
    } 

Racing Counters
^^^^^^^^^^^^^^^

\  ::

    #define BUTTON_PIN 38

    void handler_count1(void);
    void handler_count2(void);

    int count1 = 0;
    int count2 = 0;

    void setup()
    {
        // Set up BUT for input
        pinMode(BUTTON_PIN, INPUT_PULLUP);

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
            if(digitalRead(BUTTON_PIN)) {
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

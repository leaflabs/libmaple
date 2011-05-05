.. highlight:: cpp

.. _lang-hardwaretimer:

HardwareTimer
=============

This page describes how to control the built-in timers.  It does not
describe how the timers work on your board.  For more information on
that, the :ref:`timers reference <timers>`.

.. warning:: The timer interface is still taking shape, and is
   expected to change significantly between releases.  Because of
   that, the functionality described in this page shouldn't be
   considered stable.

   If you want a timer API that will be consistent between releases of
   the Maple IDE, your best bet for now is to use the low-level
   support in :ref:`libmaple-timer`.

.. contents:: Contents
   :local:

.. _lang-hardwaretimer-getting-started:

Getting Started
---------------

You'll first need to define a ``HardwareTimer`` variable, which you'll
use to control the timer.  Do this by putting the line
"``HardwareTimer timer(number);``" with your variables, where
``number`` is the timer's number.

Here's an example (we'll fill in :ref:`setup() <lang-setup>` and
:ref:`loop() <lang-loop>` later)::

   // Use timer 1
   HardwareTimer timer(1);

   void setup() {
      // Your setup code
   }

   void loop() {
      // ...
   }

Configuring the Prescaler and Overflow
--------------------------------------

After defining your ``timer`` variable, you'll probably want to
configure how fast your timer's counter changes (using the prescaler)
and when it gets reset to zero (using the overflow value).  You can do
that with the ``setPrescaleFactor()`` and ``setOverflow()`` functions.

.. _lang-hardwaretimer-setprescalefactor:

.. doxygenfunction:: HardwareTimer::setPrescaleFactor
   :no-link:

.. _lang-hardwaretimer-setoverflow:

.. doxygenfunction:: HardwareTimer::setOverflow
   :no-link:

For example::

   // Use timer 1
   HardwareTimer timer(1);

   void setup() {
       timer.setPrescaleFactor(5);
       timer.setOverflow(255);
   }

   void loop() {
      // ...
   }

You may also find the ``setPeriod()`` function useful:

.. _lang-hardwaretimer-setperiod:

.. doxygenfunction:: HardwareTimer::setPeriod
   :no-link:

For example::

   // Use timer 1
   HardwareTimer timer(1);

   void setup() {
       // Have the timer repeat every 20 milliseconds
       int microseconds_per_millisecond = 1000;
       timer.setPeriod(20 * microseconds_per_millisecond);
   }

   void loop() {
      // ...
   }

.. _lang-hardwaretimer-interrupts:

Using Timer Interrupts
----------------------

.. TODO [0.2.0] Improve the interrupts section, here or in timers.rst

In order to use timer interrupts, we recommend the following sequence:

* Pause the timer.
* Configure the prescaler and overflow.
* Pick a timer channel to handle the interrupt and set the channel's
  :ref:`mode <lang-hardwaretimer-timermode>` to ``TIMER_OUTPUT_COMPARE``.
* Set the channel compare value appropriately (this controls what counter value,
  from 0 to overflow - 1).  If you just want to make the interrupt fire once
  every time the timer overflows, and you don't care what the timer count is,
  the channel compare value can just be 1.
* Attach an interrupt handler to the channel.
* Refresh the timer.
* Resume the timer.

Here are two complete examples.

**LED blink**: This example blinks the built-in LED without doing
anything in ``loop()``. ::

    #define LED_RATE 500000    // in microseconds; should give 0.5Hz toggles

    // We'll use timer 2
    HardwareTimer timer(2);

    void setup() {
        // Set up the LED to blink
        pinMode(BOARD_LED_PIN, OUTPUT);

        // Pause the timer while we're configuring it
        timer.pause();

        // Set up period
        timer.setPeriod(LED_RATE); // in microseconds

        // Set up an interrupt on channel 1
        timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
        timer.setCompare(TIMER_CH1, 1);  // Interrupt 1 count after each update
        timer.attachCompare1Interrupt(handler_led);

        // Refresh the timer's count, prescale, and overflow
        timer.refresh();

        // Start the timer counting
        timer.resume();
    }

    void loop() {
        // Nothing! It's all in the handler_led() interrupt:
    }

    void handler_led(void) {
        toggleLED();
    }

**Racing Counters**: This example shows how to use multiple timers at
the same time. ::

    int count3 = 0;
    int count4 = 0;

    // We'll use timers 3 and 4
    HardwareTimer timer3(3);
    HardwareTimer timer4(4);

    void setup() {
        // Set up the button for input
        pinMode(BOARD_BUTTON_PIN, INPUT_PULLUP);

        // Set up timers to add 1 to their counts each time
        // their interrupts fire.
        timer3.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
        timer4.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
        timer3.pause();
        timer4.pause();
        timer3.setCount(0);
        timer4.setCount(0);
        timer3.setOverflow(30000);
        timer4.setOverflow(30000);
        timer3.setCompare(TIMER_CH1, 1000);   // somewhere in the middle
        timer4.setCompare(TIMER_CH1, 1000);
        timer3.attachCompare1Interrupt(handler3);
        timer4.attachCompare1Interrupt(handler4);
        timer3.refresh();
        timer4.refresh();
        timer3.resume();
        timer4.resume();
    }

    void loop() {
        // Display the running counts
        SerialUSB.print("Count 3: ");
        SerialUSB.print(count3);
        SerialUSB.print("\t\tCount 4: ");
        SerialUSB.println(count4);

        // While the button is held down, pause timer 4
        for (int i = 0; i < 1000; i++) {
            if (digitalRead(BOARD_BUTTON_PIN)) {
                timer4.pause();
            } else {
                timer4.resume();
            }
            delay(1);
        }
    }

    void handler3(void) {
        count3++;
    }

    void handler4(void) {
        count4++;
    }

``HardwareTimer`` Class Reference
---------------------------------

This section gives a full listing of the capabilities of a
``HardwareTimer``.

.. doxygenclass:: HardwareTimer
   :members: HardwareTimer, pause, resume, getPrescaleFactor, setPrescaleFactor, getOverflow, setOverflow, getCount, setCount, setPeriod, setMode, getCompare, setCompare, attachInterrupt, detachInterrupt, refresh

.. _lang-hardwaretimer-timermode:

.. doxygenenum:: timer_mode

Deprecated Functionality
------------------------

The following functionality exists for now, but it has been
deprecated, and will be removed in a future Maple IDE release.  You
shouldn't use it in new programs, and you should change any of your
programs which do use them to use the up-to-date features described
above.

The ``TimerMode`` type from previous releases has been renamed
``timer_mode``.  The mode ``TIMER_OUTPUTCOMPARE`` is still present,
but will be removed in a future release.  Use ``TIMER_OUTPUT_COMPARE``
instead.

.. cpp:function:: void HardwareTimer::attachCompare1Interrupt(voidFuncPtr handler)

   Use ``attachInterrupt(1, handler)`` instead.

.. cpp:function:: void HardwareTimer::attachCompare2Interrupt(voidFuncPtr handler)

   Use ``attachInterrupt(2, handler)`` instead.

.. cpp:function:: void HardwareTimer::attachCompare3Interrupt(voidFuncPtr handler)

   Use ``attachInterrupt(3, handler)`` instead.

.. cpp:function:: void HardwareTimer::attachCompare4Interrupt(voidFuncPtr handler)

   Use ``attachInterrupt(4, handler)`` instead.

.. _lang-hardwaretimer-setchannelmode:

.. cpp:function:: void HardwareTimer::setChannelMode(int channel, timer_mode mode)

   Use ``setMode(channel, mode)`` instead.

.. cpp:function:: void HardwareTimer::setChannel1Mode(timer_mode mode)

   Use ``setMode(1, mode)`` instead.

.. cpp:function:: void HardwareTimer::setChannel2Mode(timer_mode mode)

   Use ``setMode(2, mode)`` instead.

.. cpp:function:: void HardwareTimer::setChannel3Mode(timer_mode mode)

   Use ``setMode(3, mode)`` instead.

.. cpp:function:: void HardwareTimer::setChannel4Mode(timer_mode mode)

   Use ``setMode(4, mode)`` instead.

.. cpp:function:: uint16 HardwareTimer::getCompare1()

   Use ``getCompare(1, mode)`` instead.

.. cpp:function:: uint16 HardwareTimer::getCompare2()

   Use ``getCompare(2, mode)`` instead.

.. cpp:function:: uint16 HardwareTimer::getCompare3()

   Use ``getCompare(3, mode)`` instead.

.. cpp:function:: uint16 HardwareTimer::getCompare4()

   Use ``getCompare(4, mode)`` instead.

.. cpp:function:: void HardwareTimer::setCompare1(uint16 compare)

   Use ``setCompare(1, compare)`` instead.

.. cpp:function:: void HardwareTimer::setCompare2(uint16 compare)

   Use ``setCompare(2, compare)`` instead.

.. cpp:function:: void HardwareTimer::setCompare3(uint16 compare)

   Use ``setCompare(3, compare)`` instead.

.. cpp:function:: void HardwareTimer::setCompare4(uint16 compare)

   Use ``setCompare(4, compare)`` instead.

.. cpp:function:: void HardwareTimer::detachCompare1Interrupt()

   Use ``detachInterrupt(1)`` instead.

.. cpp:function:: void HardwareTimer::detachCompare2Interrupt()

   Use ``detachInterrupt(2)`` instead.

.. cpp:function:: void HardwareTimer::detachCompare3Interrupt()

   Use ``detachInterrupt(3)`` instead.

.. cpp:function:: void HardwareTimer::detachCompare4Interrupt()

   Use ``detachInterrupt(4)`` instead.

.. cpp:function:: void HardwareTimer::generateUpdate()

   Use ``refresh()`` instead.

In previous releases, to interact with a particular timers, you would
use one of the predefined ``HardwareTimer`` instances ``Timer1``,
``Timer2``, ``Timer3``, and ``Timer4``.  These are still available for
now, but they are also deprecated, and will be removed in a future
release.  As detailed in :ref:`lang-hardwaretimer-getting-started`,
you should define your own ``HardwareTimer`` variables.

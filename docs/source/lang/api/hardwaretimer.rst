.. highlight:: cpp

.. _lang-hardwaretimer:

HardwareTimer
=============

This class defines the public API for interfacing with the STM32's
built-in timer peripherals.  More information on these peripherals
(including code examples) is available in the :ref:`timers reference
<timers>`.

.. FIXME [0.0.10] Updated HardwareTimer documentation, with deprecation

.. warning:: This class has been deprecated.  It is not available in
   the current build.

Library Documentation
---------------------

HardwareTimer Class Reference
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To interact with a particular timer, call one of the methods
documented below on one of the predefined ``HardwareTimer`` instances.
For example, to set the prescale factor on timer 1 to 5, call
``Timer1.setPrescaleFactor(5)``.

.. TODO add tutorial-style examples

.. cpp:class:: HardwareTimer

   Class for interacting with a timer.  There are four predefined
   instances available on the Maple: ``Timer1``, ``Timer2``,
   ``Timer3``, and ``Timer4``.

.. _lang-hardwaretimer-attachinterrupt:

.. cpp:function:: void HardwareTimer::attachInterrupt(int channel, voidFuncPtr handler)

   Attach an interrupt handler to the given ``channel``.  This
   interrupt handler will be called when the timer's counter reaches
   the given channel :ref:`compare <lang-hardwaretimer-setcompare>`
   value.

   ``handler`` should be a function which takes no arguments and has
   :ref:`void <lang-void>` value; i.e. it should have signature ::

       void handler(void);

   You can later detach the interrupt using :ref:`detachInterrupt()
   <lang-hardwaretimer-detachinterrupt>`.

   .. note:: The function (often called an *interrupt service
             routine*, or ISR) should attempt to return as quickly as
             possible.  :ref:`Blinking the LED <lang-toggleled>`, some
             logic, :ref:`PWM <pwm>` updates, and :ref:`Serial
             <lang-serial>` writes are fine; writing to
             :ref:`SerialUSB <lang-serialusb>` or :ref:`waiting
             <lang-waitforbuttonpress>` for user input can take a long
             time and prevent other interrupts from firing on time.

             Tip: if you have a :ref:`delay() <lang-delay>` in your
             ISR, you're probably doing it wrong.

.. cpp:function:: void HardwareTimer::attachCompare1Interrupt(voidFuncPtr handler)

   Equivalent to :ref:`attachInterrupt
   <lang-hardwaretimer-attachinterrupt>`\ ``(1, handler)``.

.. cpp:function:: void HardwareTimer::attachCompare2Interrupt(voidFuncPtr handler)

   Equivalent to :ref:`attachInterrupt
   <lang-hardwaretimer-attachinterrupt>`\ ``(2, handler)``.

.. cpp:function:: void HardwareTimer::attachCompare3Interrupt(voidFuncPtr handler)

   Equivalent to :ref:`attachInterrupt
   <lang-hardwaretimer-attachinterrupt>`\ ``(3, handler)``.

.. cpp:function:: void HardwareTimer::attachCompare4Interrupt(voidFuncPtr handler)

   Equivalent to :ref:`attachInterrupt
   <lang-hardwaretimer-attachinterrupt>`\ ``(4, handler)``.

.. _lang-hardwaretimer-setchannelmode:

.. cpp:function:: void HardwareTimer::setChannelMode(int channel, TimerMode mode)

   Set the given channel of this timer to the given :ref:`mode
   <lang-hardwaretimer-modes>`.  The parameter ``channel`` is one of
   1, 2, 3, and 4, and corresponds to the compare channel you would
   like to set.  Refer to your board's :ref:`master pin map
   <gpio-pin-maps>` to match up timer channels and pin numbers.

.. cpp:function:: void HardwareTimer::setChannel1Mode(TimerMode mode)

   Equivalent to :ref:`setChannelMode <lang-hardwaretimer-setchannelmode>`\
   ``(1, mode)``.

.. cpp:function:: void HardwareTimer::setChannel2Mode(TimerMode mode)

   Equivalent to :ref:`setChannelMode <lang-hardwaretimer-setchannelmode>`\
   ``(2, mode)``.

.. cpp:function:: void HardwareTimer::setChannel3Mode(TimerMode mode)

   Equivalent to :ref:`setChannelMode <lang-hardwaretimer-setchannelmode>`\
   ``(3, mode)``.

.. cpp:function:: void HardwareTimer::setChannel4Mode(TimerMode mode)

   Equivalent to :ref:`setChannelMode <lang-hardwaretimer-setchannelmode>`\
   ``(4, mode)``.

.. _lang-hardwaretimer-getcompare:

.. cpp:function:: uint16 HardwareTimer::getCompare(int channel)

   Gets the compare value for the given ``channel``, from 1 to 4.  See
   :ref:`setCompare() <lang-hardwaretimer-setcompare>`.

.. cpp:function:: uint16 HardwareTimer::getCompare1()

   Equivalent to :ref:`getCompare <lang-hardwaretimer-getcompare>`\
   ``(1, mode)``.

.. cpp:function:: uint16 HardwareTimer::getCompare2()

   Equivalent to :ref:`getCompare <lang-hardwaretimer-getcompare>`\
   ``(2, mode)``.

.. cpp:function:: uint16 HardwareTimer::getCompare3()

   Equivalent to :ref:`getCompare <lang-hardwaretimer-getcompare>`\
   ``(3, mode)``.

.. cpp:function:: uint16 HardwareTimer::getCompare4()

   Equivalent to :ref:`getCompare <lang-hardwaretimer-getcompare>`\
   ``(4, mode)``.

.. _lang-hardwaretimer-setcompare:

.. cpp:function:: void HardwareTimer::setCompare(int channel, uint16 compare)

   Sets the compare value for the given ``channel`` to ``compare``.
   If ``compare`` is greater than this timer's overflow value, it will
   be truncated to the overflow value.  The default compare value is
   65,535 (the largest unsigned 16-bit integer value).

   When the counter reaches this value the interrupt for this channel
   will fire if the given ``channel`` :ref:`mode
   <lang-hardwaretimer-setchannelmode>` is ``TIMER_OUTPUTCOMPARE`` and
   an interrupt is :ref:`attached
   <lang-hardwaretimer-attachinterrupt>`.

   By default, this only changes the relative offsets between events
   on a single timer ("phase"); they don't control the frequency with
   which they occur. However, a common trick is to increment the
   compare value manually in the interrupt handler so that the event
   will fire again after the increment period. There can be a
   different increment value for each channel, so this trick allows
   events to be programmed at 4 different rates on a single
   timer. Note that function call overheads mean that the smallest
   increment rate is at least a few microseconds.

.. cpp:function:: void HardwareTimer::setCompare1(uint16 compare)

   Equivalent to :ref:`setCompare <lang-hardwaretimer-setcompare>`\
   ``(1, compare)``.

.. cpp:function:: void HardwareTimer::setCompare2(uint16 compare)

   Equivalent to :ref:`setCompare <lang-hardwaretimer-setcompare>`\
   ``(2, compare)``.

.. cpp:function:: void HardwareTimer::setCompare3(uint16 compare)

   Equivalent to :ref:`setCompare <lang-hardwaretimer-setcompare>`\
   ``(3, compare)``.

.. cpp:function:: void HardwareTimer::setCompare4(uint16 compare)

   Equivalent to :ref:`setCompare <lang-hardwaretimer-setcompare>`\
   ``(4, compare)``.

.. cpp:function:: uint16 HardwareTimer::getCount()

   Gets the current timer count.  Due to function call overhead, the
   return value will be increasingly accurate with smaller prescale
   values.  Also see :ref:`setCount() <lang-hardwaretimer-setcount>`.

.. _lang-hardwaretimer-setcount:

.. cpp:function:: void HardwareTimer::setCount(uint16 val)

    Set the timer's current count to ``val``.

    Note that there is some function call overhead associated with
    calling this method, so using it is not a robust way to get
    multiple timers to share a count value.

    If ``val`` exceeds the timer's :ref:`overflow value
    <lang-hardwaretimer-getoverflow>`, it is truncated to the overflow
    value.


.. _lang-hardwaretimer-detachinterrupt:

.. cpp:function:: void HardwareTimer::detachInterrupt(int channel)

   Remove the interrupt handler attached to the given ``channel``, if
   any.  The handler will no longer be called by this timer.

.. cpp:function:: void HardwareTimer::detachCompare1Interrupt()

   Equivalent to :ref:`detachInterrupt
   <lang-hardwaretimer-detachinterrupt>`\ ``(1)``.

.. cpp:function:: void HardwareTimer::detachCompare2Interrupt()

   Equivalent to :ref:`detachInterrupt
   <lang-hardwaretimer-detachinterrupt>`\ ``(2)``.

.. cpp:function:: void HardwareTimer::detachCompare3Interrupt()

   Equivalent to :ref:`detachInterrupt
   <lang-hardwaretimer-detachinterrupt>`\ ``(3)``.

.. cpp:function:: void HardwareTimer::detachCompare4Interrupt()

   Equivalent to :ref:`detachInterrupt
   <lang-hardwaretimer-detachinterrupt>`\ ``(4)``.

.. _lang-hardwaretimer-generateupdate:

.. cpp:function:: void HardwareTimer::generateUpdate()

   Re-initializes the counter (to 0 in upcounting mode, which is the
   default), and generates an update of the prescale and overflow
   registers.

.. _lang-hardwaretimer-getoverflow:

.. cpp:function:: uint16 HardwareTimer::getOverflow()

   Gets the timer's overflow value.  See :ref:`setOverflow()
   <lang-hardwaretimer-setoverflow>`.

.. _lang-hardwaretimer-setoverflow:

.. cpp:function:: void HardwareTimer::setOverflow(uint16 val)

    Sets the timer overflow (or "reload") value to ``val``.

    When the timer's counter reaches this, value it resets to
    zero. Its default value is 65535 (the largest unsigned 16-bit
    integer); setting the overflow to anything lower will cause
    interrupts to be called more frequently (see :ref:`setPeriod()
    <lang-hardwaretimer-setperiod>` function for a shortcut).

    After the next :ref:`timer update
    <lang-hardwaretimer-generateupdate>`, this number will be the
    maximum value for the timer's channel compare values.

.. _lang-hardwaretimer-pause:

.. cpp:function:: void HardwareTimer::pause()

   Stop the timer's counter, without affecting its configuration.

   The timer will no longer count or fire interrupts after this
   function is called, until it is resumed.  This function is useful
   during timer setup periods, in order to prevent interrupts from
   firing before the timer is fully configured.

   Note that there is some function call overhead associated with this
   method, so using it in concert with :ref:`resume()
   <lang-hardwaretimer-resume>` is not a robust way to align multiple
   timers to the same count value.

.. _lang-hardwaretimer-setperiod:

.. cpp:function:: uint16 HardwareTimer::setPeriod(uint32 microseconds)

   Configure the :ref:`prescaler
   <lang-hardwaretimer-getprescalefactor>` and :ref:`overflow
   <lang-hardwaretimer-getoverflow>` values to generate a timer reload
   with a period as close to the given number of ``microseconds`` as
   possible.

   The return value is the new overflow value, which may be used to
   set channel compare values.  However, if a clock that fires an
   interrupt every given number of microseconds is all that is
   desired, and the relative "phases" are unimportant, channel compare
   values may all be set to 1.

.. _lang-hardwaretimer-getprescalefactor:

.. cpp:function:: uint16 HardwareTimer::getPrescaleFactor()

    Returns the timer's prescale factor.  See
    :ref:`setPrescaleFactor() <lang-hardwaretimer-setprescalefactor>`.

.. _lang-hardwaretimer-setprescalefactor:

.. cpp:function:: void HardwareTimer::setPrescaleFactor(uint16 factor)

    Set the timer's prescale factor to ``factor``.

    The prescaler acts as a clock divider to slow down the rate at
    which the counter increments.

    For example, the system clock rate is 72MHz, so the counter will
    reach 65535 in (13.89 nanoseconds) × (65535 counts) = (910.22
    microseconds), or about a thousand times a second. If the
    prescaler equals 1098, then the clock rate is effectively 72MHz /
    1098 = 65.56KHz, and the counter will reach 65536 in (15.25
    microseconds) × (65536 counts) = (0.999 seconds), or about once
    per second.

    The :ref:`setPeriod() <lang-hardwaretimer-setperiod>` method may
    also be used as a convenient alternative.

.. _lang-hardwaretimer-resume:

.. cpp:function:: void HardwareTimer::resume()

    Resume a paused timer, without affecting its configuration.

    The timer will resume counting and firing interrupts as
    appropriate.

    Note that there is some function call overhead associated with
    using this method, so using it in concert with :ref:`pause()
    <lang-hardwaretimer-pause>` is not a robust way to align multiple
    timers to the same count value.

.. cpp:function:: timer_dev_num HardwareTimer::getTimerNum()

   Returns the :ref:`timer device number
   <lang-hardwaretimer-timer-dev-num>` associated with the timer.  For
   example, ``Timer1.getTimerNum()`` would return ``TIMER1``.

   In most cases, you should not need to use this function.  If you do
   use it, be careful; the constant ``TIMER1`` is *not equal* to the
   number 1; similarly, ``TIMER2`` is *not* the number 2, etc.  Be
   sure to refer to the timer device number by name.

.. _lang-hardwaretimer-modes:

Timer Modes
^^^^^^^^^^^
.. doxygenenum:: TimerMode

.. _lang-hardwaretimer-timer-dev-num:

Timer Device Numbers
^^^^^^^^^^^^^^^^^^^^

These provide a lower-level interface for interacting with timers.
They are mostly useful in context with the :ref:`getTimer()
<lang-hardwaretimer-gettimer>` function.  **Be careful** when using
these not to confuse e.g. ``TIMER1`` with the number 1; they are
different.

.. doxygenenum:: timer_dev_num

.. _lang-hardwaretimer-convenience:

.. _lang-hardwaretimer-gettimer:

Other Functions
^^^^^^^^^^^^^^^
.. doxygenfunction:: getTimer

Examples
^^^^^^^^

**LED blink**::

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

**Racing Counters**::

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

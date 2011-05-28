.. highlight:: cpp

.. _lang-analogwrite:

.. _lang-api-analogwrite:


analogWrite()
=============

analogWrite() is used to create a :ref:`PWM <pwm>` wave on a pin.

.. note::

   On the Maple, calling analogWrite() is the same as calling
   :ref:`lang-pwmwrite`.  We recommend writing pwmWrite() instead of
   analogWrite().

   This is because PWM is not true analog output (it's not the output
   of a `DAC
   <http://en.wikipedia.org/wiki/Digital-to-analog_converter>`_\ ), so
   the function is very badly named.  For instance, **analogWrite()
   has nothing to do with** :ref:`lang-analogread`\ , which can be
   confusing.

   We provide analogWrite() for the sake of compatibility with Arduino
   only.

.. contents:: Contents
   :local:

.. _lang-analogwrite-compatibility:

Arduino Compatibility
---------------------

There are a few important differences between Arduino's `analogWrite()
<http://arduino.cc/en/Reference/AnalogWrite>`_ and Maple's
:ref:`lang-pwmwrite` that you should keep in mind.  In each case, we
have some recommendations you can use to help converting from Arduino
to Maple.

Difference 1: Duty cycle range is different
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The first and most important difference is that the largest possible
value for the duty cycle is much bigger on the Maple.  Using Arduino's
analogWrite(), the duty cycle ranges between 0--255 (always off --
always on)\ [#fbytemax]_\ .  Using Maple's pwmWrite(), the duty cycle
ranges from 0--65,535 by default\ [#fuint16max]_\ .

This is a good thing!  The greater range of values on the Maple gives
you much more precise control over the duty cycle of your PWM output.

If you're porting code from the Arduino and want a quick-and-dirty
fix, one solution is to :ref:`map <lang-map>` the argument to
analogWrite() into the right range::

    // Arduino code:
    analogWrite(pin, duty);

    // Becomes Maple code:
    analogWrite(pin, map(duty, 0, 255, 0, 65535));

This will convert values in the range 0-255 to values in the range
0--65,535, which is the correct default range for all of the timers
which control PWM output.  See the :ref:`timers reference <timers>`
for more information.

Another fix is to consult your board's :ref:`pin maps <gpio-pin-maps>`
to find the timer which controls PWM on the pin you're using, then set
that timer's overflow to 255.  Subsequent calls to analogWrite()
should work as on the Arduino (with the same loss of precision).
Note, however, that that affects the overflow for the **entire
timer**, so other code relying on that timer (such as any
:ref:`interrupts <lang-hardwaretimer-interrupts>` the timer controls)
will likely need to be modified as well.

Difference 2: You must use pinMode() to set up PWM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The second difference is that on the Maple, you **must** set up the pin
for PWM output using :ref:`lang-pinmode`\ , with argument ``PWM``.
This should just be one extra line of code in your
:ref:`lang-setup` function.  Example::

    void setup() {
        // set up pin 9 for PWM
        pinMode(9, PWM);
    }

This also means that you can't later call :ref:`lang-digitalread`
or :ref:`lang-digitalwrite` on that pin (unless some time in
between, you use pinMode() to reconfigure that pin for ``INPUT`` or
``OUTPUT``; see the :ref:`lang-pinmode` page for more information).

Difference 3: No PWM on pin 10
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

On the Maple, the pins which support PWM are: 0, 1, 2, 3, 5, 6, 7, 8,
9, 11, 12, 14, 24, 27, and 28 or fifteen pins in total.  That's *more*
PWM-capable pins as any Arduino board, but there are differences in
*which* pins support PWM.

* On **most Arduino boards** (those with the ATmega168 or ATmega328;
  this includes the **Arduino Uno**), this function works on pins 3,
  5, 6, 9, 10, and 11, or six pins total.  Note that these boards
  support PWM on pin 10, while Maple does not.

* On the **Arduino Mega**, PWM works on pins 2 through 13, or twelve
  pins total.  Note that this board supports PWM on pins 4, 10, and
  13, while the Maple does not.

* **Older Arduino boards** with an ATmega8 only support analogWrite()
  on pins 9, 10, and 11.  Maple does not support PWM on pin 10.

In all cases, Arduino boards support PWM on pin 10, unlike Maple.  We
did our best to make PWM as pin-compatible as possible; however,
circuit layout constraints prevented us from achieving perfect
compatibility.

The "safest" pins to use for PWM output are pins 9 and 11.  These pins
work on any Arduino board and on Maple.  The "safe" pins, which work
on most recent Arduino boards, the Arduino Mega and the Maple, are
pins 3, 5, 6, 9, and 11.  Thus, if you want your project to be as
portable as possible between Maple and Arduino, we recommend using the
"safest" pins first, then the "safe" pins, then any other pins, as
necessary.

Difference 4: PWM frequency
^^^^^^^^^^^^^^^^^^^^^^^^^^^

The frequency of the PWM signal (i.e., the frequency of a complete
on/off cycle) on the Arduino is approximately 490 Hz.

On the Maple, the frequency is configurable, defaulting to about 1100
Hz, or 1.1 KHz.  This is because the PWM frequency is the frequency of
the timer which controls PWM output on the particular pin (\
:ref:`the PWM tutorial has the details <pwm>`\ ).

If your application definitely requires Arduino's PWM frequency, then
the steps are:

1. Figure out which :ref:`timer <lang-hardwaretimer>` controls PWM
   output on your pin (\ :ref:`your board's Timer Pin Map
   <gpio-pin-maps>` is your friend here).

2. Let's say it's timer ``n``, where ``n`` is some number.  You'll
   then need to put "``HardwareTimer timer(n);``" with your variables,
   as described in the :ref:`HardwareTimer
   <lang-hardwaretimer-getting-started>` reference.

3. In your :ref:`lang-setup`, put "``timer.setPeriod(2041);``".  This
   will set the timer's period to approximately 2041 microseconds,
   which is a frequency of approximately 490 Hz.

Be aware that this will change the period for the **entire timer**\ ,
and will affect anything else in your program that depends on that
timer.  The important examples are :ref:`timer interrupts
<lang-hardwaretimer-interrupts>` and :ref:`PWM
<timers-pwm-conflicts>`\ .

See Also
--------

- :ref:`pwm`
- :ref:`lang-pwmwrite`
- :ref:`BOARD_NR_PWM_PINS <lang-board-values-nr-pwm-pins>`
- :ref:`boardPWMPins <lang-board-values-pwm-pins>`

.. rubric:: Footnotes

.. [#fbytemax] This is because the value for the duty cycle on Arduino
   must fit in 1 byte of memory, and an unsigned (i.e., nonnegative)
   integer with size 1 byte can hold the values between 0 and 255.

.. [#fuint16max] This is because the value for the duty cycle on the
   Maple uses 2 bytes of memory, and an unsigned (i.e., nonnegative)
   integer with size 2 bytes can hold the values between 0 and 65,535.

.. include:: /arduino-cc-attribution.txt

.. _pwm:

PWM
===

Pulse Width Modulation (PWM) is a basic technique to create repeated square
waves (digital high/low voltage transitions) of user defined length
and duty cycle. It can be used as a way to encode an "analog" signal
on a single digital (high/low) line using the time between transitions
("pulse width") as the variable; this technique is commonly used to
send servo position and motor speed commands. Another use is to use to
the ratio of "high" and "low" time to approximate a voltage output;
this technique can be used to dim an LED or even (with careful
filtering) generate audio waveforms.

.. contents:: Contents
   :local:

Overview
--------

The Maple has a large number of 16-bit PWM outputs, each connected to
one of 4 timers.  Some configuration, such as the clock rate or
prescaling, must be common to the entire timer; see the :ref:`timer
documentation <timers>` for more information.

Note that unlike the Arduino, the Maple does not have PWM
functionality on pin D10; all other pins are :ref:`compatible
<compatibility>`.

The following table shows which timer can generate which PWM
outputs. See the :ref:`pin mapping table <pin-mapping-mega-table>` to
track down exactly which timer *channel* corresponds to each pin.

.. _pwm-timer-table:

.. csv-table::
   :header: Timer, PWM Headers
   :delim: |

   Timer1 | D6,D7,D8
   Timer2 | D0,D1,D2,D3
   Timer3 | D11,D12,D27,D28
   Timer4 | D5,D9,D14,D24

Background
----------

In its simplest form, the device is a single counter with two
variables.  The counter starts at zero, and the output starts at
"high".  The counter increments every clock cycle until it reaches the
first variable number, at which point the output goes "low".  The
counter continues incrementing until it reaches the second variable at
which point the output goes "high" again and the counter resets to
zero. The time spent with output high is called the **pulse duration**
or **duty**; the total time before repeat is the **period**.

This simple functionality could be approximated in software by setting
a GPIO high or low, but the beauty of PWM is that user code simply has
to configure the device and set the two variables and the device will
function on its own; no further microprocessor cycles will be
consumed, and a repeated high/low waveform will spew out.

The Maple has 16-bit PWM resolution, which means that the counter and
variables can be as large as 65535, as opposed to 255 with 8-bit
resolution. With a 72MHz clock rate, a PWM output could have maximum
period of about one millisecond; using a :ref:`prescaler
<lang-hardwaretimer-setprescalefactor>` (clock divider) in front of
the counter can increase this maximum period.  Setting the
:ref:`period <lang-hardwaretimer-setperiod>` to something other than
the maximum value gives further control over the total length of the
waveform.  However, this effectively limits the resolution with which
the duty can be modified: the duty must be less than or equal to the
period.

Here are some commonly used PWM configurations (note that servos are
notoriously variable, especially the lower cost models):

+-------------+----------+-----------+---------+---------------+------+
|**Purpose**  |**Period**|**Duty**   |Prescaler|Period         |Duty  |
|             |(ms)      |(ms)       |         |               |      |
+=============+==========+===========+=========+===============+======+
|LED throb    |0.020     |0--0.020   |1 (none) |65535 (default)|0--767|
|             |          |           |         |               |      |
+-------------+----------+-----------+---------+---------------+------+
|Servo control|20        |1.25 (0°)  |21       |65535 (default)|4096  |
|             |          |           |         |               |      |
|             |          |1.50 (90°) |21       |65535 (default)|4915  |
|             |          |           |         |               |      |
|             |          |1.75 (180°)|21       |65535 (default)|5734  |
|             |          |           |         |               |      |
+-------------+----------+-----------+---------+---------------+------+

Function Reference
------------------

- :ref:`lang-pinmode`
- :ref:`lang-pwmwrite`
- :ref:`Timer API<lang-hardwaretimer>` (especially :ref:`setOverflow()
  <lang-hardwaretimer-setoverflow>`, :ref:`setPrescaleFactor()
  <lang-hardwaretimer-setprescalefactor>`, and :ref:`setPeriod()
  <lang-hardwaretimer-setperiod>`).
- :ref:`Timers reference <timers>`.

Recommended Reading
-------------------

* `Wikipedia Article on Pulse-width modulation
  <http://en.wikipedia.org/wiki/Pulse-width_modulation>`_
* `Arduino tutorial on PWM <http://www.arduino.cc/en/Tutorial/PWM>`_
* `Secrets of Arduino PWM
  <http://www.arcfn.com/2009/07/secrets-of-arduino-pwm.html>`_ by Ken
  Shirriff
* `So You Want To Use PWM, Eh? <http://www.arcfn.com/2009/07/secrets-of-arduino-pwm.html>`_ at Non-Lexical Vocables
* STMicro documentation for STM32F103RB microcontroller:

  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)

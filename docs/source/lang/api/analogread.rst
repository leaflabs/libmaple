.. highlight:: cpp

.. _lang-analogread:

.. _lang-api-analogread:

analogRead()
============

Used to perform ADC conversion.

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. doxygenfunction:: analogRead

Discussion
----------

Reads the value from the specified analog pin.  The Maple boards
contain 16-channel, 12-bit analog to digital converters.  This means
that a converter will map input voltages between 0 and 3.3 volts into
integer values between 0 and 4095.  However, a number of factors
interfere with getting full accuracy and precision.  For more
information, see :ref:`adc`.

Before calling analogRead() on a pin, that pin must first be
configured for analog input, using :ref:`lang-pinMode`.  You only have
to do this once, so it's usually done in :ref:`lang-setup`\ .

Parameter Discussion
--------------------

The pin parameter is the number of the analog input pin to read from.
The pins which support analog to digital conversion have ``AIN``
listed underneath their number on your board's silkscreen.  These pin
numbers are available to your program in the :ref:`boardADCPins
<lang-board-values-adc-pins>` board-specific array.  The number of
pins which are capable of analog to digital conversion on your board
is given by the ``BOARD_NR_ADC_PINS`` constant.  These values are
documented for each board in the :ref:`Board Hardware Documentation
<index-boards>` pages.

.. note:: Pin 3 is not marked ``AIN`` on the silkscreen for Maple
   revisions through Rev 5; however **it does work** as an analog
   input pin.

Note
----

If the analog input pin is not connected to anything, the value
returned by ``analogRead()`` will fluctuate due to a number of reasons
(like the values of the other analog inputs, how close your hand is to
the board, etc.) in a "random" way.

Example
-------

::

    int analogPin = 3;     // Potentiometer wiper (middle terminal) connected
                           // to analog pin 3. outside leads to ground and +3.3V.
                           // You may have to change this value if your board
                           // cannot perform ADC conversion on pin 3.

    int val = 0;           // variable to store the value read

    void setup() {
      pinMode(analogPin, INPUT_ANALOG); // set up pin for analog input
    }

    void loop() {
      val = analogRead(analogPin);    // read the input pin
      SerialUSB.println(val);         // print the value, for debugging with
                                      // a serial monitor
    }

Arduino Compatibility
---------------------

The Arduino board contains a 6 channel (8 channels on the Mini and
Nano, 16 on the Mega), 10-bit analog to digital converter with an
input voltage range of 0V--5V. This means that it will map input
voltages between 0 and 5 volts (which is **larger** than Maple's range
of 0V-3.3V) into integer values between 0 and 1023 (which is
**smaller** than the Maple's range of 0--4095).

This yields a theoretical resolution between readings of: 5 volts /
1024 units or .0049 volts (4.9 mV) per unit on Arduino boards, which
is larger, and thus less precise, than Maple's 0.0008 volts (0.8 mV).

If your program expects Arduino-style 10-bit ADC, you can :ref:`right
shift <lang-bitshift>` the value of a Maple readout by 2, like so::

    // right shift means that the result will be between 0 and 1023;
    // be aware that you're losing a lot of precision if you do this
    int adc_reading = analogRead(pin) >> 2;

.. FIXME [0.1.0] Mention that Native can do analogReference()

On the Arduino, the input range and resolution can be changed using
the `analogReference()
<http://arduino.cc/en/Reference/AnalogReference>`_ function. Because
of hardware restrictions, this function is not available on the Maple
and Maple RET6 Edition.  If your inputs lie in a different voltage
range than 0V--3.3V, you'll need to bring them into that range before
using ``analogRead()``.  See the :ref:`ADC reference <adc-range>` for
more information.

See Also
--------

- :ref:`ADC tutorial <adc>`
- `(Arduino) Tutorial: Analog Input Pins <http://arduino.cc/en/Tutorial/AnalogInputPins>`_

.. include:: /arduino-cc-attribution.txt

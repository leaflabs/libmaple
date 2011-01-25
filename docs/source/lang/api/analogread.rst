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

Reads the value from the specified analog pin.  The Maple board
contains a 16-channel, 12-bit analog to digital converter.  This means
that it will map input voltages between 0 and 3.3 volts into integer
values between 0 and 4095.  This yields a resolution between readings
of 3.3V / 4096 units, or 0.8 millivolts.  However, a number of factors
interfere with getting full accuracy and precision.  For more
information, see :ref:`adc`.

Before calling analogRead() on a pin, that pin must first be
configured for analog input, using :ref:`lang-pinMode` (you only
have to do this once, so it's usually done in :ref:`lang-setup`\ ).

Parameter Discussion
--------------------

The pin parameter is the number of the analog input pin to read from.
Header pins on the Maple with ADC functionality (marked as "AIN" on
the silkscreen) are:

  0, 1, 2, 3, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 27, 28

Note that pins 3, 27, and 28 are not marked AIN on the silkscreen
for Maple revisions through Rev 5, however, they **do work** as
analog input pins.

Note
----

If the analog input pin is not connected to anything, the value
returned by analogRead() will fluctuate based on a number of factors
(e.g. the values of the other analog inputs, how close your hand is to
the board, etc.) in a seemingly random way.


Example
-------

 ::


    int analogPin = 3;     // potentiometer wiper (middle terminal) connected
                           // to analog pin 3. outside leads to ground and +3.3V
    int val = 0;           // variable to store the value read

    void setup() {
      pinMode(analogPin, INPUT_ANALOG); // set up pin for analog input
      SerialUSB.begin();                // set up usb virtual COM port
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

On the Arduino, the input range and resolution can be changed using
their implementation of `analogReference()
<http://arduino.cc/en/Reference/AnalogReference>`_\ . Because of the
way its hardware (as of Rev 5) was designed, it's not possible to
implement analogReference on the Maple, so this function doesn't
exist.  If your inputs lie in a different voltage range than 0V--3.3V,
you'll need to bring them into that range before using analogRead.
Some basic tools to accomplish this are `resistor dividers
<http://en.wikipedia.org/wiki/Voltage_divider>`_ and `Zener diodes
<http://en.wikipedia.org/wiki/Voltage_source#Zener_voltage_source>`_\
. However, opamps and other powered components can also be used if
greater precision is required.

See also
--------

- :ref:`ADC note <adc>`
- `(Arduino) Tutorial: Analog Input Pins <http://arduino.cc/en/Tutorial/AnalogInputPins>`_

.. include:: cc-attribution.txt

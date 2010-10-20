.. highlight:: cpp

.. _arduino-analogread:

analogRead()
============


Signature
---------

``int analogRead(int pin);``


Description
-----------

Reads the value from the specified analog pin.  The Maple board
contains a 16-channel, 12-bit analog to digital converter.  This means
that it will map input voltages between 0 and 3.3 volts into integer
values between 0 and 4095.  This yields a resolution between readings
of 3.3V / 4096 units, or 0.8 millivolts.  However, a number of factors
interfere with getting full accuracy and precision.  For more
information, see :ref:`adc`.

Before calling analogRead() on a pin, that pin must first be
configured for analog input, using :ref:`arduino-pinMode`.

The input range and resolution can be changed using
:ref:`arduino-analogReference`.

It takes about 0.8 microseconds (.0000008 seconds) to read an analog
input, so the maximum sample rate using this function is approximately
1.3 million samples per second [#fsamp]_.


Parameters
----------

**pin**

  The number of the analog input pin to read from.  Header pins on the
  Maple with ADC functionality (marked as "AIN" on the silkscreen)
  are:

    0, 1, 2, 3, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 27, 28

  Note that pins 3, 27, and 28 are not marked AIN on the silkscreen
  for Maple revisions through Rev 5, however, they **do work** as
  analog input pins.

Returns
-------

Converted input voltage as an ``int``, with value 0 to 4095, inclusive.


Note
----

If the analog input pin is not connected to anything, the value
returned by analogRead() will fluctuate based on a number of factors
(e.g. the values of the other analog inputs, how close your hand is to
the board, etc.).


Example
-------

 ::

     
    int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3
                           // outside leads to ground and +3.3V
    int val = 0;           // variable to store the value read
    
    void setup() {
      pinMode(analogPin, INPUT_ANALOG);
      SerialUSB.begin();
    }
    
    void loop() {
      val = analogRead(analogPin);    // read the input pin
      SerialUSB.println(val);         // debug value
    }


Arduino Compatibility Note
--------------------------

The Arduino board contains a 6 channel (8 channels on the Mini and
Nano, 16 on the Mega), 10-bit analog to digital converter. This means
that it will map input voltages between 0 and 5 volts into integer
values between 0 and 1023. This yields a resolution between readings
of: 5 volts / 1024 units or, .0049 volts (4.9 mV) per unit.  On the
Arduino, the input range and resolution can be changed using their
implementation of `analogReference()
<http://arduino.cc/en/Reference/AnalogReference>`_\ .

On the Arduino, it takes about 100 microseconds (0.0001 s) to read an
analog input, so the maximum reading rate is about 10,000 times a
second.


See also
--------

- :ref:`ADC note <adc>`
- :ref:`analogReference <arduino-analogreference>`
- `(Arduino) Tutorial: Analog Input Pins <http://arduino.cc/en/Tutorial/AnalogInputPins>`_


.. rubric:: Footnotes

.. [#fsamp] This is based on the current configuration of a 55.5 cycle
   sample time, at 72 MHz. However, the minimum sample time *possible*
   is 1.5 cycles, leading to a theoretical maximum of approximately 48
   million samples per second (of course, doing anything with the
   readings also consumes cycles, so this maximum can't be reached in
   practice).

   See the `STM32 Reference Manual <full-manual>`_, §§11.12.4--5
   (pp. 225--226), for more information on the low-level bit twiddling
   currently necessary to change the sample time.  For examples of how
   the ADCs are configured in libmaple, see `adc.h
   <http://github.com/leaflabs/libmaple/blob/master/libmaple/adc.h>`_
   and `adc.c
   <http://github.com/leaflabs/libmaple/blob/master/libmaple/adc.c>`_\
   .  Be aware that changing the sample time has important
   consequences related to the impedance of the device connected to
   the input pin.  If you want to make changes, as a minimum, you
   should first read ST's application notes on `ADC modes
   <stm32-adc-modes>`_ and `ADC oversampling
   <stm32-adc-oversampling>`_.

.. _arduino-analogreference:

analogReference(type)
=====================

Description
-----------

Configures the reference voltage used for analog input (i.e. the
value used as the top of the input range). The options are:




-  DEFAULT: the default analog reference of 5 volts (on 5V Arduino
   boards) or 3.3 volts (on 3.3V Arduino boards)
-  INTERNAL: an built-in reference, equal to 1.1 volts on the
   ATmega168 or ATmega328 and 2.56 volts on the ATmega8.
-  EXTERNAL: the voltage applied to the AREF pin is used as the
   reference.



Parameters
----------

type: which type of reference to use (DEFAULT, INTERNAL, or
EXTERNAL).



Returns
-------

None.



Warning
-------

**If you're using an external reference voltage (applied to the AREF pin), you must set the analog reference to EXTERNAL before calling analogRead().**
Otherwise, you will short together the active reference voltage
(internally generated) and the AREF pin, possibly damaging the
microcontroller on your Arduino board.



Alternatively, you can connect the external reference voltage to
the AREF pin through a 5K resistor, allowing you to switch between
external and internal reference voltages. Note that the resistor
will alter the voltage that gets used as the reference because
there is an internal 32K resistor on the AREF pin. The two act as a
voltage divider, so, for example, 2.5V applied through the resistor
will yield 2.5 \* 32 / (32 + 5) = ~2.2V at the AREF pin.



See also
--------


-  `Description of the analog input pins <http://arduino.cc/en/Tutorial/AnalogInputPins>`_
-  `analogRead <http://arduino.cc/en/Reference/AnalogRead>`_\ ()



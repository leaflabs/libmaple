.. _adc:

=====
 ADC
=====

Analog-Digital Conversion is the process of reading a physical voltage
as a number. The Maple has a large number of pins which are capable of
taking 12-bit ADC measurements, which means that voltages from ground
to +3.3v are read as numbers from 0 to 4095; this corresponds to a
theoretical sensitivity of just under 1 millivolt. In reality, a
number of factors introduce noise and bias into this reading and a
number of techniques must be used to get good precision and accuracy.

.. compound::

   The header pins with ADC functionality (marked as "AIN" on the
   silkscreen) are:

     D0, D1, D2, D3, D10, D11, D12, D13, D15, D16, D17, D18, D19, D20, D27, D28

   Note that pins 3, 27, and 28 are not marked AIN on the silkscreen
   for Maple revisions through Rev 5, however, they **do work** as
   analog input pins.

.. contents:: Contents
   :local:

.. _adc-noise-bias:

Noise and Bias
--------------

The biggest issues with analog-digital conversion are noise and bias.
With the Maple, we have tried to isolate the ADC pins and traces from
strong noise sources but there are always trade--offs between noise,
additional functionality, cost, and package size.

The 6 ADC pins in a bank (D15--D20) generally have the least
noise and should be used for fine measurements.  If the input voltage
changes relatively slowly, a number of samples can be taken in
succession and averaged together, or the same voltage can even be
sampled by multiple ADC pins at the same time.

An important factor when taking a voltage reading is the reference
voltages that the sample is being compared against. In the case of the
Maple, the high reference is |vcc| and the low reference is ground.
This means that noise or fluctuations on either |vcc| or ground will
affect the measurement. It also means that the voltage you are trying
to sample must be between ground and 3.3V. In the case of a variable
reading, it is best if the voltage varies over the entire range of
0--3.3V; otherwise, only a fraction of the sensitivity is being
leveraged.  Resistor dividers and constant voltage diodes are basic
tools which can help bring a given voltage signal into the appropriate
range; opamps and other powered components can also be used.

.. _adc-function-reference:

Function Reference
------------------

.. doxygenfunction:: analogRead

.. doxygenfunction:: pinMode

.. doxygenenum:: WiringPinMode

.. _adc-recommended-reading:

Recommended Reading
-------------------

* `Wikipedia article on Analog-to-digital converter <http://en.wikipedia.org/wiki/Analog-to-digital_converter>`_
* `Arduino Analog Input Tutorial <http://arduino.cc/en/Tutorial/AnalogInputPins>`_
* STMicro documentation for STM32F103RB microcontroller:

  * `All <http://www.st.com/mcu/devicedocs-STM32F103RB-110.html>`_
  * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
  * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
  * `Application Note on ADC Modes (pdf) <http://www.st.com/stonline/products/literature/an/16840.pdf>`_
  * `Application Note on ADC Oversampling (pdf) <http://www.st.com/stonline/products/literature/an/14183.pdf>`_

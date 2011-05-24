.. _adc:

=====
 ADC
=====

Analog-Digital Conversion is the process of reading a physical voltage
as a number. The Maple has a large number of pins which are capable of
taking 12-bit ADC measurements, which means that voltages from 0 to
3.3V are read as numbers from 0 to 4095.  This corresponds to a
theoretical sensitivity of just under 1 millivolt. In reality, a
number of factors introduce noise and bias into this reading, and a
number of techniques must be used to get good precision and accuracy.

.. contents:: Contents
   :local:

.. _adc-noise-bias:

Noise and Bias
--------------

.. FIXME [0.0.11, Maple form factor-specific]

The biggest issues with analog-digital conversion are noise and bias.
With the Maple, we have tried to isolate the ADC pins and traces from
strong noise sources, but there are always trade--offs between noise,
additional functionality, cost, and package size.

The 6 ADC pins in a bank (D15--D20) generally have the least
noise, and should be used for fine measurements.  If the input voltage
changes relatively slowly, a number of samples can be taken in
succession and averaged together, or the same voltage can even be
sampled by multiple ADC pins at the same time.

An important factor when taking a voltage reading is the reference
voltages that the sample is being compared against. In the case of the
Maple, the high reference is |vcc| and the low reference is ground.
This means that noise or fluctuations on either |vcc| or ground will
affect the measurement. It also means that the voltage you are trying
to sample must be between ground and 3.3V.

.. _adc-range:

In the case of a variable reading, it is best if the voltage varies
over the entire range of 0--3.3V; otherwise, only a fraction of the
sensitivity is being leveraged.  Some basic tools to accomplish this
are `resistor dividers
<http://en.wikipedia.org/wiki/Voltage_divider>`_ and `Zener diodes
<http://en.wikipedia.org/wiki/Voltage_source#Zener_voltage_source>`_\
.  However, `operational amplifiers
<http://en.wikipedia.org/wiki/Operational_amplifier>`_ and other
powered components can also be used if greater precision is required.

.. _adc-function-reference:

Function Reference
------------------

* :ref:`lang-analogread`
* :ref:`lang-pinmode`

.. _adc-recommended-reading:

Recommended Reading
-------------------

* `Wikipedia: Analog-to-Digital Converter
  <http://en.wikipedia.org/wiki/Analog-to-digital_converter>`_
* `Arduino Analog Input Tutorial
  <http://arduino.cc/en/Tutorial/AnalogInputPins>`_
* ST documentation:

  * `Application Note on ADC Modes
    <http://www.st.com/stonline/products/literature/an/16840.pdf>`_ (PDF)
  * `Application Note on ADC Oversampling
    <http://www.st.com/stonline/products/literature/an/14183.pdf>`_ (PDF)

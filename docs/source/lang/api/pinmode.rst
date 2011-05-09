.. highlight:: cpp

.. _lang-pinmode:

pinMode()
=========

.. contents:: Contents
   :local:

Library Documentation
---------------------

.. doxygenfunction:: pinMode

.. _lang-pinmode-wiringpinmode:

.. doxygenenum:: WiringPinMode

Discussion
----------

``pinMode()`` is usually called within :ref:`lang-setup` in order to
configure a pin for a certain usage (although it may be called
anywhere).

Example
-------

::

    int ledPin = 13;                 // LED connected to digital pin 13

    void setup() {
      pinMode(ledPin, OUTPUT);      // sets the digital pin as output
    }

    void loop() {
      digitalWrite(ledPin, HIGH);   // sets the LED on
      delay(1000);                  // waits for a second
      digitalWrite(ledPin, LOW);    // sets the LED off
      delay(1000);                  // waits for a second
    }

Arduino Compatibility
---------------------

.. TODO check out Arduino vs. Maple static discilpline cutoffs to
.. ensure accuracy of following:

The libmaple implementation of ``pinMode()`` supports the ``INPUT``
and ``OUTPUT`` modes with semantics identical to that of the Arduino
function (however, be advised that the Maple, as a 3.3V device, will
only drive 3.3V to an ``OUTPUT`` pin that has been set ``HIGH``).

``INPUT_ANALOG`` and ``PWM`` modes were added because the Maple does
not distinguish between analog and digital pins the same way the
Arduino does.  Unlike the Arduino, you **must call** ``pinMode()`` to
set up a pin for these purposes before a call to, e.g.,
:ref:`lang-analogRead`.  In practice, this should only add a few lines
to your :ref:`lang-setup` function.

.. TODO [0.1.0] verify following before putting it in:

.. ``OUTPUT_OPEN_DRAIN``, ``INPUT_PULLUP``, ``INPUT_PULLDOWN``, and
.. ``PWM_OPEN_DRAIN`` modes represent functionality not currently
.. available on Arduino boards.

See Also
--------

-  :ref:`lang-constants`
-  :ref:`lang-digitalwrite`
-  :ref:`lang-digitalread`
-  Maple :ref:`GPIO <gpio>` reference page

.. include:: /arduino-cc-attribution.txt

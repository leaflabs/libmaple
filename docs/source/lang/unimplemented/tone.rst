.. _lang-tone:

tone()
======

Description
-----------

Generates a square wave of the specified frequency (and 50% duty
cycle) on a pin. A duration can be specified, otherwise the wave
continues until a call to
`noTone <http://arduino.cc/en/Reference/NoTone>`_\ (). The pin can be
connected to a piezo buzzer or other speaker to play tones.

Only one tone can be generated at a time. If a tone is already
playing on a different pin, the call to tone() will have no effect.
If the tone is playing on the same pin, the call will set its
frequency.

Use of the tone() function will interfere with PWM output on pins 3
and 11 (on boards other than the Mega).

**NOTE:** if you want to play different pitches on multiple pins,
you need to call noTone() on one pin before calling tone() on the
next pin.

Syntax
------

tone(pin, frequency)
tone(pin, frequency, duration)

Parameters
----------

pin: the pin on which to generate the tone

frequency: the frequency of the tone in hertz

duration: the duration of the tone in milliseconds (optional)

Returns
-------

nothing

See Also
--------

-  `noTone <http://arduino.cc/en/Reference/NoTone>`_\ ()
-  `analogWrite <http://arduino.cc/en/Reference/AnalogWrite>`_\ ()
-  `Tutorial:Tone <http://arduino.cc/en/Tutorial/Tone>`_
-  `Tutorial:Pitch follower <http://arduino.cc/en/Tutorial/Tone2>`_
-  `Tutorial:Simple Keyboard <http://arduino.cc/en/Tutorial/Tone3>`_
-  `Tutorial: multiple tones <http://arduino.cc/en/Tutorial/Tone4>`_
-  `Tutorial: PWM <http://arduino.cc/en/Tutorial/PWM>`_

.. include:: /arduino-cc-attribution.txt

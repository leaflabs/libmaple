.. _lang-notone:

noTone()
========

Description
-----------

Stops the generation of a square wave triggered by
`tone <http://arduino.cc/en/Reference/Tone>`_\ (). Has no effect if
no tone is being generated.

**NOTE:** if you want to play different pitches on multiple pins,
you need to call noTone() on one pin before calling tone() on the
next pin.

Syntax
------

noTone(pin)

Parameters
----------

pin: the pin on which to stop generating the tone

Returns
-------

Nothing.

See Also
--------

-  `tone <http://arduino.cc/en/Reference/Tone>`_ ()

.. include:: /lang/cc-attribution.txt

.. highlight:: cpp

.. _lang-unsignedchar:

``unsigned char``
=================

An unsigned version of the :ref:`char <lang-char>` data type.  An
``unsigned char`` occupies 1 byte of memory; it stores an integer from
0 to 255.

Like an :ref:`unsigned int <lang-unsignedint>`, an ``unsigned char``
won't store negative numbers; it is also subject to the same
:ref:`overflow issues <lang-int-overflow>` as any integral data type.

Example
-------

 ::

        unsigned char c = 240;

See Also
--------

- :ref:`byte <lang-byte>`
- :ref:`int <lang-int>`
- :ref:`array <lang-array>`
- :ref:`SerialUSB.println() <lang-serialusb-println>`
- :ref:`Serial.println() <lang-serial-println>`

.. include:: /arduino-cc-attribution.txt

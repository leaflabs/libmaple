.. highlight:: cpp

.. _lang-unsignedlong:

``unsigned long``
=================

An unsigned version of the :ref:`long <lang-long>` data type.  An
``unsigned long`` occupies 8 bytes of memory; it stores an integer
from 0 to 2^64-1, which is approximately 1.8×10^19 (18 quintillion, or
18 billion billion).

Like an :ref:`unsigned int <lang-unsignedint>`, an ``unsigned long``
won't store negative numbers; it is also subject to the same
:ref:`overflow issues <lang-int-overflow>` as any integral data type.

Here is an example of declaring an ``unsigned long`` variable named
``c``, then giving it value 299,792,458,000,000,000 (see :ref:`integer
constants <lang-constants-integers-u-l>` for an explanation of the "L"
at the end of the number)::

        // Speed of light in nanometers per second (approximate).
        unsigned long c = 299792458000000000L;

The general syntax for declaring an ``unsigned long`` variable named
``var``, then giving it value ``val``, looks like::

        unsigned long var = val;

See Also
--------

-  :ref:`long <lang-long>`
-  :ref:`int <lang-int>`
-  :ref:`unsigned <lang-unsignedint>`
-  :ref:`char <lang-char>`
-  :ref:`unsigned char <lang-unsignedchar>`
-  :ref:`Integer Constants <lang-constants-integers>`
-  :ref:`Variables <lang-variables>`

.. include:: cc-attribution.txt

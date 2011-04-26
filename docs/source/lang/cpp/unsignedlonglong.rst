.. highlight:: cpp

.. _lang-unsignedlonglong:

``unsigned long long``
======================

An unsigned version of the :ref:`long long <lang-longlong>` data type.
An ``unsigned long long`` occupies 8 bytes of memory; it stores an
integer from 0 to 2^64-1, which is approximately 1.8×10^19 (18
quintillion, or 18 billion billion).

A synonym for the ``unsigned long long`` type is ``uint64``.

Like an :ref:`unsigned int <lang-unsignedint>`, an ``unsigned long
long`` won't store negative numbers; it is also subject to the same
:ref:`overflow issues <lang-int-overflow>` as any integral data type.

Here is an example of declaring an ``unsigned long long`` variable
named ``c``, then giving it value 299,792,458,000,000,000 (see
:ref:`integer constants <lang-constants-integers-u-l>` for an
explanation of the "ULL" at the end of the number)::

        // Speed of light in nanometers per second (approximate).
        unsigned long long c = 299792458000000000ULL;

The general syntax for declaring an ``unsigned long long`` variable named
``var``, then giving it value ``val``, looks like::

        unsigned long long var = val;

See Also
--------

- :ref:`long long <lang-longlong>`
- :ref:`int <lang-int>`
- :ref:`unsigned <lang-unsignedint>`
- :ref:`char <lang-char>`
- :ref:`unsigned char <lang-unsignedchar>`
- :ref:`Integer Constants <lang-constants-integers>`
- :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt

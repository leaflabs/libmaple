.. highlight:: cpp

.. _lang-built-in-types:

================
 Built-in Types
================

This document serves as a reference for many of the built-in types
which are available when programming in the IDE.  Programmers using
the :ref:`command-line tools <unix-toolchain>` will have access to
these types as long as they have imported `wirish.h
<https://github.com/leaflabs/libmaple/blob/master/wirish/wirish.h>`_;
several are defined in in `libmaple_types.h
<https://github.com/leaflabs/libmaple/blob/master/libmaple/libmaple_types.h>`_.

.. _lang-built-in-types-integral:

Integral types
--------------

.. cpp:type:: char

   8-bit integer value.

.. cpp:type:: short

   16-bit integer value.

.. cpp:type:: int

   32-bit integer value.

.. cpp:type:: long

   32-bit integer value.

.. cpp:type:: long long

   64-bit integer value.

.. cpp:type:: int8

   Synonym for ``char``.

.. cpp:type:: uint8

   Synonym for ``unsigned char``.

.. cpp:type:: int16

   Synonym for ``short``.

.. cpp:type:: uint16

   Synonym for ``unsigned short``.

.. cpp:type:: int32

   Synonym for ``int``.

.. cpp:type:: uint32

   Synonym for ``unsigned int``

.. cpp:type:: int64

   Synonym for ``long long``

.. cpp:type:: uint64

   Synonym for ``unsigned long long``.

Floating-Point Types
--------------------

.. cpp:type:: float

   32-bit, IEEE 754 single-precision floating-point type.

.. cpp:type:: double

   64-bit, IEEE 754 double-precision floating-point type.

Other Types
-----------

.. cpp:type:: voidFuncPtr

   Pointer to a function that takes no arguments and returns nothing, i.e.

   ::

       typedef void (*voidFuncPtr)(void);


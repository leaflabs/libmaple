.. highlight:: c++
.. default-domain:: cpp

.. _libraries:

=========================
 Maple Library Reference
=========================

.. Note: if you port an Arduino library and document it here, be sure
.. to update compatibility.rst to reflect that fact.

This page lists the extra libraries that are part of the :ref:`Maple
IDE <ide>` (along with the rest of :ref:`libmaple <libmaple>`). You
can use a library from within a sketch by going to Sketch > Import
Library... from within the IDE, then choosing the library you want.

Any incompatibilities between the Maple and Arduino versions of a
library are noted in the library's documentation.

.. contents:: Contents
   :local:

.. toctree::
   :hidden:

   libs/servo.rst
   libs/wire.rst

.. admonition:: **Looking for Something Else?**

   - See the :ref:`language` for information on the core functions
     used for programming a Maple board.

   - If you're looking for something from the C standard library (like
     ``atoi()``, for instance): the :ref:`CodeSourcery GCC compiler
     <arm-gcc>` used to compile your programs is configured to link
     against `newlib <http://sourceware.org/newlib/>`_, and allows the
     use of any of its header files.  However, dynamic memory allocation
     (``malloc()``, etc.) is not available.

   - If you're looking for low-level hardware support libraries, see
     the :ref:`libmaple Reference <libmaple>`.

.. _libraries-servo:

Servo
-----

The :ref:`Servo <libs-servo>` library is provided for convenient
control of RC servomotors.

.. _libraries-liquid-crystal:

LiquidCrystal
-------------

.. TODO [0.1.0] LiquidCrystal docs under libs/liquidcrystal.rst

The LiquidCrystal library allows Maple to control LCD screens. For
more information, see the `Arduino LiquidCrystal documentation
<http://www.arduino.cc/en/Reference/LiquidCrystal>`_.

**Arduino Compatibility**

At this time, no incompatibilities between the Maple and Arduino
versions are known (although the Maple version should perform
significantly faster). Any observed differences should be considered
bugs, and reported on the forums.

.. _libraries-wire:

Wire
----

.. FIXME [0.1.0] Update with hard Wire implementation info

We currently provide a soft (bit-banged) implementation of the
:ref:`Wire <libs-wire>` I2C library.  A hardware version is planned
for Maple IDE release 0.1.0.

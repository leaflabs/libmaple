
.. _arm-gcc:

GCC for Maple
=============

This document provides notes on using of ``arm-none-eabi-gcc``, the
`CodeSourcery <http://www.codesourcery.com/>`_ version of the GNU `GCC
<http://gcc.gnu.org/>`_ compilers used for the Maple boards.  It is
not intended as a reference manual for GCC; such manuals are available
`elsewhere <http://gcc.gnu.org/>`_.

Obtaining ``arm-none-eabi-gcc``
-------------------------------

Recent versions of ``arm-none-eabi-gcc`` and associated tools are
included with the :ref:`Maple IDE <ide>`.

Users who wish to use ``arm-none-eabi-gcc`` directly, along with a
standard Unix Make-based toolchain, should read the
:ref:`unix-toolchain`, which describes how to set up such an
environment.

LeafLabs maintains `mirrors
<http://static.leaflabs.com/pub/codesourcery/>`_ for some of the more
recent versions of the compiler, including versions for OS X, Win32,
and 32-bit Linux.

Compiler Flags Used by libmaple
-------------------------------

This section documents the flags passed to ``arm-none-eabi-gcc`` by
the :ref:`Maple IDE <ide>` and the default Makefile provided with the
:ref:`Unix toolchain <unix-toolchain>`.  The information in this
section is subject to change between :ref:`libmaple <libmaple>`
releases.

.. highlight:: sh

The following flags are among those passed to the C compiler::

    -Os -g -mcpu=cortex-m3 -mthumb -march=armv7-m -nostdlib
    -ffunction-sections -fdata-sections -Wl,--gc-sections

In addition to those flags just given for the C compiler, the
following flags are among those passed to the C++ compiler::

    -fno-rtti -fno-exceptions -Wall

The following flags are among those passed to the assembler::

    -mcpu=cortex-m3 -march=armv7-m -mthumb

.. highlight:: cpp

.. _arm-gcc-avr-gcc:

Using the C Standard Library
----------------------------

By default (under both the :ref:`Maple IDE <ide>` and the :ref:`Unix
toolchain <unix-toolchain>`), ``arm-none-eabi-gcc`` is configured to
link against `newlib <http://sourceware.org/newlib/>`_, a C standard
library intended for use with embedded applications.  You are free to
include of any of its headers.

Switching from AVR-GCC
----------------------

This section, which is expected to grow over time, describes
techniques for porting code which uses AVR-GCC features (AVR-GCC is
the compiler used by many Atmel AVR-based microcontroller boards,
including Arduino) for use on the Maple.

.. _arm-gcc-attribute-flash:

- Replacing ``PROGMEM``: You can direct the linker script provided
  with libmaple to store a variable in Flash (instead of RAM) by using
  the libmaple macro ``__FLASH__``, like so::

      uint32 array[] __FLASH__ = {0, 1, 2};

  Be aware, however, that if you do that, you can only store values
  which are compile-time constants, and that if you attempt to change
  a variable stored in Flash, your program will crash.

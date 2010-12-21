
.. _arm-gcc:

GCC for Maple
=============

This document provides notes on the current usage of
``arm-none-eabi-gcc``, the `CodeSourcery <http://codesourcery.com>`_
version of the GNU `GCC <http://gcc.gnu.org/>`_ compilers used to
compile programs for the Maple.  It is not intended as a reference
manual for GCC; such manuals are available `elsewhere
<http://gcc.gnu.org/>`_.

Obtaining ``arm-none-eabi-gcc``
-------------------------------

Recent versions of ``arm-none-eabi-gcc`` and associated tools are
included with the :ref:`Maple IDE <ide>`.

Users who wish to use ``arm-none-eabi-gcc`` in concert with a standard
Unix toolchain are referred to our :ref:`unix-toolchain` reference,
which describes how to set up such an environment.

LeafLabs mirrors some of the more recent versions of the compiler
under http://static.leaflabs.com/pub/codesourcery/\ , including
versions for OS X, win32, and 32-bit Linux.

Compiler Flags Used by libmaple
-------------------------------

This section documents the flags passed to ``arm-none-eabi-gcc`` by
the :ref:`Maple IDE <ide>` and the default Makefile provided with
:ref:`libmaple <unix-toolchain>`.  The information in this section is
subject to change without notice.

.. highlight:: sh

The following flags are among those passed to the C compiler::

    -Os -g -mcpu=cortex-m3 -mthumb -march=armv7-m -nostdlib
    -ffunction-sections -fdata-sections -Wl,--gc-sections

The following flags are among those passed to the C++ compiler::

    -fno-rtti -fno-exceptions -Wall

The following flags are among those passed to the assembler::

    -mcpu=cortex-m3 -march=armv7-m -mthumb

.. highlight:: cpp

.. _arm-gcc-avr-gcc:

Switching from AVR-GCC
----------------------

This section, which is expected to grow over time, describes
techniques for porting code which uses AVR-GCC features (AVR-GCC is
the compiler used by many Atmel AVR-based microcontroller boards,
including Arduino) for use on the Maple.

.. _arm-gcc-attribute-flash:

- Replacing ``PROGMEM``: You can direct the linker script provided
  with libmaple to store a variable in flash by using
  ``__attribute__((section (".USER_FLASH")))``, like so::

      uint32 arr[] __attribute__((section (".USER_FLASH"))) = {...};


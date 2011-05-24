.. highlight:: sh

.. _libmaple:

``libmaple``
============

LeafLabs' libmaple (`source code on GitHub
<https://github.com/leaflabs/libmaple>`_) is the library we have
developed for the `STM32 <http://www.st.com/stonline>`_ line of ARM
Cortex M3 microcontrollers.  Its high-level interfaces are
:ref:`largely compatible <arduino-compatibility>` with the AVR
libraries written for the `Arduino <http://arduino.cc>`_ and `Wiring
<http://wiring.org.co/>`_ development boards.

libmaple is split into two pieces: a lower level layer written in pure
C, which we call *libmaple proper* (in the `libmaple/
<https://github.com/leaflabs/libmaple/tree/master/libmaple>`_
directory of the source repository), and the Wiring-style C++ API
written on top of it, called *Wirish* (in `wirish/
<https://github.com/leaflabs/libmaple/tree/master/wirish>`_).

libmaple is bundled with the :ref:`Maple IDE <ide>`.  However, we
develop it separately, and :ref:`release it standalone
<unix-toolchain>` for advanced users who might chafe at the "sketch"
programming model of the IDE.

As always, :ref:`patches are welcome <libmaple-contributing>`.

**Contents:**

.. toctree::
   :maxdepth: 1

   libmaple/overview
   libmaple/apis
   libmaple/contributing
   libmaple/coding-standard


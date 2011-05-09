.. highlight:: cpp

.. _external-interrupts:

External Interrupts
===================

External interrupts can be used to trigger routines to run in response
to changes in voltage on a pin.  Each :ref:`GPIO pin <gpio>` can be
used to detect transitions, such as when the voltage goes from
:ref:`LOW <lang-constants-low>` to :ref:`HIGH <lang-constants-high>`,
or from ``HIGH`` to ``LOW``. This can be used to avoid checking for
changes on a pin "manually" by waiting in a loop until the pin
changes.

.. _contents: Contents
   :local:

Overview
--------

External interrupts are often used to detect when events happen
outside of the microcontroller. These can be used to tell Maple when
events happen, such as when a sensor has data ready to be read, or
when a button has been pushed.  When such an event happens, an
interrupt is raised, and the Maple can react to it with a preset
*interrupt handler*, which is a function that gets called whenever the
event occurs.

.. _external-interrupts-exti-line:

Every GPIO pin can generate an external interrupt, subject to certain
constraints.  There can be a maximum of 16 different external
interrupts set up at a time.  This is because the external interrupt
lines on the STM32 are shared between GPIO ports. In effect, this
means that every pin on the Maple connects to what is called an *EXTI
line*, and within an EXTI line, only one of the pins that connects to
it can be used to detect external interrupts at a time.

The EXTI Line Pin Map for your board lists which pins connect to which
EXTI lines:

* :ref:`Maple <maple-exti-map>`
* :ref:`Maple RET6 Edition <maple-ret6-exti-map>`

.. note::

   You should set the :ref:`pin mode <lang-pinmode>` of your
   desired pin to an input mode (e.g ``INPUT`` or ``INPUT_FLOATING``,
   ``INPUT_PULLUP``, ``INPUT_PULLDOWN``).

Function Reference
------------------

- :ref:`attachInterrupt() <lang-attachinterrupt>`
- :ref:`detachInterrupt() <lang-detachinterrupt>`

Recommended Reading
-------------------

* ST manual `RM0008
  <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_
  (PDF), Chapter 9, "General-purpose and alternate-function I/Os", and
  Chapter 10, "Interrupts and Events".

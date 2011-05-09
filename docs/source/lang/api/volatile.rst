.. highlight:: cpp

.. _lang-volatile:

``volatile``
============

The ``volatile`` keyword known is a variable *qualifier*.  It is
usually used before the datatype of a variable, to modify the way in
which the compiler treats the variable.

Declaring a variable ``volatile`` is a directive to the compiler. The
compiler is software which translates your C++ code into the machine
code, which are the real instructions for the STM32 chip in the
Maple. (The particular compiler we provide for use with the Maple is a
version of :ref:`GCC <arm-gcc>`).

Specifically, it directs the compiler to read the variable's value
fresh every time it is used, rather than "backing up" the value and
reading from its backup copy. (Compilers often "back up" a variable's
value in RAM into a storage location called a *register*; this is done
for efficiency).

A variable should be declared ``volatile`` whenever its value can be
changed by something beyond the control of the code section in which
it appears, such as an :ref:`external interrupt
<external-interrupts>`. (The only place that this is likely to occur
in most programs is inside of code called by interrupts).

Example
-------

::

    // toggles LED when interrupt pin changes state

    int pin = 13;
    volatile int state = LOW;

    void setup() {
      pinMode(pin, OUTPUT);
      attachInterrupt(0, blink, CHANGE);
    }

    void loop() {
      digitalWrite(pin, state);
    }

    void blink() {
      if (state == HIGH) {
        state = LOW;
      } else {
        // state must be HIGH
        state = HIGH;
      }
    }

See Also
--------

- :ref:`External Interrupts <external-interrupts>`
- :ref:`lang-attachinterrupt`
- :ref:`lang-detachinterrupt`

.. include:: /arduino-cc-attribution.txt

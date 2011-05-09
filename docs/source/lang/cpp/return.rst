.. highlight:: cpp

.. _lang-return:

``return``
==========

Terminates a function and return a value from a function to the
calling function, if the function has non-``void`` return type.

Syntax:
-------

::

    // from within a "void" function:
    return;

    // from within a non-"void" function:
    return value;

In the second case, ``value`` should have a type which is the same as
the return type of the function, or be convertible to it (like an
``int`` to a ``double``, etc.; see :ref:`this note
<lang-arithmetic-typeconversion>` for some references).

Examples:
---------

A function to compare a sensor input to a threshold::

     // converts analog readings between 0 and 400 to 0, and 400 up to 1.
     int checkSensor() {
        if (analogRead(0) > 400) {
            return 1;
        else {
            return 0;
        }
    }

An early ``return`` is also useful when testing a section of code
without having to "comment out" large sections of possibly buggy code,
like so::

    void loop() {

        // brilliant code idea to test here

        return;

        // the rest of a dysfunctional sketch here
        // this code will never be executed
    }

See Also
--------

- :ref:`comments <lang-comments>`

.. include:: /arduino-cc-attribution.txt

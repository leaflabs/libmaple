.. highlight:: cpp

.. _lang-sq:

sq()
====

(Macro) computes the square of a number.

Syntax
------

::

    sq(a)

Parameters
----------

**a**: the number.

Returns
-------

**a** squared (**a** × **a**).

Warning
-------

Because of the way ``sq()`` is implemented, avoid using other
functions or causing side effects inside the parentheses, as it may
lead to incorrect results::

    b = sq(a++);   // avoid this - yields incorrect results

    b = sq(a);     // use this instead -
    a++;           // keep other operations outside sq()


Arduino Compatibility
---------------------

Maple's implementation of ``sq()`` is compatible with Arduino.

.. include:: /arduino-cc-attribution.txt

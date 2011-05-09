.. highlight:: cpp

.. _lang-abs:


abs()
======

(Macro) computes the absolute value of a number.

Syntax
------

::

   abs(x)

Parameters
----------

**x**: the number.

Returns
-------

**x**: if **x** is greater than or equal to 0.

**-x**: if **x** is less than 0.

Warning
-------

Because of the way ``abs()`` is implemented, avoid using other
functions or causing side effects inside the parentheses, as it may
lead to incorrect results::

    abs(a++);   // avoid this - yields incorrect results

    abs(a);       // use this instead -
    a++;          // keep other operations outside abs()


Arduino Compatibility
---------------------

Maple's implementation of ``abs()`` is compatible with Arduino.

.. include:: /arduino-cc-attribution.txt

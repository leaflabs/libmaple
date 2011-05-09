.. highlight:: cpp

.. _lang-constrain:

constrain()
===========

(Macro) Constrains a number to be within a range.

Syntax
------

::

    constrain(x, a, b)


Parameters
----------

**x**: the number to constrain

**a**: the lower end of the range

**b**: the upper end of the range

Returns
-------

**x**: if **x** is between **a** and **b**

**a**: if **x** is less than **a**

**b**: if **x** is greater than **b**

Example
-------

::

    // limits range of sensor values to between 10 and 150:
    sensVal = constrain(sensVal, 10, 150);


Warning
-------

Because of the way ``constrain()`` is implemented, avoid using other
functions or causing side effects inside the parentheses, as it may
lead to incorrect results::

    constrain(x,a++,b);   // avoid this - yields incorrect results

    constrain(x,a,b);     // use this instead-
    a++;                  // keep other math outside constrain()

Arduino Compatibility
---------------------

Maple's implementation of ``constrain()`` is compatible with Arduino.

See Also
--------

-  :ref:`min() <lang-min>`
-  :ref:`max() <lang-max>`

.. include:: /arduino-cc-attribution.txt

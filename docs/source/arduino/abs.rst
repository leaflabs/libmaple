.. _arduino-abs:

abs(x)
======

Description
-----------

(Macro) computes the absolute value of a number.

Parameters
----------

**x**: the number

Returns
-------

**x**: if **x** is greater than or equal to 0.

**-x**: if **x** is less than 0.

Warning
-------

Because of the way ``abs()`` is implemented, avoid using other
functions or causing side effects inside the brackets, as it may lead
to incorrect results ::

    abs(a++);   // avoid this - yields incorrect results
    
    a++;          // use this instead -
    abs(a);       // keep other math outside the function

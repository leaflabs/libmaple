.. _arduino-min:

min(x, y)
=========

Description
-----------

Calculates the minimum of two numbers.



Parameters
----------

x: the first number, any data type



y: the second number, any data type



Returns
-------

The smaller of the two numbers.



Examples
--------

::

    sensVal = min(sensVal, 100); // assigns sensVal to the smaller of sensVal or 100
                                 // ensuring that it never gets above 100.

Note
----

Perhaps counter-intuitively, max() is often used to constrain the
lower end of a variable's range, while min() is used to constrain
the upper end of the range.



Warning
-------

Because of the way the min() function is implemented, avoid using
other functions inside the brackets, it may lead to incorrect
results



::

    min(a++, 100);   // avoid this - yields incorrect results
    
    a++;
    min(a, 100);    // use this instead - keep other math outside the function



See also
--------


-  `max <http://arduino.cc/en/Reference/Max>`_\ ()
-  `constrain <http://arduino.cc/en/Reference/Constrain>`_\ ()

.. _arduino-max:

max(x, y)
=========

Description
-----------

Calculates the maximum of two numbers.



Parameters
----------

x: the first number, any data type



y: the second number, any data type



Returns
-------

The larger of the two parameter values.



Example
-------

::

    sensVal = max(senVal, 20); // assigns sensVal to the larger of sensVal or 20
                               // (effectively ensuring that it is at least 20)

Note
----

Perhaps counter-intuitively, max() is often used to constrain the
lower end of a variable's range, while min() is used to constrain
the upper end of the range.



Warning
-------

Because of the way the max() function is implemented, avoid using
other functions inside the brackets, it may lead to incorrect
results



::

    max(a--, 0);   // avoid this - yields incorrect results
    
    a--;           // use this instead -
    max(a, 0);     // keep other math outside the function



See also
--------


-  `min <http://arduino.cc/en/Reference/Min>`_\ ()
-  `constrain <http://arduino.cc/en/Reference/Constrain>`_\ ()

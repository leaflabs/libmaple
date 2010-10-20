.. _arduino-constrain:

constrain(x, a, b)
==================

Description
-----------

Constrains a number to be within a range.



Parameters
----------

x: the number to constrain, all data types



a: the lower end of the range, all data types



b: the upper end of the range, all data types



Returns
-------

**x**: if **x** is between **a** and **b**



**a**: if **x** is less than **a**



**b**: if **x** is greater than **b**



Example
-------

::

    sensVal = constrain(sensVal, 10, 150);
    // limits range of sensor values to between 10 and 150 



See also
--------


-  `min <http://arduino.cc/en/Reference/Min>`_\ ()
-  `max <http://arduino.cc/en/Reference/Max>`_\ ()



.. _arduino-float:

float
=====

Description
-----------

Datatype for floating-point numbers, a number that has a decimal
point. Floating-point numbers are often used to approximate analog
and continuous values because they have greater resolution than
integers. Floating-point numbers can be as large as 3.4028235E+38
and as low as -3.4028235E+38. They are stored as 32 bits (4 bytes)
of information.



Floats have only 6-7 decimal digits of precision. That means the
total number of digits, not the number to the right of the decimal
point. Unlike other platforms, where you can get more precision by
using a double (e.g. up to 15 digits), on the Arduino, double is
the same size as float.



Floating point numbers are not exact, and may yield strange results
when compared. For example ``6.0 / 3.0`` may not equal ``2.0``. You
should instead check that the absolute value of the difference
between the numbers is less than some small number.



Floating point math is also much slower than integer math in
performing calculations, so should be avoided if, for example, a
loop has to run at top speed for a critical timing function.
Programmers often go to some lengths to convert floating point
calculations to integer math to increase speed.



Examples
--------

::

        float myfloat;
        float sensorCalbrate = 1.117;



Syntax
------

::

        float var = val;




-  var - your float variable name
-  val - the value you assign to that variable



Example Code
------------

::

       int x;
       int y;
       float z;
    
       x = 1;
       y = x / 2;            // y now contains 0, ints can't hold fractions
       z = (float)x / 2.0;   // z now contains .5 (you have to use 2.0, not 2)



See Also
--------


-  `int <http://arduino.cc/en/Reference/Int>`_
-  `double <http://arduino.cc/en/Reference/Double>`_
-  `Variable Declaration <http://arduino.cc/en/Reference/VariableDeclaration>`_


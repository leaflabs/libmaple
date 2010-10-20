.. _arduino-incrementcompound:

+= , -= , \*= , /=
==================

Description
-----------

Perform a mathematical operation on a variable with another
constant or variable. The += (et al) operators are just a
convenient shorthand for the expanded syntax, listed below.



Syntax
------

::

    x += y;   // equivalent to the expression x = x + y;
    x -= y;   // equivalent to the expression x = x - y; 
    x *= y;   // equivalent to the expression x = x * y; 
    x /= y;   // equivalent to the expression x = x / y; 



Parameters
----------

x: any variable type



y: any variable type or constant



Examples
--------

::

    x = 2;
    x += 4;      // x now contains 6
    x -= 3;      // x now contains 3
    x *= 10;     // x now contains 30
    x /= 2;      // x now contains 15



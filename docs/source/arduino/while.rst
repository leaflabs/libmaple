.. _arduino-while:

while loops
===========

Description
-----------

**while** loops will loop continuously, and infinitely, until the
expression inside the parenthesis, () becomes false. Something must
change the tested variable, or the **while** loop will never exit.
This could be in your code, such as an incremented variable, or an
external condition, such as testing a sensor.



Syntax
------

::

    while(expression){
      // statement(s)
    }



Parameters
----------

expression - a (boolean) C statement that evaluates to true or
false



Example
-------

::

    var = 0;
    while(var < 200){
      // do something repetitive 200 times
      var++;
    }


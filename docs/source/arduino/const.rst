.. _arduino-const:

const keyword
=============

The **const** keyword stands for constant. It is a variable
*qualifier* that modifies the behavior of the variable, making a
variable "*read-only*". This means that the variable can be used
just as any other variable of its type, but its value cannot be
changed. You will get a compiler error if you try to assign a value
to a **const** variable.



Constants defined with the *const* keyword obey the rules of
*`variable scoping <http://arduino.cc/en/Reference/Scope>`_* that
govern other variables. This, and the pitfalls of using*#define*,
makes the *const* keyword a superior method for defining constants
and is preferred over using
*`#define <http://arduino.cc/en/Reference/Define>`_*.



Example
-------

::

    const float pi = 3.14;
    float x;
    
    // ....
    
    x = pi * 2;    // it's fine to use const's in math
    
    pi = 7;        // illegal - you can't write to (modify) a constant
    

**#define** or **const**
------------------------

You can use either **const** or **#define** for creating numeric or
string constants. For
`arrays <http://arduino.cc/en/Reference/Array>`_, you will need to
use **const**. In general *const* is preferred over *#define* for
defining constants.



See also:


-  `#define <http://arduino.cc/en/Reference/Define>`_
-  `volatile <http://arduino.cc/en/Reference/Volatile>`_


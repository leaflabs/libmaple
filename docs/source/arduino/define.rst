.. _arduino-define:

Define
======

``#define`` is a useful C component that allows the programmer to
give a name to a constant value before the program is compiled.
Defined constants in arduino don't take up any program memory space
on the chip. The compiler will replace references to these
constants with the defined value at compile time.



This can have some unwanted side effects though, if for example, a
constant name that had been #defined is included in some other
constant or variable name. In that case the text would be replaced
by the #defined number (or text).



In general, the *`const <http://arduino.cc/en/Reference/Const>`_*
keyword is preferred for defining constants and should be used
instead of #define.



Arduino defines have the same syntax as C defines:



Syntax
------

``#define constantName value``



Note that the # is necessary.



Example
-------

::

    #define ledPin 3
    // The compiler will replace any mention of ledPin with the value 3 at compile time.



Tip
---

There is no semicolon after the #define statement. If you include
one, the compiler will throw cryptic errors further down the page.



::

    #define ledPin 3;    // this is an error 



Similarly, including an equal sign after the #define statement will
also generate a cryptic compiler error further down the page.



::

    #define ledPin  = 3  // this is also an error 



See
---


-  `const <http://arduino.cc/en/Reference/Const>`_
-  `Constants <http://arduino.cc/en/Reference/IntegerConstants>`_


.. _arduino-braces:

{} Curly Braces
===============

Curly braces (also referred to as just "braces" or as "curly
brackets") are a major part of the C programming language. They are
used in several different constructs, outlined below, and this can
sometimes be confusing for beginners.



An opening curly brace "{" must always be followed by a closing
curly brace "}". This is a condition that is often referred to as
the braces being balanced. The Arduino IDE (integrated development
environment) includes a convenient feature to check the balance of
curly braces. Just select a brace, or even click the insertion
point immediately following a brace, and its logical companion will
be highlighted.



At present this feature is slightly buggy as the IDE will often
find (incorrectly) a brace in text that has been "commented out."



Beginning programmers, and programmers coming to C from the BASIC
language often find using braces confusing or daunting. After all,
the same curly braces replace the RETURN statement in a subroutine
(function), the ENDIF statement in a conditional and the NEXT
statement in a FOR loop.



Because the use of the curly brace is so varied, it is good
programming practice to type the closing brace immediately after
typing the opening brace when inserting a construct which requires
curly braces. Then insert some carriage returns between your braces
and begin inserting statements. Your braces, and your attitude,
will never become unbalanced.



Unbalanced braces can often lead to cryptic, impenetrable compiler
errors that can sometimes be hard to track down in a large program.
Because of their varied usages, braces are also incredibly
important to the syntax of a program and moving a brace one or two
lines will often dramatically affect the meaning of a program.



**The main uses of curly braces**
---------------------------------

Functions
---------

::

      void myfunction(datatype argument){
        statements(s)
      }



Loops
-----

::

      while (boolean expression)
      {
         statement(s)
      }
    
      do
      {
         statement(s)
      } while (boolean expression);
    
      for (initialisation; termination condition; incrementing expr)
      {
         statement(s)
      } 



Conditional statements
----------------------



::

      if (boolean expression)
      {
         statement(s)
      }
    
      else if (boolean expression)
      {
         statement(s)
      } 
      else
      {
         statement(s)
      }



`Reference Home <http://arduino.cc/en/Reference/HomePage>`_


.. highlight:: cpp

.. _arduino-scope:

Variable Scope
==============

Variables in the C++ programming language, which Maple uses (all of
your sketches are C++ programs in disguise), have a property called
*scope*. This is in contrast to languages such as BASIC where every
variable is a *global* variable.

A global variable is one that can be "seen" by every function in a
program. Local variables are only usable within the function in which
they are declared. In the :ref:`Maple IDE <ide>`, any variable
declared outside of a function (like :ref:`setup() <arduino-setup>`,
:ref:`loop() <arduino-loop>`, etc.), is a global variable.

When programs start to get larger and more complex, local variables
are a useful way to ensure that a function has exclusive access to its
own variables.  This prevents programming errors when one function
inadvertently modifies variables used by another function.

It is also sometimes useful to declare and initialize a variable
inside a :ref:`for <arduino-for>` loop. This creates a variable that
can only be accessed from inside the loop body.

Scope in C++ is actually a fairly complex topic.  More information is
available in the `C++ programming Wikibook
<http://en.wikibooks.org/wiki/C%2B%2B_Programming/Programming_Languages/C%2B%2B/Code/Statements/Scope>`_.

Example:
--------

::

    int globalVar;  // any function will see this variable

    void setup() {
      // ...
    }

    void loop() {
      int i;    // "i" is only "visible" inside of "loop"
      float f;  // "f" is only "visible" inside of "loop"
      // ...

      for (int j = 0; j <100; j++){
          // variable j can only be accessed inside the for-loop brackets
          i = j * j;
      }
      i = globalVar; // globalVar can be accessed from anywhere, including loop()
    }

See Also
--------

- `C++ programming Wikibook <http://en.wikibooks.org/wiki/C%2B%2B_Programming/Programming_Languages/C%2B%2B/Code/Statements/Scope>`_.
- Wikipedia article on `scope <http://en.wikipedia.org/wiki/Scope_%28programming%29>`_


.. include:: cc-attribution.txt
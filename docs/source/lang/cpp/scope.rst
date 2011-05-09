.. highlight:: cpp

.. _lang-scope:

Scope
=====

Variables in the C++ programming language, which Maple uses (all of
your sketches are C++ programs in disguise), have a property called
*scope*.  Simply put, a variable's scope is made up of all of the
lines where the variable can be used.

Scope in C++ is a fairly complex topic, so we won't try to describe it
in full here.  Instead, we present a simplified view, describing two
different kinds of scopes, *global* and *local*.  For more detailed
information, consult a C++ reference.

Global and Local Variables
--------------------------

A global variable is one that can be "seen" by every function in a
program.  In the :ref:`Maple IDE <ide>`, any variable declared outside
of a function (like :ref:`setup() <lang-setup>` and :ref:`loop()
<lang-loop>`) is a global variable.

A local variable can only be "seen" inside of a particular function.
You can declare a variable to be local to a function by declaring it
inside of the :ref:`curly braces <lang-curly-braces>` which enclose
that function.

When programs start to get larger and more complex, local variables
are a useful way to ensure that a function has exclusive access to its
own variables.  This prevents programming errors when one function
mistakenly modifies variables used by another function.

It is also sometimes useful to declare and initialize a variable
inside a :ref:`for <lang-for>` loop. This creates a variable that
can only be accessed from inside the loop body.

Example
-------

Here is an example sketch (which you can copy into the Maple IDE and
run on your Maple) that illustrates the use of global and local
variables, as well as declaring variables inside of a ``for`` loop.
Be sure to open a :ref:`serial monitor <ide-serial-monitor>` after you
:ref:`verify <ide-verify>` and :ref:`upload <ide-upload>` the sketch::

    int globalVar;  // any function will see this variable

    void setup() {
      // since "globalVar" is declared outside of any function,
      // every function can "see" and use it:
      globalVar = 50;

      // the variables "i" and "d" declared inside the "loop" function
      // can't be seen here.  see what happens when you uncomment the
      // following lines, and try to Verify (compile) the sketch:
      //
      // i = 16;
      // SerialUSB.print("i = ");
      // SerialUSB.println(i);
      // d = 26.5;
      // SerialUSB.print("d = ");
      // SerialUSB.println(d);
    }

    void loop() {
      // since "i" and "d" are declared inside of the "loop" function,
      // they can only be seen and used from inside of it:
      int i;
      double d;

      for (int j = 0; j < 5; j++) {
          // variable i can be used anywhere inside the "loop" function;
          // variable j can only be accessed inside the for-loop brackets:
          i = j * j;
          SerialUSB.print("i = ");
          SerialUSB.println(i);
      }

      // globalVar can be accessed from anywhere.  note how even
      // though we set globalVar = 50 in the "setup" function, we can
      // see that value here:
      SerialUSB.print("globalVar = ");
      SerialUSB.println(globalVar);

      // d can be accessed from anywhere inside the "loop" function:
      d = 26.5;
      SerialUSB.print("d = ");
      SerialUSB.print(d);
      SerialUSB.println(" (before separateFunction())");

      separateFunction();

      // notice how even though separateFunction() has a variable
      // named "d", it didn't touch our (local) variable which has
      // the same name:
      SerialUSB.print("d = ");
      SerialUSB.print(d);
      SerialUSB.println(" (after separateFunction())");
    }

    void separateFunction() {
      // variable "d" here has the same name as variable "d" inside of
      // the "loop" function, but since they're both _local_
      // variables, they don't affect each other:
      double d = 30.5;
      SerialUSB.print("d = ");
      SerialUSB.print(d);
      SerialUSB.println(" (inside of separateFunction())");
    }

See Also
--------

- `C++ programming Wikibook <http://en.wikibooks.org/wiki/C%2B%2B_Programming/Programming_Languages/C%2B%2B/Code/Statements/Scope>`_.
- Wikipedia article on `scope <http://en.wikipedia.org/wiki/Scope_%28programming%29>`_

.. include:: /arduino-cc-attribution.txt

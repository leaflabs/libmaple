.. highlight:: cpp

.. _lang-for:

``for``
=======

A ``for`` loop is used to repeat a block of statements enclosed in
curly braces.  ``for`` loops are useful for performing repetitive
operations, and are often used in combination with :ref:`arrays
<lang-array>` to operate on collections of data or multiple
:ref:`pins <gpio>`.  A ``for`` loop is composed of two parts: first, a
*header*, which sets up the for loop, and then a *body*, which is made
up of lines of code enclosed in curly braces.

.. contents:: Contents
   :local:

Syntax
------

There are three parts to the ``for`` loop header: an *initialization*
expression, *loop condition* expression, and a *post-loop*
expression.  The general syntax looks like this::

    for (initialization; condition; post-loop) {
        // all of these lines inside the curly braces are part
        // of the loop body.
        statement 1;
        statement 2;
        ...
    }

(Note that there is no semicolon after the post-loop).  The
initialization happens first and exactly once, before the loop begins.
Each time through the loop, the condition is tested.  The condition is
a :ref:`boolean <lang-boolean>` expression.  If it is true, then the
list of statements inside the curly braces are executed.  Next, the
post-loop is executed.  The loop then begins again by evaluating the
condition again, entering the loop body if it is true.  This proceeds
until the condition becomes false.

Examples
--------

Here's an example::

    // Dim an LED using a PWM pin
    int pwmPin = 9; // LED in series with 470 ohm resistor on pin 9

    void setup() {
       pinMode(pwmPin, PWM);
    }

    void loop() {
       for (int i=0; i <= 65535; i++) {
          pwmWrite(pwmPin, i);
          delay(1);
       }
    }

There is a ``for`` loop In the :ref:`loop() <lang-loop>` function of
the above example.  This loop starts by declaring an ``int`` variable
named ``i``, whose value starts out at zero.  The loop proceeds by
checking if ``i`` is less than or equal to 65535.  Since ``i`` is
zero, this is true, and so the calls to :ref:`pwmWrite()
<lang-pwmwrite>` and :ref:`delay() <lang-delay>` happen next.  At this
point, the post-loop expression ``i++`` is evaluated, which
:ref:`increments <lang-increment>` ``i``, so that ``i`` becomes one.
That concludes the first time through the loop.  Each "time through
the loop" is referred to as an *iteration*.

The loop then jumps back to the beginning, checking the condition as
the beginning of its second iteration (initialization is skipped,
since this only happens once, before the first iteration).  One is
less than 65535, so the loop statements are executed again.  This
proceeds over and over until the iteration when ``i`` finally
reaches 65536.  At that point, the condition is no longer true, so the
loop stops executing, and the ``loop()`` function returns.

Here's another example, using a ``for`` loop to brighten and fade an
LED (see the :ref:`pwmWrite() <lang-pwmwrite>` reference for more
information)::

    int pwmPin = 9; // hook up the LED to pin 9
    void loop() {
       int x = 1;
       for (int i = 0; i >= 0; i += x) {
          analogWrite(pwmPin, i); // controls the brightness of the LED
          if (i == 65535) {
              x = -1;             // switch direction, so i starts decreasing
          }
          delay(1);
       }
    }

Coding Tips
-----------

The C ``for`` loop is more flexible than ``for`` loops found in some
other computer languages, including BASIC.  Any or all of the three
header elements may be left blank, although the semicolons are
required. Also the statements for initialization, condition, and
post-loop can be any valid C statements, and use any C datatypes,
including :ref:`floating point numbers <lang-double>`. These types
of unusual ``for`` loops sometimes provide solutions to less-common
programming problems.

For example, using a multiplication in the post-loop line will
generate a `geometric progression
<http://en.wikipedia.org/wiki/Geometric_progression>`_::

    for(int x = 1; x <= 100; x = x * 2) {
        SerialUSB.println(x);
    }


This loop prints out the numbers 1, 2, 4, 8, ..., 64.  Check
your understanding of ``for`` loops by answering the following two
questions (answers are in footnote [#fanswers]_\ ):

1. How many iterations occur before the loop finishes?

2. Why does it stop at 64?

See Also
--------

- :ref:`while <lang-while>` loops
- :ref:`do <lang-dowhile>` loops

.. rubric:: Footnotes

.. [#fanswers]
   1. Seven.

   2. After the seventh iteration, the post-loop causes ``x`` to
      equal 128.  This is larger than 100, so the loop condition is
      false, and the loop stops.


.. include:: /arduino-cc-attribution.txt

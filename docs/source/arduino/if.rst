.. highlight:: cpp

.. _arduino-if:

if Statements
=============

An ``if`` statement is used to execute code when certain conditions
are met.  The general syntax for an ``if`` statement is::

    if (condition) {
        body
    }

An ``if`` statement first tests whether its *condition* is true (such
as an input being above a certain number).  If the condition is true,
the ``if`` statement executes its *body*, which is made up of lines of
code inside :ref:`curly braces <arduino-braces>`.  If the condition is
false, the body is not executed.  Here's a more concrete example::

    if (someVariable > 50) {
      // do something here
    }

The program tests to see if ``someVariable`` is greater than 50. If it
is, the program executes every line in the curly braces (which in the
above example does nothing, since the body is just the :ref:`comment
<arduino-comments>` line "``// do something here``").

Put another way, if the statement in parentheses is true, the
statements inside the braces are run. If not, the program skips over
the code.

An ``if`` statement's condition (which is inside the parentheses after
``if``) often uses one or more :ref:`boolean <arduino-boolean>` or
:ref:`comparison <arduino-comparison>` operators.

Writing the if Body
-------------------

The brackets may be omitted after an ``if`` statement's
conditional. If this is done, the next line (which ends in a
semicolon) becomes the only line in the body.  The following three
``if`` statements all do the same thing::

    if (x > 120) digitalWrite(ledPin, HIGH);

    if (x > 120)
        digitalWrite(ledPin, HIGH);

    if (x > 120) {
        digitalWrite(ledPin, HIGH);
    }

However, the following two examples are different::

    // example 1: two lines of code in the if body
    if (x > 120) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
    }

    // example 2: one line of code in the if body, and
    // another line of code after the if statement
    if (x > 120)
      digitalWrite(ledPin1, HIGH); // this is in the if body
      digitalWrite(ledPin2, HIGH); // this is NOT in the if body

In the first example, since the body is enclosed in curly braces, both
lines are included.  In the second example, since the curly braces are
missing, only the first line is in the ``if`` body.

See Also
--------

- :ref:`boolean operators <arduino-boolean>`
- :ref:`comparison operators <arduino-comparison>`
- :ref:`else <arduino-else>`


.. include:: cc-attribution.txt
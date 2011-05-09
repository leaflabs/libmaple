.. highlight:: cpp

.. _lang-if:

``if``/``else``
===============

An ``if`` statement is used to execute code when certain conditions
are met.  The general syntax for an ``if`` statement is::

    if (condition) {
        body
    }

An ``if`` statement first tests whether its *condition* is true (such
as an input being above a certain number).  If the condition is true,
the ``if`` statement executes its *body*, which is made up of lines of
code inside :ref:`curly braces <lang-curly-braces>`.  If the condition
is false, the body is not executed.  Here's a more concrete example::

    if (someVariable > 50) {
      // do something here
    }

The program tests to see if ``someVariable`` is greater than 50. If it
is, the program executes every line in the curly braces (which in the
above example does nothing, since the body is just the :ref:`comment
<lang-comments>` line "``// do something here``").

Put another way, if the statement in parentheses is true, the
statements inside the braces are run. If not, the program skips over
the code.

An ``if`` statement's condition (which is inside the parentheses after
``if``) often uses one or more :ref:`boolean <lang-boolean>` or
:ref:`comparison <lang-comparison>` operators.

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

``else``
--------

``if``/\ ``else`` allows greater control over the flow of code than
the basic :ref:`if <lang-if>` statement, by allowing multiple tests to
be grouped together. For example, an :ref:`analog input
<lang-analogread>` could be tested, with one action taken if the input
was less than 500, and another action taken if the input was 500 or
greater. The code would look like this::

    if (pinFiveInput < 500) {
      // action A
    } else {
      // action B
    }

``else`` can precede another ``if`` test, so that multiple, mutually
exclusive tests can be run at the same time.

Each test will proceed to the next one until a true test is
encountered. When a true test is found, its associated block of code
is run, and the program then skips to the line following the entire
if/else construction. If no test proves to be true, the default
``else`` block is executed, if one is present, and sets the default
behavior.

Note that an ``else if`` block may be used with or without a
terminating ``else`` block, and vice-versa. An unlimited number of
such ``else if`` branches is allowed.  Here is a code example::

    if (pinFiveInput < 500) {
      // do Thing A
    } else if (pinFiveInput >= 1000) {
      // do Thing B
    } else {
      // do Thing C
    }

Another way to express branching, mutually exclusive tests, is with a
:ref:`switch/case <lang-switchcase>` statement.


See Also
--------

- :ref:`boolean operators <lang-boolean>`
- :ref:`comparison operators <lang-comparison>`

.. include:: /arduino-cc-attribution.txt

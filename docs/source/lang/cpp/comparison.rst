.. highlight:: cpp

.. _lang-comparison:

Comparison Operators (``==``, ``!=``, ``<``, ``>``, ``<=``, ``>=``)
===================================================================

The comparison operators ``==``, ``!=``, ``<``, ``>``, ``<=``, and
``>=`` are used to compare two numbers.  They are :ref:`true
<lang-constants-true>` when the comparison is true, and :ref:`false
<lang-constants-false>` otherwise.  They are based on the symbols
=, ≠, <, >, ≤, and ≥ from mathematics.

Here are some examples, with their meaning in comments::

     // "eq" is true when x is equal to y
     bool eq = (x == y);

     // "neq" is true when x is different than y
     bool neq = (x != y);

     // "lt" is true when x is less than, but NOT equal to, y
     bool lt = (x <  y);

     // "gt" is true when x is greater than, but NOT equal to, y
     bool gt = (x >  y);

     // "lte" is true when x is less than or equal to y
     bool lte = (x <= y);

     // "gte" is true when x is greater than or equal to y
     bool gte = (x >= y);

The parentheses are optional; they are present only for clarity.  For
example, the following two lines are the same::

    bool eq = x == y;

    bool eq = (x == y);

Uses
----

Comparison operators, along with :ref:`boolean operators
<lang-boolean>`, are useful inside the conditionals of :ref:`if
<lang-if>` statements.  Here's one example::

    if (x < 50) {
       // only execute these lines if x is less than 50
       SerialUSB.println("delaying:");
       SerialUSB.println(x);
       delay(x);
    }

.. warning::
   Beware of accidentally using the single equal sign (``=``) when you
   meant to test if two numbers are equal (``==``).  This is a common
   mistake inside of ``if`` statement conditionals, e.g.::

       // DON'T MAKE THIS MISTAKE
       if (x = 10) {
          // body
       }

   The single equal sign is the assignment operator, and sets x to 10
   (puts the value 10 into the variable x).  Instead use the double equal
   sign (e.g. ``if (x == 10)``), which is the comparison operator, and
   tests *whether* x is equal to 10 or not. The latter statement is only
   true if x equals 10, but the former statement will always be true.

   This is because C evaluates the statement ``if (x=10)`` as follows: 10
   is assigned to x (remember that the single equal sign is the
   :ref:`assignment operator <lang-assignment>`), so x now
   contains 10. Then the 'if' conditional evaluates 10, which evaluates
   to :ref:`true <lang-constants-true>`, since any non-zero number
   evaluates to ``true``.

   Consequently, the conditional of an ``if`` statement like ``if (x =
   10) {...}`` will always evaluate to ``true``, and the variable x
   will be set to 10, which is probably not what you meant.

   (This sometimes has uses, though, so just because an assignment
   appears within a conditional doesn't mean it's automatically wrong.
   Be careful to know what you mean.)

.. include:: /arduino-cc-attribution.txt

.. highlight:: cpp

.. _lang-boolean:

Boolean Operators
=================

These can be used inside the condition of an :ref:`if <lang-if>`
statement.  Evaluate to :ref:`true <lang-constants-true>` or
:ref:`false <lang-constants-false>`.

.. contents:: Contents
   :local:

.. _lang-boolean-and:

&& (logical and)
----------------

True only if both operands are true.  For example::

    if (digitalRead(2) == HIGH  && digitalRead(3) == HIGH) { // read two switches
      // ...
    }

is true only if both inputs are high.  Another example::

    if (a >= 10 && a <= 20){}   // true if a is between 10 and 20

**Be careful** not to say ``10 <= a <= 20``!  This won't work the way
you want.  You have to separately test whether ``a`` is at least 10
using ``a >= 10``, then test whether ``a`` is at most 20 using ``a <=
20``, then combine the results using ``&&``.


.. _lang-boolean-or:

\|\| (logical or)
-----------------

True if either operand is true.  For example::

    if (x > 0 || y > 0) {
      // ...
    }

is true if either ``x`` or ``y`` is greater than 0.

.. _lang-boolean-not:

! (logical not)
---------------

True if the operand is false.  For example::

    if (!x) {
      // ...
    }

is true if ``x`` is false (i.e. if ``x`` is zero).

Some Advice
-----------

.. warning::

   Make sure you don't mistake the boolean AND operator ``&&``
   (double ampersand) for the :ref:`bitwise AND operator
   <lang-bitwisemath-and>` ``&`` (single ampersand). They are
   entirely different beasts.

   Similarly, do not confuse the boolean OR operator ``||`` (double
   pipe) with the :ref:`bitwise OR operator <lang-bitwisemath-or>`
   ``|`` (single pipe).

   The :ref:`bitwise NOT operator <lang-bitwisemath-not>` ``~``
   (tilde) looks much different than the boolean not operator ``!``
   (exclamation point, or "bang", as some programmers say), but you
   still have to be sure which one you want.


See Also
--------

- :ref:`Bitwise operators <lang-bitwisemath>` (``&``, ``|``, ``^``, ``~``)
- :ref:`Compound bitwise operators <lang-compoundbitwise>` (``&=``,
  ``|=``, ``^=``).
- :ref:`if statement <lang-if>`

.. include:: /arduino-cc-attribution.txt

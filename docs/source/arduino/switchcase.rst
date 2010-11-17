.. _arduino-switchcase:

switch / case statements
========================

Like :ref:`if/else <arduino-else>` blocks, A ``switch`` statement
controls program flow by allowing you to specify different code that
should be executed under various cases.

Syntax
------

::

    switch (var) {
    case val1:
        // statements
        break;
    case val2:
        // statements
        break;
    ...
    default:
        // statements
    }

Where ``var`` is a variable whose value to investigate, and the
``val1``, ``val2`` after each ``case`` are constant values that
``var`` might be.

Description
-----------

A ``switch`` statement compares the value of a variable to the values
specified in ``case`` statements. When a ``case`` statement is found
whose value matches that of the variable, the code in that case
statement is run.

The ``break`` keyword exits the switch statement, and is typically
used at the end of each ``case``. Without a ``break``, the ``switch``
statement will continue executing the following ``case`` expressions
("falling-through") until a ``break`` (or the end of the switch
statement) is reached.

Writing ``default:`` instead of a ``case`` statement allows you to
specify what to do if none of the ``case`` statements matches.  Having
a ``default:`` is optional (you can leave it out), but if you have
one, it must appear after all of the ``case`` statements, as shown
above.

``switch`` statements are often used with an ``enum`` value as the
variable to compare.  In this case, you can write down all of the
values the ``enum`` takes as ``case`` statements, and be sure you've
covered all the possibilities.

Example
-------

::

      switch (var) {
      case 1:
          //do something when var equals 1
          break;
      case 2:
          //do something when var equals 2
          break;
      default:
          // if nothing else matches, do the default
          // default is optional
      }

See also:
---------

`if...else <http://arduino.cc/en/Reference/Else>`_




.. include:: cc-attribution.txt
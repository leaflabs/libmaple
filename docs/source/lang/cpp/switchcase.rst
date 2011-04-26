.. highlight:: cpp

.. _lang-switchcase:

``switch``\ /\ ``case``
=======================

Like :ref:`if <lang-if>` statements, A ``switch`` statement controls
program flow by allowing you to specify different code that should be
executed under various cases.

The general syntax looks like this::

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

Here's a more concrete example::

      switch (var) {
      case 1:
          doThing1();
          break;
      case 2:
          doThing2();
          break;
      }
      afterTheSwitch();

In the above example, if ``var == 1``, then the code beginning on the
line after ``case 1`` gets executed.  That is, if ``var`` is one,
``doThing1()`` gets called first, and then the ``break`` statement is
executed.

The ``break`` keyword exits the ``switch`` statement, and is typically
used at the end of each ``case``.  Since there is a ``break`` at the
end of ``case 1``, the ``switch`` statement exits, and the next line
to be run is the one which calls ``afterTheSwitch()``.

Without a ``break``, the ``switch`` statement will continue executing
the following ``case`` expressions ("falling-through") until a
``break`` (or the end of the switch statement) is reached.  Let's
pretend the ``switch`` looked like this instead::

      switch (var) {
      case 1:
          doThing1();
          // no break statement anymore
      case 2:
          doThing2();
          break;
      }
      afterTheSwitch();

Now, if ``var`` is one, ``doThing1()`` gets executed like before.
However, without a ``break``, the code would continue to be executed
line-by-line, so ``doThing2()`` would be called next.  At this point,
a ``break`` has been reached, so the program continues by calling
``afterTheSwitch()``.  This is usually not what you want, which is why
each ``case`` usually has a ``break`` at the end.

.. _lang-switchcase-default:

Writing "``default:``" instead of a ``case`` statement allows you to
specify what to do if none of the ``case`` statements matches.  Having
a ``default`` is optional (you can leave it out), but if you have one,
it must appear after all of the ``case`` statements.  Let's add a
``default`` to the ``switch`` we've been discussing::

      switch (var) {
      case 1:
          doThing1();
          break;
      case 2:
          doThing2();
          break;
      default:
          doSomethingElse();
      }
      afterTheSwitch();

If ``var`` is one, then ``doThing1()`` gets called.  If ``var`` is
two, ``doThing2()`` gets called.  If ``var`` is anything else,
``doSomethingElse()`` gets called.  As stated above, a ``default`` is
optional.  If you're missing one and none of the ``case`` statements
match, the ``switch`` does nothing at all, as if it weren't there.

``switch`` statements are often used with an :ref:`enum <lang-enum>`
value as the variable to compare.  In this case, you can write down
all of the values the ``enum`` takes as ``case`` statements, and be
sure you've covered all the possibilities.

See Also:
---------

- :ref:`if/else <lang-if>`

.. include:: /arduino-cc-attribution.txt

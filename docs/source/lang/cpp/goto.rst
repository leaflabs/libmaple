.. highlight:: cpp

.. _lang-goto:

Labels and ``goto``
===================

A *label* gives a name to a line of code within a function.  You can
label a line by writing a name for it, then a colon (``:``), before
the line starts.  The ``goto`` keyword allows program flow to transfer
to a labeled line from anywhere within the same function.

.. warning:: The use of ``goto`` is discouraged in C and C++
   programming.  It is *never necessary* to use ``goto`` to write a
   program.

   Unless you know what you're doing, using ``goto`` tends to
   encourage code which is harder to debug and understand than
   programs without ``goto`` that do the same thing.  That said,
   however, it's sometimes useful; :ref:`see below <goto-when-to-use>`
   for a concrete example.

Using Labels and goto
---------------------

Labels and ``goto`` are probably best explained through example.
Let's start with an example of how to label lines.  The first line
(``int x = analogRead(some_pin);``) in the :ref:`loop <lang-loop>`
function below has label ``readpin``.  The third line (``delay(x);``)
has label ``startdelay``.  The second line (``SerialUSB.println(x);``)
does not have a label::

       void loop() {
       readpin:
              int x = analogRead(some_pin);
              SerialUSB.println(x); // for debugging
       startdelay:
              delay(x);
              // ... more code ...
       }

Anything which can be a :ref:`variable <lang-variables>` name can
be a label.

Let's say that we wanted to print ``x`` only if it was very large, say
at least 2000.  We might want to do this just so anybody watching on a
:ref:`serial monitor <ide-serial-monitor>` would know they were in for
a longer wait than usual.  We can accomplish this through the use of a
``goto`` statement that skips the printing if ``x`` is less than
2000::

       void loop() {
       readpin:
              int x = analogRead(some_pin);
              if (x < 2000) {
                  goto startdelay;
              }
              SerialUSB.println(x); // for debugging
       startdelay:
              delay(x);
              // ... more code ...
       }

In this modified program, whenever ``x`` is less than 2000, the body
of the :ref:`if <lang-if>` statement in the second line is
executed.  The ``goto`` statement inside the ``if`` body skips
straight to the line labeled ``startdelay``, passing over the line
doing the printing.

A ``goto`` does not have to "move forwards"; it can go "backwards",
too.  For example, the following program prints "5" forever (why?)::

    void loop() {
    printfive:
        SerialUSB.println(5);
        goto printfive;
        SerialUSB.println(6);
    }

.. _goto-when-to-use:

When to Use goto
----------------

As mentioned above, use of ``goto`` is `generally discouraged
<http://en.wikipedia.org/wiki/Goto#Criticism_and_decline>`_.  However,
when used with care, ``goto`` can simplify certain programs.  One
important use case for ``goto`` is breaking out of deeply nested
:ref:`for <lang-for>` loops or :ref:`if <lang-if>` logic blocks.
Here's an example::

    for(int r = 0; r < 255; r++) {
        for(int g = 255; g > -1; g--) {
            for(int b = 0; b < 255; b++) {
                if (analogRead(0) > 250) {
                    goto bailout;
                }
                // more statements ...
            }
            // innermost loop ends here
        }
    }
    bailout:
    // more code here

In the above example, whenever the :ref:`analog reading
<lang-analogread>` on pin 0 was greater than 250, the program would
jump to the line labeled ``bailout``, exiting all three loops at once.

While there is already a :ref:`break <lang-break>` keyword for
breaking out of a loop, it will only break out of the *innermost*
loop.  So, if instead of saying "``goto bailout;``", there was a
"``break;``" instead, the program would only exit from the loop with
header "``for(int b = 0; b < 255; b++)``".  The program would continue
at the line which reads "``// innermost loop ends here``", which is
clearly undesirable if you wanted to leave all three loops at once.

More examples of when ``goto`` is a good choice are given in Donald
Knuth's paper, "Structured Programming with go to Statements"; see
below for a link.

See Also
--------

- Dijkstra, Edsger W. `Go To Statement Considered Harmful <http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.92.4846&rep=rep1&type=pdf>`_ (PDF)

- Knuth, Donald. `Structured Programming with go to Statements <http://pplab.snu.ac.kr/courses/adv_pl05/papers/p261-knuth.pdf>`_ (PDF)

.. include:: /arduino-cc-attribution.txt

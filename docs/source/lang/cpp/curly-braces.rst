.. highlight:: cpp

.. _lang-curly-braces:

Curly Braces (``{``, ``}``)
===========================

.. contents:: Contents
   :local:

Introduction
------------

Curly braces (also referred to as just "braces" or as "curly
brackets") are a major part of the C and C++ programming
languages. They are used in several different constructs, outlined
below, and this can sometimes be confusing for beginners.

An opening curly brace, ``{`` must always be followed by a closing
curly brace ``}``. This is a condition that is often referred to as
the braces being *balanced*. The Maple IDE (integrated development
environment) includes a convenient feature to check the balance of
curly braces. Just select a brace, or even click the insertion point
immediately following a brace, and its companion will be highlighted\
[#fbug]_\ .

Beginning programmers, and programmers coming to C++ from languages
without braces, often find using them confusing or daunting.

Because the use of the curly brace is so varied, it is good
programming practice to type the closing brace immediately after
typing the opening brace when inserting a construct which requires
curly braces. Then insert some blank lines between your braces and
begin inserting statements. Your braces, and your attitude, will never
become unbalanced.

Unbalanced braces can often lead to cryptic, impenetrable compiler
errors that can sometimes be hard to track down in a large program.
Because of their varied usages, braces are also incredibly important
to the syntax of a program and moving a brace one or two lines will
usually dramatically affect the meaning of a program.

The main uses of curly braces
-----------------------------

**Functions**::

      // a function body needs braces around it
      void myFunction(datatype argument) {
        // ... function body goes in here ...
      }

**Loops** (see the :ref:`while <lang-while>`\ , :ref:`for
<lang-for>`\ , and :ref:`do/while <lang-dowhile>` loop reference
pages for more information)::

      // you should put braces around the body of a loop:

      while (boolean expression) {
         // code inside the loop goes here
      }

      for (initialisation; termination condition; incrementing expr) {
         // code inside the loop goes here
      }

      do {
         // code inside the loop goes here
      } while (boolean expression);


**Conditional statements** (see the :ref:`if statement <lang-if>`
reference page for more information)::

      // you should put braces around the body of an "if", "else if",
      // or "else":

      if (boolean expression) {
          // code inside the "if"
      }
      else if (boolean expression) {
          // code inside the "else if"
      }
      else {
          // code inside the "else"
      }

**Switch statements** (see the :ref:`switch statement
<lang-switchcase>` reference page for more information)::

      switch (var) {
      case 1:
          doThing1();
          break;
      case 2:
          doThing2();
          break;
      }

.. rubric:: Footnotes

.. [#fbug] At present this feature is slightly buggy as the IDE will
   often find (incorrectly) a brace in text that has been commented
   out.

.. include:: /arduino-cc-attribution.txt

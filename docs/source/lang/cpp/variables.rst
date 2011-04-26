.. highlight:: cpp

.. _lang-variables:

Variables
=========

A variable is a way of naming and storing a value for later use by
the program, such as data from a sensor or an intermediate value
used in a calculation.

.. contents:: Contents
   :local:

.. _lang-variables-declaring:

Declaring Variables
-------------------

Before they are used, all variables have to be *declared*. Declaring a
variable means defining its type, giving it a name, and (optionally)
giving it an initial value (this is often referred to as
*initializing* the variable).  Variables do not have to be initialized
(given a value) when they are declared, but it is good style to give
them an initial value whenever possible.

Here is an example of declaring a variable named ``inputVariable1``
with type :ref:`int <lang-int>` (the ``int`` type is used to store
integers, like -2, -1, 0, 1, etc.)::

    int inputVariable1;

In the above declaration, we did not give the variable an initial
value.  Here is another example, where we declare an ``int`` variable
named ``inputVariable2``, with an initial value of ``0``::

    int inputVariable2 = 0;

The Maple environment comes ready to use with many useful types of
variables.  See the :ref:`built-in types <lang-built-in-types>` page
for more information.

Here are a few examples of declaring variables of different types::

     int lightSensVal;
     char currentLetter;
     unsigned long long speedOfLight = 186000ULL;
     char errorMessage = {"choose another option"}; // see string

Naming Variables
----------------

The rules for naming a variable are simple.  Names for variables can
contain letters, numbers, and underscores (the underscore is the
:kbd:`_` character), and cannot begin with a number.  So
``temperature_reading``, ``tempReading``, ``tempReading1``, and
``tempReading2`` are all valid variable names, but ``4_temp_readings``
is not, because it begins with a number.

You cannot choose a name for a variable that is one of the C++
:ref:`keywords <lang-keywords>`.

Variable names are case-sensitive, so "tempreading" and "tempReading"
are different variables.  However, it is very bad style to write code
that chooses variables which are the same up to case.

You should give your variables descriptive names, so as to make your
code more readable. Variable names like ``tiltSensor`` or
``pushButton`` help you (and anyone else reading your code) understand
what the variable represents. Variable names like ``var`` or
``value``, on the other hand, do little to make your code readable.

.. _lang-variables-scope:

Variable Scope
--------------

An important choice that programmers face is where (in the program
text) to declare variables. The specific place that variables are
declared influences how various functions in a program will "see" the
variable.  This is called variable *scope*.  See the :ref:`scope
reference <lang-scope>` for more information.

.. _lang-variables-initializing:

Initializing Variables
----------------------

Variables may be *initialized* (assigned a starting value) when they
are declared or not. It is always good programming practice however to
double check that a variable has valid data in it before it is used.
Using a variable before you give it a value is a common source of
bugs.

.. _lang-variables-rollover:

Variable Rollover
-----------------

Every (numeric) type has a valid *range*.  The range of a type is the
smallest and largest value that a variable of that type can store.
For example, the :ref:`int <lang-int>` type has a range of
-2,147,483,648 to 2,147,483,647 [#frange]_.

When variables are made to exceed their range's maximum value, they
"roll over" back to their minimum value.  Note that this happens in
both directions.  It's like in the game *Pac-Man* -- when Pac-Man goes
past the right edge of the screen, he reappears on the left, and when
he goes past the left side of the screen, he reappears on the right::

       int x;
       x = -2,147,483,648;
       x = x - 1; // x now contains -2,147,483,647; rolled over "left to right"

       x = 2,147,483,647;
       x = x + 1; // x now contains -2,147,483,648; rolled over "right to left"

Each numeric type's reference page includes its range.  See the
:ref:`built-in types <lang-built-in-types>` reference for links to each
type's reference page.

Using Variables
---------------

Once variables have been declared, they are given values using the
:ref:`assignment operator <lang-assignment>`, which is a single equals
sign, ``=``. The assignment operator tells the program to store the
value on the right side of the equals sign into the variable on the
left side::

    inputVariable1 = 7;             // sets variable named inputVariable1 to 7
    inputVariable2 = analogRead(2); // sets variable named inputVariable2 to
                                    // the (digitized) input voltage read from
                                    //  analog pin #2

Once a variable has been set (assigned a value), you can test its
value to see if it meets certain conditions, or you can use its value
directly. For instance, the following code tests whether the
inputVariable2 is less than 100, then sets a delay based on
inputVariable2 (which, at that point, is at least 100)::

    if (inputVariable2 < 100) {
      inputVariable2 = 100;
    }

    delay(inputVariable2);

See Also
--------

- :ref:`lang-scope`
- :ref:`lang-built-in-types`

.. rubric:: Footnotes

.. [#frange] This range might seem a little weird at first.  The
   reasons for this range of values have to do with the fact that an
   ``int`` occupies 32 bits of memory, and the facts ::

     2^31 = -2,147,483,648
     2^31 - 1 = 2,147,483,647


   Why 2^31 instead of 2^32?  Well, that has to do with `how ints are
   (usually) stored
   <http://en.wikipedia.org/wiki/Two%27s_complement>`_ on computers.

.. include:: /arduino-cc-attribution.txt


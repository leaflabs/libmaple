.. highlight:: cpp

.. _lang-define:

``#define``
===========

``#define`` is a useful C and C++ feature that allows the programmer
to give a name to a constant value before the program is compiled.
The compiler will replace references to these constants with the
defined value at compile time.

This can have some unwanted side effects.  In general, the :ref:`const
<lang-const>` keyword is preferred for defining constants.

Syntax
------

The following line would define the name ``MY_CONSTANT`` to have value
``value``::

    #define MY_CONSTANT value

Note that the ``#`` is necessary.  It is usually good style for the
name to be capitalized, although this is not required.

There is no semicolon after the #define statement. If you include one,
the compiler will likely throw cryptic errors in unrelated places.
That is, **don't do this**::

    // DON'T DO THIS! THE SEMICOLON SHOULDN'T BE THERE!
    #define NAME value;

Similarly, including an equal sign after the ``#define`` line will
also generate a cryptic compiler error further down the page.  That
is, **don't do this, either**::

    // DON'T DO THIS, EITHER! THE EQUALS SIGN SHOULDN'T BE THERE!
    #define NAME = value

Example
-------

 ::

    #define LED_PIN 13
    // The compiler will replace any mention of LED_PIN with
    // the value 3 at compile time.

See Also
--------
-  :ref:`const <lang-const>`

.. include:: /arduino-cc-attribution.txt

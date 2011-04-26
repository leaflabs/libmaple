.. highlight:: cpp

.. _lang-string:

Strings
=======

Text strings can be represented in two ways.  You can

1. Use the :ref:`String <lang-stringclass>` data type, which is
part of the core as of version 0.0.9, or

2. You can make a string out of an array of type :ref:`char
<lang-char>` and null-terminate it.

This page describes the second method.

Examples
--------

All of the following are valid declarations for strings::

      char str1[15];
      char str2[6] = {'m', 'a', 'p', 'l', 'e'};
      char str3[6] = {'m', 'a', 'p', 'l', 'e', '\0'};
      char str4[ ] = "maple";
      char str5[6] = "maple";
      char str6[15] = "maple";

As you can see, there are several methods available for declaring and
initializing strings:

- Declare an array of ``char`` without initializing it, as with ``str1``.

- Declare an array of ``char`` (with one extra ``char``) and the
  compiler will add the required null character, as with ``str2``.

- Explicitly add the null character (``'\0'``), as with ``str3``.

- Initialize with a string constant in quotation marks (``"..."``);
  the compiler will size the array to fit the string constant and a
  terminating null character (``str4``).

- Initialize the array with an explicit size and string constant,
  (``str5``).

- Initialize the array, leaving extra space for a larger string
  (``str6``).

Null Termination
----------------

Generally, strings are terminated with a null character (`ASCII
<http://en.wikipedia.org/wiki/ASCII>`_ code 0). This allows functions
(like ``SerialUSB.print()``) to tell where the end of a string is.
Otherwise, they would continue reading subsequent bytes of memory that
aren't actually part of the string.

This means that your string needs to have space for one more character
than the text you want it to contain. That is why ``str2`` and
``str5`` need to be six characters, even though "maple" is only five
-- the last position is automatically filled with a NULL
character. ``str4`` will be automatically sized to six characters, one
for the extra null. In the case of ``str3``, we've explicitly included
the null character (written ``'\0'``) ourselves.

Note that it's possible to have a string without a final null
character (e.g. if you had specified the length of ``str2`` as five
instead of six). This will break most functions that use strings, so
you shouldn't do it intentionally. If you notice something behaving
strangely (operating on characters not in the string), however, this
could be the problem.

Single quotes or double quotes?
-------------------------------

Strings are always defined inside double quotes (``"Abc"``) and
characters are always defined inside single quotes (``'A'``).

Wrapping long strings
---------------------

You can wrap long strings like this::

    char myString[] = "This is the first line"
                      " this is the second line"
                      " etcetera";

Arrays of Strings
-----------------

It is often convenient, when working with large amounts of text,
such as a project with an LCD display, to setup an array of
strings. Because strings themselves are arrays, this is in actually
an example of a two-dimensional array.

In the code below, the asterisk after the datatype char ``char *``
indicates that this is an array of "pointers". All array names are
actually pointers, so this is required to make an array of arrays.
Pointers are one of the more esoteric parts of C for beginners to
understand, but it isn't necessary to understand pointers in detail to
use them effectively here::

    char* myStrings[] = {"This is string 1", "This is string 2",
                         "This is string 3", "This is string 4",
                         "This is string 5", "This is string 6"};

    void setup() {
        SerialUSB.begin();
    }

    void loop() {
        for (int i = 0; i < 6; i++) {
            SerialUSB.println(myStrings[i]);
            delay(500);
        }
    }


See Also
--------

- :ref:`array <lang-array>`
- :ref:`__attribute__ <arm-gcc-attribute-flash>`
- :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt

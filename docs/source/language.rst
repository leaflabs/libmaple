.. highlight:: c++

.. _language:

==========================
 Maple Language Reference
==========================

The Maple can be programmed in the `Wiring
<http://www.wiring.org.co/reference/>`_ language, which is the same
language used to program the `Arduino <http://arduino.cc/>`_ boards.
Please see the extensive `language reference
<http://arduino.cc/en/Reference/HomePage>`_ on the Arduino webpage for
more information, or follow a direct link below.

.. warning::

   The Arduino boards have different sizes for data types, so don't
   trust their documentation for how many bytes an ``int``, ``long``,
   etc. take up.  The sizes of each data type on the Maple are given
   in the :ref:`table below <language-arduino-docs>`.

C or C++ programmers curious about the differences between the Wiring
language and C++ may wish to skip to the
:ref:`arduino_c_for_c_hackers`.

.. contents:: Contents
   :local:

Unique Maple Additions
----------------------

.. _language-assert:

``ASSERT(...)``
    The ``ASSERT()`` function can be very useful for basic program
    debugging. The function accepts a boolean; for example::

      ASSERT(state == WAIT);

    zero is false and any other number is true. If the boolean is true
    the assertion passes and the program continues as usual. If it is
    false, the assertion fails: the program is halted, debug
    information is printed to USART2, and the status LED begins to
    throb in intensity (it's noticeably different from blinking). The
    debug information is printed at 9600 baud and consists of the
    filename and line number where the particular assertion failed.

    Including assertions in a program increases the program size. When
    using libmaple **from the command line only**, they can be
    disabled by making the definition ::

      #define DEBUG_LEVEL DEBUG_NONE

    before including either wirish or libmaple. In this case, all
    assertions will pass without any lost clock cycles.  Note that
    this will **not work in the IDE**; even with this definition,
    assertions will still be enabled.

.. _language-arduino-docs:

Arduino Documentation Links
---------------------------

(This table was copied from http://arduino.cc/en/Reference/Extended).

+------------------------------------+------------------------------------+-----------------------------------------+
| Structure                          | Variables                          | Functions                               |
|                                    |                                    |                                         |
+====================================+====================================+=========================================+
|                                    |**Constants**                       |**Digital I/O**                          |
|* `setup()`_                        |                                    |                                         |
|                                    |* `HIGH`_ | `LOW`_                  |* `pinMode()`_                           |
|* `loop()`_                         |                                    |                                         |
|                                    |* `INPUT`_ | `OUTPUT`_              |* `digitalWrite()`_                      |
|                                    |                                    |                                         |
|**Control Structures**              |* `true`_ | `false`_                |* `digitalRead()`_                       |
|                                    |                                    |                                         |
|* `if`_                             |* `integer constants`_              |                                         |
|                                    |                                    |**Analog I/O**                           |
|* `if...else`_                      |* `floating point constants`_       |                                         |
|                                    |                                    |* `analogReference()`_                   |
|* `for`_                            |                                    |                                         |
|                                    |**Data Types**                      |* `analogRead()`_                        |
|* `switch/case`_                    |                                    |                                         |
|                                    |Primitive data types on the Maple   |* `analogWrite()`_ - PWM                 |
|* `while`_                          |have different sizes than on the    |                                         |
|                                    |Arduino, since the Maple has a full |                                         |
|* `do...while`_                     |32-bit processor.  The size of each |**Advanced I/O**                         |
|                                    |such type on the Maple is given     |                                         |
|* `break`_                          |below.                              |* `tone()`_                              |
|                                    |                                    |                                         |
|* `continue`_                       |The ``word`` type is (deliberately) |* `noTone()`_                            |
|                                    |:ref:`not supported                 |                                         |
|* `return`_                         |<language-no-word>`.                |* `shiftOut()`_                          |
|                                    |                                    |                                         |
|* `goto`_                           |* `void`_                           |* `pulseIn()`_                           |
|                                    |                                    |                                         |
|                                    |* `boolean`_ (1 byte)               |                                         |
|**Further syntax**                  |                                    |**Time**                                 |
|                                    |* `char`_ (1 byte)                  |                                         |
|* `;`_ (semicolon)                  |                                    |* `millis()`_                            |
|                                    |* `unsigned char`_ (1 byte)         |                                         |
|* `{}`_ (curly braces)              |                                    |* `micros()`_                            |
|                                    |* `byte`_ (1 byte)                  |                                         |
|* `//`_ (single line comment)       |                                    |* `delay()`_                             |
|                                    |* `int`_ (4 bytes)                  |                                         |
|* `/\* \*/`_ (multi-line comment)   |                                    |* `delayMicroseconds()`_                 |
|                                    |* `unsigned int`_ (4 bytes)         |                                         |
|* `#define`_                        |                                    |                                         |
|                                    |* `long`_ (8 bytes)                 |**Math**                                 |
|* `#include`_                       |                                    |                                         |
|                                    |* `unsigned long`_ (8 bytes)        |* `min()`_                               |
|                                    |                                    |                                         |
|**Arithmetic Operators**            |* `float`_ (4 bytes)                |* `max()`_                               |
|                                    |                                    |                                         |
|* `=`_ (assignment operator)        |* `double`_ (8 bytes)               |* `abs()`_                               |
|                                    |                                    |                                         |
|* `+`_ (addition)                   |* `string`_                         |* `constrain()`_                         |
|                                    |                                    |                                         |
|* `-`_ (subtraction)                |* `array`_                          |* `map()`_                               |
|                                    |                                    |                                         |
|* `*`_ (multiplication)             |                                    |* `pow()`_                               |
|                                    |**Conversion**                      |                                         |
|* `/`_ (division)                   |                                    |* `sqrt()`_                              |
|                                    |* `char()`_                         |                                         |
|* `%`_ (modulo)                     |                                    |                                         |
|                                    |* `byte()`_                         |**Trigonometry**                         |
|                                    |                                    |                                         |
|**Comparison Operators**            |* `int()`_                          |* `sin()`_                               |
|                                    |                                    |                                         |
|* `==`_ (equal to)                  |* `word()`_                         |* `cos()`_                               |
|                                    |                                    |                                         |
|* `!=`_ (not equal to)              |* `long()`_                         |* `tan()`_                               |
|                                    |                                    |                                         |
|* `<`_ (less than)                  |* `float()`_                        |                                         |
|                                    |                                    |**Random Numbers**                       |
|* `>`_ (greater than)               |                                    |                                         |
|                                    |**Variable Scope & Qualifiers**     |* `randomSeed()`_                        |
|* `<=`_ (less than or equal to)     |                                    |                                         |
|                                    |* `variable scope`_                 |* `random()`_                            |
|* `>=`_ (greater than or equal to)  |                                    |                                         |
|                                    |* `static`_                         |                                         |
|                                    |                                    |**Bits and Bytes**                       |
|**Boolean Operators**               |* `volatile`_                       |                                         |
|                                    |                                    |* `lowByte()`_                           |
|* `&&`_ (and)                       |* `const`_                          |                                         |
|                                    |                                    |* `highByte()`_                          |
|* `||`_ (or)                        |                                    |                                         |
|                                    |**Utilities**                       |* `bitRead()`_                           |
|* `!`_ (not)                        |                                    |                                         |
|                                    |* `sizeof()`_ (sizeof operator)     |* `bitWrite()`_                          |
|                                    |                                    |                                         |
|**Pointer Access Operators**        |                                    |* `bitSet()`_                            |
|                                    |                                    |                                         |
|* `* dereference operator`_         |                                    |* `bitClear()`_                          |
|                                    |                                    |                                         |
|* `& reference operator`_           |                                    |* `bit()`_                               |
|                                    |                                    |                                         |
|                                    |                                    |                                         |
|**Bitwise Operators**               |                                    |**External Interrupts**                  |
|                                    |                                    |                                         |
|* `&`_ (bitwise and)                |                                    |For more information on external         |
|                                    |                                    |interrupts on Maple, see                 |
|* `|`_ (bitwise or)                 |                                    |`our reference page`_.                   |
|                                    |                                    |                                         |
|* `^`_ (bitwise xor)                |                                    |                                         |
|                                    |                                    |* `attachInterrupt()`_                   |
|* `~`_ (bitwise not)                |                                    |                                         |
|                                    |                                    |* `detachInterrupt()`_                   |
|* `<<`_ (shift left)                |                                    |                                         |
|                                    |                                    |                                         |
|* `>>`_ (shift right)               |                                    |**Interrupts**                           |
|                                    |                                    |                                         |
|                                    |                                    |* `interrupts()`_                        |
|**Compound Operators**              |                                    |                                         |
|                                    |                                    |* `noInterrupts()`_                      |
|* `++`_ (increment)                 |                                    |                                         |
|                                    |                                    |                                         |
|* `- -`_ (decrement)                |                                    |**Communication**                        |
|                                    |                                    |                                         |
|* `+=`_ (compound addition)         |                                    |* `Serial`_                              |
|                                    |                                    |                                         |
|* `-=`_ (compound subtraction)      |                                    |**Looking for something else?**          |
|                                    |                                    |                                         |
|* `*=`_ (compound multiplication)   |                                    |See the :ref:`libraries` page for        |
|                                    |                                    |interfacing with particular types of     |
|* `/=`_ (compound division)         |                                    |hardware. Try the list of                |
|                                    |                                    |`community-contributed code`_.  Maple    |
|* `&=`_ (compound bitwise and)      |                                    |links against `newlib`_ and allows the   |
|                                    |                                    |use of any of its functions; see its     |
|* `|=`_ (compound bitwise or)       |                                    |documentation for more details.          |
|                                    |                                    |                                         |
+------------------------------------+------------------------------------+-----------------------------------------+

.. _language-no-word:

.. note::

   The ``word`` data type is not supported on the Maple.  This is by
   choice.

   We decided not to include it because, while the Maple has 32-bit
   words, the word size on an Arduino board is only 16 bits, and code
   that uses the ``word`` type is likely to rely on that fact.

   By not supporting ``word``, you'll get a compile error when porting
   Arduino code to your Maple instead of potentially weird,
   hard-to-debug runtime behavior.

   If you're porting over Arduino code and really want ``word``, you
   can put the following at the top of the file you're porting::

     typedef uint16 word;
   
.. _if: http://arduino.cc/en/Reference/If
.. _if...else: http://arduino.cc/en/Reference/Else
.. _for: http://arduino.cc/en/Reference/For
.. _switch/case: http://arduino.cc/en/Reference/SwitchCase
.. _while: http://arduino.cc/en/Reference/While
.. _do...while: http://arduino.cc/en/Reference/DoWhile
.. _break: http://arduino.cc/en/Reference/Break
.. _continue: http://arduino.cc/en/Reference/Continue
.. _return: http://arduino.cc/en/Reference/Return
.. _goto: http://arduino.cc/en/Reference/Goto

.. _;: http://arduino.cc/en/Reference/SemiColon
.. _{}: http://arduino.cc/en/Reference/Braces
.. _//: http://arduino.cc/en/Reference/Comments
.. _/\* \*/: http://arduino.cc/en/Reference/Comments
.. _#define: http://arduino.cc/en/Reference/Define
.. _#include: http://arduino.cc/en/Reference/Include

.. _=: http://arduino.cc/en/Reference/Assignment
.. _+: http://arduino.cc/en/Reference/Arithmetic
.. _-: http://arduino.cc/en/Reference/Arithmetic
.. _*: http://arduino.cc/en/Reference/Arithmetic
.. _/: http://arduino.cc/en/Reference/Arithmetic
.. _%: http://arduino.cc/en/Reference/Modulo

.. _==: http://arduino.cc/en/Reference/If
.. _!=: http://arduino.cc/en/Reference/If
.. _<: http://arduino.cc/en/Reference/If
.. _>: http://arduino.cc/en/Reference/If
.. _<=: http://arduino.cc/en/Reference/If
.. _>=: http://arduino.cc/en/Reference/If

.. _&&: http://arduino.cc/en/Reference/Boolean
.. _||: http://arduino.cc/en/Reference/Boolean
.. _!: http://arduino.cc/en/Reference/Boolean

.. _* dereference operator: http://arduino.cc/en/Reference/Pointer
.. _& reference operator: http://arduino.cc/en/Reference/Pointer

.. _&: http://arduino.cc/en/Reference/BitwiseAnd
.. _|: http://arduino.cc/en/Reference/BitwiseAnd
.. _^: http://arduino.cc/en/Reference/BitwiseAnd
.. _~: http://arduino.cc/en/Reference/BitwiseXorNot
.. _<<: http://arduino.cc/en/Reference/Bitshift
.. _>>: http://arduino.cc/en/Reference/Bitshift

.. _++: http://arduino.cc/en/Reference/Increment
.. FIXME can't freaking get two hyphens to show up! sphinx turns "--"
.. into an endash, whatever, fine, try to escape like "\-\-", that
.. ALSO becomes endash (!@#$), damn, well, maybe someone else is
.. eating my slash, try "\\-\\-", nope, that turns into a motherfing
.. \-\-. i hate everything.
.. _- -: http://arduino.cc/en/Reference/Increment
.. _+=: http://arduino.cc/en/Reference/IncrementCompound
.. _-=: http://arduino.cc/en/Reference/IncrementCompound
.. _*=: http://arduino.cc/en/Reference/IncrementCompound
.. _/=: http://arduino.cc/en/Reference/IncrementCompound
.. _&=: http://arduino.cc/en/Reference/BitwiseCompound
.. _|=: http://arduino.cc/en/Reference/BitwiseCompound

.. _HIGH: http://arduino.cc/en/Reference/Constants
.. _LOW: http://arduino.cc/en/Reference/Constants
.. _INPUT: http://arduino.cc/en/Reference/Constants
.. _OUTPUT: http://arduino.cc/en/Reference/Constants
.. _true: http://arduino.cc/en/Reference/Constants
.. _false: http://arduino.cc/en/Reference/Constants
.. _integer constants: http://arduino.cc/en/Reference/IntegerConstants
.. _floating point constants: http://arduino.cc/en/Reference/Fpconstants

.. _void: http://arduino.cc/en/Reference/Void
.. _boolean: http://arduino.cc/en/Reference/BooleanVariables
.. _char: http://arduino.cc/en/Reference/Char
.. _unsigned char: http://arduino.cc/en/Reference/UnsignedChar
.. _byte: http://arduino.cc/en/Reference/Byte
.. _int: http://arduino.cc/en/Reference/Int
.. _unsigned int: http://arduino.cc/en/Reference/UnsignedInt
.. _word: http://arduino.cc/en/Reference/Word
.. _long: http://arduino.cc/en/Reference/Long
.. _unsigned long: http://arduino.cc/en/Reference/UnsignedLong
.. _float: http://arduino.cc/en/Reference/Float
.. _double: http://arduino.cc/en/Reference/Double
.. _string: http://arduino.cc/en/Reference/String
.. _array: http://arduino.cc/en/Reference/Array

.. _char(): http://arduino.cc/en/Reference/CharCast
.. _byte(): http://arduino.cc/en/Reference/ByteCast
.. _int(): http://arduino.cc/en/Reference/IntCast
.. _word(): http://arduino.cc/en/Reference/WordCast
.. _long(): http://arduino.cc/en/Reference/LongCast
.. _float(): http://arduino.cc/en/Reference/FloatCast

.. _variable scope: http://arduino.cc/en/Reference/Scope
.. _static: http://arduino.cc/en/Reference/Static
.. _volatile: http://arduino.cc/en/Reference/Volatile
.. _const: http://arduino.cc/en/Reference/Const
.. _sizeof(): http://arduino.cc/en/Reference/Sizeof

.. Links for the standard Arduino built-in functions are included as
.. part of the standard epilog.
.. _our reference page: http://leaflabs.com/docs/external-interrupts/

.. _Serial: http://arduino.cc/en/Reference/Serial
.. _community-contributed code: http://www.arduino.cc/playground/Main/GeneralCodeLibrary
.. _newlib: http://sourceware.org/newlib/


.. _arduino_c_for_c_hackers:

Note for C/C++ Programmers
--------------------------

This is a note for programmers comfortable with C or C++ (although,
you C programmers should remember that `C++ is not a superset of C
<http://en.wikipedia.org/wiki/Compatibility_of_C_and_C%2B%2B>`_) who
want a better understanding of the differences between C++ and the
Wiring language.  The good news is that the differences are relatively
few.

A *sketch* is the IDE's notion of a project; it consists of one or
more files written in the Wiring language, which is mostly the same as
C++.  The major difference between the two is that in Wiring, it's not
necessary to declare global functions before they are used.  That is,
the following is valid Wiring, and ``f()`` returns ``5``::

  int f() {
    return g();
  }

  int g() {
    return 5;
  }

All of the files in a sketch share the same (global) namespace.  That
is, the behavior is as if all of a sketch's files were part of the
same translation unit, so they don't have to include one another in
order to access each other's definitions.  The only other major
difference between Wiring and C++ is that Wiring doesn't support
dynamically allocated memory -- that is, ``new`` and ``delete`` won't
work.  As of |today|, Maple only has 20 KB RAM, anyway, so it's
doubtful that static allocation is not what you want.

The Wiring language also does not require you to define your own
``main`` method (in fact, it forbids you from doing so).  Instead, you
are required to define two functions, ``setup`` and ``loop``, with
type signatures ::

  void setup(void)
  void loop(void)

Once a sketch is uploaded to a Maple and begins to run, ``setup()`` is
called once, and then ``loop()`` is called repeatedly.  The IDE
compilation process proceeds via a source-to-source translation from
the files in a sketch to C++.

This translation process first concatenates the sketch files, then
parses the result to produce a list of all functions defined in the
global scope.  (We borrow this stage from the Arduino IDE, which in
turn borrows it from Wiring.  It uses regular expressions to parse
C++, which is, of course, `Bad and Wrong
<http://www.retrologic.com/jargon/B/Bad-and-Wrong.html>`_.  An
upcoming rewrite of the IDE performs this preprocessing step
correctly, using a real parser.  Until then, you have our apologies.)
The order in which the individual sketch files are concatenated is not
defined; it is unwise to write code that depends on a particular
ordering.

The concatenated sketch files are then appended onto a file which
includes `WProgram.h
<http://github.com/leaflabs/libmaple/blob/master/wirish/WProgram.h>`_
(which includes the wirish and libmaple libraries, and declares
``setup()`` and ``loop()``), and then provides declarations for all
the function definitions found in the previous step.  At this point,
we have a file that is a valid C++ translation unit, but lacks a
``main()`` method.  The final step of compilation provides this
method, which behaves roughly like::

  int main(void) {
    setup();
    while (true) loop();
  }

(The truth is a little bit more complicated, but not by much).  

As an example, consider a sketch with two files.  The first file
contains ``setup()`` and ``loop()``::

  int the_pin;

  void setup() {
    the_pin = choose_a_pin();
    pinMode(the_pin, OUTPUT);
  }

  void loop() {
    static int toggle = 0;
    toggle ^= 1;
    digitalWrite(the_pin, toggle);
  }

The second file contains the (not very useful) implementation for
``choose_a_pin()``::

  int choose_a_pin() {
     return random(5, 15);
  }

Then the results of the concatenation process might be ::

  int the_pin;

  void setup() {
    the_pin = choose_a_pin();
    pinMode(the_pin, OUTPUT);
  }

  void loop() {
    static int toggle = 0;
    toggle ^= 1;
    digitalWrite(the_pin, toggle);
  }

  int choose_a_pin(void);

  int choose_a_pin() {
     return random(5, 15);
  }

Which could plausibly be turned into the final source file ::

  #include "WProgram.h"

  void setup(void);
  void loop(void);
  int choose_a_pin(void);

  int the_pin;

  void setup() {
    the_pin = choose_a_pin();
    pinMode(the_pin, OUTPUT);
  }

  void loop() {
    static int toggle = 0;
    toggle ^= 1;
    digitalWrite(the_pin, toggle);
  }

  int choose_a_pin(void);

  int choose_a_pin() {
     return random(5, 15);
  }

  int main() {
    setup();
    while (true) loop();
  }

(Recall that it's legal C++ for a function to be declared multiple
times, as long as it's defined exactly once).


Recommended Reading
-------------------

* `newlib Documentation <http://sourceware.org/newlib/>`_
* STMicro documentation for STM32F103RB microcontroller:

    * `All documents <http://www.st.com/mcu/devicedocs-STM32F103RB-110.html>`_
    * `Datasheet <http://www.st.com/stonline/products/literature/ds/13587.pdf>`_ (pdf)
    * `Reference Manual <http://www.st.com/stonline/products/literature/rm/13902.pdf>`_ (pdf)
    * `Programming Manual <http://www.st.com/stonline/products/literature/pm/15491.pdf>`_ (assembly language and register reference)

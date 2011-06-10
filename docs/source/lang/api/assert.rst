.. highlight:: cpp

.. _lang-assert:

``ASSERT(...)``
===============

ASSERT() can be very useful for basic program debugging. It accepts a
boolean; for example::

  ASSERT(state == WAIT);

Zero is false and any other number is true.  If the boolean is true,
the assertion passes and the program continues as usual.  If it is
false, the assertion fails: the program is halted, debug information
is printed to USART2, and the status LED begins to throb (it's
noticeably different from blinking). The debug information is printed
at 9600 baud and consists of the filename and line number where the
ASSERT() failed.

Including assertions in a program increases the program size. When
using libmaple **from the command line only**, they can be disabled by
making the definition ::

  #define DEBUG_LEVEL DEBUG_NONE

before including either wirish.h or libmaple.h. In this case, all
assertions will pass without any lost clock cycles.  Note that this
will **not work in the IDE**; even with this definition, assertions
will still be enabled.

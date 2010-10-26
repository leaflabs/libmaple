.. highlight:: cpp

.. _arduino-long:

long
====

Description
-----------

The ``long`` data type stores extended size integer values.  You can
use a ``long`` when your values are too large to fit into an :ref:`int
<arduino-int>`.  A ``long`` occupies 8 bytes of memory.  This yields a
range of approximately -9.2×10^18 to 9.2×10^18 (that's 9.2 billion
billion, or about 92 million times the number of stars in the Milky
Way galaxy).  The exact range of a ``long`` on the Maple is from
-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807, or -2^63 to
(2^63-1).

Here's an example of declaring a long (see :ref:`integer constants
<arduino-constants-u-l>` for explanation of the 'L')::

        // Speed of light in nanometers per second (approximate).
        long c = 299792458000000000L;

The general syntax for declaring an ``long`` variable named ``var``,
then giving it value ``val``, looks like::

    long var = val;

This is identical to the ``int`` syntax, with ``long`` replacing
``int``.

Note that ``long`` values will still :ref:`overflow
<arduino-int-overflow>`, just like ``int`` values, but their much
larger range makes this less likely to happen.

The downside to using a ``long`` instead of an ``int`` (besides the
extra storage) is that :ref:`arithmetic <arduino-arithmetic>`
operations on ``long``\ s will take longer than on ``int``\ s.

See Also
--------

-  :ref:`char <arduino-char>`
-  :ref:`unsigned char <arduino-unsignedchar>`
-  :ref:`int <arduino-int>`
-  :ref:`unsigned int <arduino-unsignedint>`
-  :ref:`unsigned long <arduino-unsignedlong>`
-  :ref:`Integer Constants <arduino-constants-integers>`
-  :ref:`Variables <arduino-variables>`


.. highlight:: cpp

.. _lang-long:

``long``
========

The ``long`` data type stores extended size integer values.  You can
use a ``long`` when your values are too large to fit into an :ref:`int
<lang-int>`.  A ``long`` occupies 8 bytes of memory.  This yields a
range of approximately -9.2×10^18 to 9.2×10^18 (that's 9.2 billion
billion, or about 92 million times the number of stars in the Milky
Way galaxy).  The exact range of a ``long`` on the Maple is from
-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807, or -2^63 to
(2^63-1).  A ``long`` it is subject to the same :ref:`overflow issues
<lang-variables-rollover>` as any numeric data type.

Here's an example of declaring a long (see :ref:`integer constants
<lang-constants-integers-u-l>` for an explanation of the "L" at the end of the
number)::

        // Speed of light in nanometers per second (approximate).
        long c = 299792458000000000L;

The general syntax for declaring an ``long`` variable named ``var``,
then giving it value ``val``, looks like::

    long var = val;

This is identical to the ``int`` syntax, with ``long`` replacing
``int``.

Note that ``long`` values will still :ref:`overflow
<lang-int-overflow>`, just like ``int`` values, but their much
larger range makes this less likely to happen.

The downside to using a ``long`` instead of an ``int`` (besides the
extra storage) is that :ref:`arithmetic <lang-arithmetic>` operations
on ``long``\ s will take slightly longer than on ``int``\ s.

See Also
--------

-  :ref:`char <lang-char>`
-  :ref:`unsigned char <lang-unsignedchar>`
-  :ref:`int <lang-int>`
-  :ref:`unsigned int <lang-unsignedint>`
-  :ref:`unsigned long <lang-unsignedlong>`
-  :ref:`Integer Constants <lang-constants-integers>`
-  :ref:`Variables <lang-variables>`

.. include:: cc-attribution.txt

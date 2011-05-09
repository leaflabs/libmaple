.. highlight:: cpp

.. _lang-longlong:

``long long``
=============

The ``long long`` data type stores extended size integer values.  You
can use a ``long long`` when your values are too large to fit into an
:ref:`int <lang-int>`.  A ``long long`` occupies 8 bytes of memory.
This yields a range of approximately -9.2×10^18 to 9.2×10^18 (that's
9.2 billion billion, or about 92 million times the number of stars in
the Milky Way galaxy).  The exact range of a ``long long`` on the
Maple is from -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807,
or -2^63 to (2^63-1).  A ``long long`` it is subject to the same
:ref:`overflow issues <lang-variables-rollover>` as any numeric data
type.

A synonym for the ``long long`` type is ``int64``.

Here's an example of declaring a long long (see :ref:`integer
constants <lang-constants-integers-u-l>` for an explanation of the
"LL" at the end of the number)::

        // Speed of light in nanometers per second (approximate).
        long long c = 299792458000000000LL;

The general syntax for declaring an ``long long`` variable named ``var``,
then giving it value ``val``, looks like::

    long long var = val;

This is identical to the ``int`` syntax, with ``long long`` (or, at
your option, ``int64``) replacing ``int``.

Note that ``long long`` values will still :ref:`overflow
<lang-int-overflow>`, just like ``int`` values, but their much larger
range makes this less likely to happen.

The downside to using a ``long long`` instead of an ``int`` (besides
the extra storage) is that :ref:`arithmetic <lang-arithmetic>`
operations on ``long long``\ s will take slightly longer than on
``int``\ s.

See Also
--------

-  :ref:`char <lang-char>`
-  :ref:`unsigned char <lang-unsignedchar>`
-  :ref:`int <lang-int>`
-  :ref:`unsigned int <lang-unsignedint>`
-  :ref:`unsigned long long <lang-unsignedlonglong>`
-  :ref:`Integer Constants <lang-constants-integers>`
-  :ref:`Variables <lang-variables>`

.. include:: /arduino-cc-attribution.txt

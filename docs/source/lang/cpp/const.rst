.. highlight:: cpp

.. _lang-const:

``const``
=========

The ``const`` keyword stands for "constant". It is a variable
*qualifier* that modifies the behavior of the variable, making a
variable "*read-only*". This means that the variable can be used just
as any other variable of its type, but its value cannot be
changed. You will get a compiler error if you try to assign a value to
a ``const`` variable.

Constants defined with the ``const`` keyword obey the same rules of
:ref:`variable scoping <lang-scope>` that govern other
variables. This, and the pitfalls of using :ref:`#define
<lang-define>`, often makes using the ``const`` keyword a superior
method for defining constants than ``#define``.

Example
-------

 ::

    // this defines a variable called "pi", which cannot be changed:
    const float pi = 3.14;
    float x;

    // ....

    x = pi * 2;    // it's fine to find the value of a const variable

    pi = 7;        // illegal - you can't write to (modify) a constant

**#define** or **const**
------------------------

You can use either ``const`` or ``#define`` for creating numeric or
string constants. For :ref:`arrays <lang-array>`\ , you will need
to use ``const``. In general, ``const`` is preferred over ``#define``
for defining constants.

See Also
--------

-  :ref:`#define <lang-define>`
-  :ref:`volatile <lang-volatile>`

.. include:: /arduino-cc-attribution.txt

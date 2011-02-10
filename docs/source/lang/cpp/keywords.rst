.. _lang-keywords:

Keywords
========

This page lists all of the C++ keywords, and either links to a
reference page explaining their use, or provides a brief description.

List of Keywords
----------------

The C++ keywords are:

``and``, ``and_eq``, ``asm``, ``auto``, ``bitand``, ``bitor``,
``bool``, ``break``, ``case``, ``catch``, ``char``, ``class``,
``compl``, ``const``, ``const_cast``, ``continue``, ``default``,
``delete``, ``do``, ``double``, ``dynamic_cast``, ``else``, ``enum``,
``explicit``, ``export``, ``extern``, ``false``, ``float``, ``for``,
``friend``, ``goto``, ``if``, ``inline``, ``int``, ``long``,
``mutable``, ``namespace``, ``new``, ``not``, ``not_eq``,
``operator``, ``or``, ``or_eq``, ``private``, ``protected``,
``public``, ``register``, ``reinterpret_cast``, ``return``, ``short``,
``signed``, ``sizeof``, ``static``, ``static_cast``, ``struct``,
``switch``, ``template``, ``this``, ``throw``, ``true``, ``try``,
``typedef``, ``typeid``, ``typename``, ``union``, ``unsigned``,
``using``, ``virtual``, ``void``, ``volatile``, ``wchar_t``,
``while``, ``xor``, ``xor_eq``

Boolean Operator Synonyms
-------------------------

- ``and`` is a synonym for :ref:`&& <lang-boolean-and>`.
- ``not`` is a synonym for :ref:`\! <lang-boolean-not>`.
- ``not_eq`` is a synonym for :ref:`\!= <lang-comparison>`.
- ``or`` is a synonym for :ref:`|| <lang-boolean-or>`.

Bitwise Operator Synonyms
-------------------------

- ``and_eq`` is a synonym for :ref:`&= <lang-compoundbitwise-and>`.
- ``bitand`` is a synonym for (bitwise) :ref:`& <lang-bitwisemath-and>`.
- ``bitor`` is a synonym for :ref:`\| <lang-bitwisemath-or>`.
- ``compl`` is a synonym for :ref:`~ <lang-bitwisemath-not>`.
- ``or_eq`` is a synonym for :ref:`|= <lang-compoundbitwise-or>`.
- ``xor`` is a synonym for :ref:`^ <lang-bitwisemath-xor>`.
- ``xor_eq`` is a synonym for :ref:`^= <lang-compoundbitwise-xor>`.

Constants
---------

- ``true`` and ``false`` are the :ref:`boolean constants
  <lang-booleanvariables>`.

Control Flow
------------

- ``break`` can exit out of a :ref:`switch statement
  <lang-switchcase>` or a :ref:`for <lang-for>`, :ref:`do
  <lang-dowhile>`, or :ref:`while <lang-while>` loop.

- ``case`` defines alternatives in a :ref:`switch statement <lang-switchcase>`.

- ``continue`` will move control flow to the next iteration of the
  enclosing :ref:`for <lang-for>`, :ref:`do <lang-dowhile>`, or
  :ref:`while <lang-while>` loop.

- ``default`` defines the default alternative in a :ref:`switch
  statement <lang-switchcase>`.

- ``do`` introduces a :ref:`do <lang-dowhile>` loop.

- ``else`` is used in :ref:`if statements <lang-if>`.

- ``for`` introduces a :ref:`for <lang-for>` loop.

- ``goto`` :ref:`jumps <lang-goto>` to a label.

- ``if`` introduces an :ref:`if statement <lang-if>`.

- ``return`` :ref:`transfers flow to a function's caller <lang-return>`.

- ``switch`` introduces a :ref:`switch statement <lang-switchcase>`.

- ``while`` introduces a :ref:`while <lang-while>` loop.

Types
-----

The following keywords are used for built-in types.

- :ref:`bool <lang-booleanvariables>`
- :ref:`char <lang-char>`
- :ref:`double <lang-double>`
- :ref:`float <lang-float>`
- :ref:`int <lang-int>`
- :ref:`long <lang-long>`
- :ref:`short <lang-built-in-types-integral>`
- :ref:`void <lang-void>` (not really a type, but used in the absence
  of one)

The following keywords are used to introduce new types.

- :ref:`enum <lang-enum>`

Qualifiers
----------

- :ref:`static <lang-static>` can be used to declare persistent local
  variables; it has other uses not documented here.

- ``unsigned`` is used to specify an unsigned integral type.
  Examples: :ref:`lang-unsignedint`, :ref:`lang-unsignedchar`.

- :ref:`volatile <lang-volatile>` is useful when declaring variables
  that may be modified by external interrupts.

- :ref:`const <lang-const>` is used to define constants.

Other
-----

These keywords are not described in the Maple documentation.  For more
information, consult a C++ reference.

- ``asm`` is used to insert literal assembly language.

- ``auto`` is used to declare that a variable has automatic storage.

- ``catch`` is used in exception handling.  Note that the default
  flags we pass to :ref:`GCC <arm-gcc>` include ``-fno-exceptions``.

- ``class`` is used to define classes.

- ``const_cast`` is used in typecasting.

- ``delete`` is used to free ``new``\ -allocated storage.  Note that
  dynamic memory allocation is not available by default on the Maple,
  so you'll have to bring your own ``new`` and ``delete`` if you want
  this.

- ``dynamic_cast`` is used in typecasting.

- ``explicit`` is used to declare constructors that can be called only
  explicitly.

- ``export`` declares a template definition accessible to other
  compilation units.

- ``extern`` can mark a declaration as a declaration and not a
  definition, and also grant external linkage to a ``const`` or
  ``typedef``.

- ``friend`` is used to declare that certain functions have access to
  a class's private variables.

- ``inline`` is a compiler hint to inline a function.

- ``mutable`` specifies that a member can be updated, even when a
  member of a ``const`` object.

- ``namespace`` declares a new namespace.

- ``new`` dynamically allocates space for a value.  Note that dynamic
  memory allocation is not available by default on the Maple, so
  you'll have to bring your own ``new`` and ``delete`` if you want
  this.

- ``operator`` is used to define type-specific operator overrides.

- ``private`` declares a private class member.

- ``protected`` declares a protected class member.

- ``public`` declares a public class member.

- ``register`` is a compiler hint to store a variable in a register.

- ``reinterpret_cast`` is used in typecasting.

- ``signed`` is the opposite of ``unsigned``.

- ``static_cast`` is used in typecasting.

- ``struct`` declares a new struct.

- ``template`` introduces a template class, function, etc.

- ``this`` is a pointer to the receiver object.

- ``throw`` is used in exception handling.  Note that the default
  flags we pass to :ref:`GCC <arm-gcc>` include ``-fno-exceptions``.

- ``try`` is used in exception handling.  Note that the default
  flags we pass to :ref:`GCC <arm-gcc>` include ``-fno-exceptions``.

- ``typedef`` defines a type synonym.

- ``union`` defines an untagged union.

- ``using`` is a directive related to namespaces.

- ``virtual`` declares a method which may be overridden.

- ``wchar_t`` is the wide character type.

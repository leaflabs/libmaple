.. _libmaple-coding-standard:

Coding Standard
===============

This page documents the coding standard for :ref:`libmaple`.  It's
intended as a guide for how you should structure any code you would
like included into the LeafLabs releases of libmaple.

LeafLabs team members are required to follow these when producing new
code.  Community contributors to libmaple are strongly encouraged to
do so; following these rules will greatly increase the probability
that your patches will be folded in.

In general, follow this guide unless there's a very good reason not
to.  Laziness doesn't count as a good reason.  Most, if not all, of
these decisions are entirely arbitrary, but it's important for
readability that we be consistent.  (If you notice an inconsistency,
you should fix it).

Note that the file ``.dir-locals.el`` in the libmaple root directory
already ensures that many of these standards are followed by default
in Emacs (but not on Windows, where it would need to be named
``_dir_locals.el``, and no way, man).  There's also some elisp
scattered about this file which will provide you additional help.

Vim customizations to do the same thing would be nice!

.. contents:: Contents
   :local:

License
-------

.. highlight:: scheme

Put an MIT license at the beginning of the file (look at any of our
source files for an example).  Copyright should go either to you or to
LeafLabs, LLC.

Emacs: if you don't like seeing the license, you should use elide-head
(which will hide it for you).  You can use the following::

    (require 'elide-head)
    (setq programming-mode-hooks '(c-mode-hook c++-mode-hook))
    (add-to-list 'elide-head-headers-to-hide
                 '("The MIT License" . "DEALINGS IN\n [*] THE SOFTWARE"))
    (add-to-list 'elide-head-headers-to-hide
                 '("The MIT License" . "DEALINGS IN THE\n...SOFTWARE"))
    (dolist (hook programming-mode-hooks)
      (add-hook hook (lambda () (elide-head))))

Whitespace
----------

- 4 space indents (set in ``.dir-locals.el``).

- Unix newlines. Some exceptions are currently grandfathered in; these
  will go away in time.

- No tab characters (set in ``.dir-locals.el``).

- No trailing whitespace.  For help getting this (and no tab
  characters) done automatically in Emacs, you can use
  `code-fascism.el <https://github.com/mbolivar/code-fascism>`_.

- Files end in exactly one newline. The presence of a newline at EOF
  is already done by ``c-require-final-newline`` in recent versions of
  Emacs.

- Exactly two newlines separate source paragraphs (you do separate
  your code into paragraphs, don't you?).

- The first line in a function is non-blank.

.. highlight:: cpp

- Exactly one space after ``if``, ``else``, ``for``, and ``while``,
  before the following ``{`` or ``(``.  One space before ``else``,
  after the preceding ``}``.  For example::

      // This is good; we like this:
      if (foo) {
          while (quux) {
              bar();
          }
      } else {
          baz();
      }

      // THIS IS BAD! DON'T DO THIS:
      if(foo){
          while(quux){
              bar();
          }
      }else{
          baz();
      }

- Exactly one space in between binary arithmetic, logical, and
  comparison operators and their operands.  Examples::

      // This is good:
      int x = a + b * (c - d);
      if (x != 0 && a > 7) {
          SerialUSB.println(x);
      }

      // THIS IS BAD!
      int x = a+b*(c-d);
      if (x!=0 && a>7) {
          SerialUSB.println(x);
      }

      // This is good:
      uint32 adc_data = ADC1_BASE->DR;
      SerialUSB.println(adc_data);

      // THIS IS BAD!
      uint32 adc_data = ADC1_BASE -> DR;
      SerialUSB . println(adc_data);

- No space between a unary operator and its operand.  Examples::

      // Good:
      x++;

      // BAD!
      x ++;

      // Good:
      y = -x;

      // BAD!
      y = - x;

- If you need to break up a long line:

  * Prefer to break up long expressions after a binary operator.  Example::

      // Good:
      if (some_really_long_conditional_wow_this_really_goes_on_forever ||
          maybe_something_else_could_happen_too) {
          ...
      }

      // BAD!
      if (some_really_long_conditional_wow_this_really_goes_on_forever
          || maybe_something_else_could_happen_too) {
          ...
      }

  * When breaking up a function's arguments over multiple lines, align
    the arguments on subsequent lines with the first argument.
    Example::

      // Good:
      return_type value_i_got = function_with_a_really_long_name(argument1,
                                                                 argument2,
                                                                 argument3);

      // BAD!
      return_type value_i_got = function_with_a_really_long_name(argument1,
          argument2,
          argument3);

      // BAD!
      return_type value_i_got = function_with_a_really_long_name(argument1,
                                                                    argument2,
                                                                    argument3);

- In function invocations, no space in between the function name and
  the opening parenthesis.  Example::

      // Good:
      SerialUSB.println("Hello, world!");

      // BAD!
      SerialUSB.println ("Hello, world!");

- Don't indent C code within a conditionally-compiled ``extern "C"``
  block.  Example::

      // Good:
      #ifdef __cplusplus
      extern "C"{
      #endif

      void some_c_function(void);

      #ifdef __cplusplus
      } // extern "C"
      #endif

      // BAD!
      #ifdef __cplusplus
      extern "C"{
      #endif

          void some_c_function(void);

      #ifdef __cplusplus
      } // extern "C"
      #endif

  Emacs does the "bad" behavior by default, which can be very
  annoying.  You can turn this off with ::

      (defun c-mode-inextern-lang-hook ()
          (setcdr (assq 'inextern-lang c-offsets-alist) '-))
      (add-hook 'c-mode-hook c-mode-inextern-lang-hook)

Comments
--------

.. highlight:: c++

- Multi-line comments are pretty flexible.  Any of these is fine::

    /* Comment starts here.
     * Continued lines have a '*' before them.
     * The comment can end after the last line.
     */

    /* Comment starts here.
     * The comment can end on the same line. */

    /*
     * You can also place a newline after the opening "/*".
     */

- Doxygen comments are multi-line comments that begin with ``/**``
  instead.

- Single-line comments are up to you.

Braces
------

- Mostly `1TBS
  <http://en.wikipedia.org/wiki/Indent_style#Variant:_1TBS>`_.  The
  only difference is that the opening brace of a function's definition
  occurs exactly one space character after the closing parenthesis in
  that function's parameter list.  Example::

      void func(void) {
          ...
      }

Naming conventions
------------------

We'll handle the usual casing/underscore debate as follows.

- First, ``Dont_Mix_Like_This``, because ``It_Looks_Really_Ugly``, ok?
  [There's been some debate about this, and some exceptions are
  already grandfathered in, so in order to settle it, let's call this
  a "recommendation" instead of "requirement".]

- Variables: Use underscores to separate words in C identifiers::

    int some_example_name;

  User-facing C++ variables should be camel cased
  (``thisIsAnExample``, ``boardPWMPins``, etc.), for consistency with
  the Arduino style.  It's probably a good idea for you to case
  non-user facing C++ variables in the C style; this will help
  disambiguate what's part of the Wirish API and what's not.

- Classes: Pascal case.  So ``ThisIsAClassName``, but ``thisIsNot``,
  ``this_is_not``, and ``Dont_You_DareTryANYTHING_STUPID``.

- Functions: C functions are all lowercase, and words are separated by
  underscores.  C++ method names are camel cased.

- Structs: Usually like variables (``adc_dev``, ``adc_reg_map``,
  etc.), but it's not crucial.  Don't feel obliged to put ``_t`` at
  the end of the type name; we don't.

- Macros and constants: all caps, separated by underscores.  C++
  variables with the ``const`` qualifier generally aren't considered
  "constants" for the purposes of this rule; i.e., they are cased
  according to the rules for variables.  We make an exception for
  ``PIN_MAP``, because it's the central Wirish data structure.

- foo.h gets ``#ifdef``\ 'ed to ``_FOO_H_``.

- Acronyms: The case of letters in an acronym is determined by the
  case of the first letter in the acronym, which is determined by
  following the above rules.  Examples::

      // Good:
      void usb_func() { ... }
      void frob_usb_disc() { ... }
      class SomethingUSB {
          void usbInit();
          void initUSB();
      };

      // BAD:
      class BadUsb { ... }; // say "GoodUSB" instead
      void swizzle_USB_disc() { ... } // say "swizzle_usb_disc" instead

Documentation
-------------

- Doxygen comments on every user-facing function and type.
  Additionally, individually document the fields and enumerator values
  of nontrivial user-facing structs and enums.  See any register map
  type's definition for an example.

- For libmaple proper, you don't need comments for each register bit
  definition, since that's just repeating information better obtained
  by reading ST RM0008.

- Doxygen comments generally only belong on types, functions,
  etc. that are part of the public user-facing API.  This generally
  means that if there's ReST documentation for it under libmaple's
  ``docs/source/``, it needs Doxygen comments, and that ReST should
  use Breathe to pull that Doxygen comment out. (For more information
  on this, see libmaple file ``docs/README``).

  There are some exceptions to this rule since Breathe isn't totally
  mature yet and Sphinx's C++ domain is still in flux.  In these
  cases, document the code "manually" in ReST.

  This should be avoided if at all possible, since it creates a
  maintenance burden of documenting things in two places at once, and
  makes it easier for documentation to go stale.

  If you do have to document something manually, put a comment in the
  source file informing future maintainers about it, so they'll pay
  extra attention when making changes.

- When adding peripheral support, it would be nice if you put
  longer-form comments into the libmaple ``notes/`` directory, with a
  comment in the corresponding .h file referring to it.  See the
  :ref:`dac.h <libmaple-dac>` source for an example.

  This lets us keep the source files relatively free of "introductory"
  material, while allowing new readers a convenient starting point.
  These longer-form notes also have a habit of turning into official,
  user-facing documentation.

- **For libmaple proper**, the convention is to document any
  user-facing function at the point where it is defined.  In
  particular, this means you should document an externally-linked
  function defined in a .c file in that .c file, not in the header
  file where it is declared to the user.

  **For Wirish**, the convention is to put the documentation in the
  header file where the function is declared.

General Formatting
------------------

.. highlight:: scheme

- Keep it 80-column clean.  

  Emacs users: this means that the largest column number is 79.  You
  should turn on column number mode to help you out::

    (column-number-mode 1)

  You can get more help from `lineker-mode
  <http://www.helsinki.fi/~sjpaavol/programs/lineker.el>`_.  Just put
  lineker.el somewhere in your load-path, and::

    (require 'lineker)
    (dolist (hook '(c-mode-hook c++-mode-hook))
      (add-hook hook (lambda () (lineker-mode 1))))

.. highlight:: cpp

Language Features
-----------------

In libmaple proper, aim for C99 compatibility.  Some GCC extensions
are OK, but `don't get crazy <http://www.youtube.com/watch?v=jZkdcYlOn5M>`_.

Explicitly approved GCC extensions:

  * `asm volatile <http://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html>`_

  * `Nested functions <http://gcc.gnu.org/onlinedocs/gcc/Nested-Functions.html>`_

In Wirish, generally be very conservative when using C++ features that
aren't part of C.  We are forced to use C++ for Arduino compatibility
(and the general Arduino style of conflating objects and libraries),
but it's an angry beast, and we don't want to provoke it.  **The
mantra is "C with classes"**.

Explicitly approved C++ features:

  * Initializers that aren't constant; e.g. the ``gpio_dev*`` values
    in a ``PIN_MAP``.

  * Default arguments: e.g., the timeout argument in
    :ref:`lang-waitforbuttonpress`.

Explicitly forbidden C++ features:

  * Templates

Conditionally allowed C++ features:

  * Operator overloading: Never allowed when it's just for style.
    Probably fine when you're implementing a class that models a
    mathematical structure, and you'd like to implement
    e.g. ``operator+()``.


.. highlight:: cpp

.. _lang-comments:

Comments
========

Comments are lines in the program that are used to inform yourself or
others about the way the program works. They are ignored by the
compiler, and not exported to the processor, so they don't take up any
space in RAM or Flash.

One use for comments is to help you understand (or remember) how your
program works, or to inform others how your program works.  There are
two different ways of making comments.

.. _lang-comments-singleline:

**Single line comment**: Anything following two slashes, ``//``, until
the end of the line, is a comment::

     x = 5;  // the rest of this line is a comment

.. _lang-comments-multiline:

**Multi-line comment**: Anything in between a pair of ``/*`` and ``*/``
is a comment::

    /* <-- a slash-star begins a multi-line comment

    all of this in the multi-line comment - you can use it to comment
    out whole blocks of code

    if (gwb == 0){   // single line comment is OK inside a multi-line comment
    x = 3;
    }

    // don't forget the "closing" star-slash - they have to be balanced:
    */

Note that it's okay to use single-line comments within a multi-line
comment, but you can't use multi-line comments within a multi-line
comment.  Here's an example::

    /* ok, i started a multi-line comment

    x = 3; /* this next star-slash ENDS the multi-line comment: */

    x = 4; // this line is outside of the multi-line comment

    // next line is also outside of the comment, and causes a compile error:
    */

Programming Tip
---------------

When experimenting with code, "commenting out" parts of your program
is a convenient way to remove lines that may be buggy.  This leaves
the lines in the code, but turns them into comments, so the compiler
just ignores them. This can be especially useful when trying to locate
a problem, or when a program refuses to compile and the compiler error
is cryptic or unhelpful.

.. include:: /arduino-cc-attribution.txt

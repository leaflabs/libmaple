.. _arduino-comments:

Comments
========

Comments are lines in the program that are used to inform yourself
or others about the way the program works. They are ignored by the
compiler, and not exported to the processor, so they don't take up
any space on the Atmega chip.



Comments only purpose are to help you understand (or remember) how
your program works or to inform others how your program works.
There are two different ways of marking a line as a comment:



Example
-------

::

     x = 5;  // This is a single line comment. Anything after the slashes is a comment 
             // to the end of the line
    
    /* this is multiline comment - use it to comment out whole blocks of code
    
    if (gwb == 0){   // single line comment is OK inside a multiline comment
    x = 3;           /* but not another multiline comment - this is invalid */
    }
    // don't forget the "closing" comment - they have to be balanced!
    */



**Tip**
When experimenting with code, "commenting out" parts of your
program is a convenient way to remove lines that may be buggy. This
leaves the lines in the code, but turns them into comments, so the
compiler just ignores them. This can be especially useful when
trying to locate a problem, or when a program refuses to compile
and the compiler error is cryptic or unhelpful.



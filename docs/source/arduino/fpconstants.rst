.. _arduino-fpconstants:

floating point constants
========================

Similar to integer constants, floating point constants are used to
make code more readable. Floating point constants are swapped at
compile time for the value to which the expression evaluates.



Examples:



``n = .005;``



Floating point constants can also be expressed in a variety of
scientific notation. 'E' and 'e' are both accepted as valid
exponent indicators.



::

    
    floating-point   evaluates to:      also evaluates to:
      constant 
    
       10.0              10
      2.34E5          2.34 * 10^5             234000
      67e-12        67.0 * 10^-12         .000000000067



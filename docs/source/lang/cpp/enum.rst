.. highlight:: cpp

.. _lang-enum:

``enum``
========

The ``enum`` keyword is used to specify an enumeration type.  An
enumeration type is a type whose values are taken from a specified,
fixed list of constant values.

Example
-------

Here's an example defining an enumeration type called ``weather``,
which has values ``HOT``, ``COMFY``, and ``COLD``::

    enum weather {HOT, COMFY, COLD};

Once you've defined this type, you can create variables of type
``weather``, in the same way you would with an :ref:`int <lang-int>`::

    // create a weather variable named theWeather, with value COMFY:
    weather theWeather = COMFY;

Enumeration types are useful within :ref:`switch statements
<lang-switchcase>`.  If you know that an argument is of an enumeration
type, you can make ``case`` statements for all of that type's possible
values, so you know you won't miss anything::

    void describeWeather(weather currentWeather) {
        switch(currentWeather) {
        case HOT:
            SerialUSB.println("it's hot out");
            break;
        case COMFY:
            SerialUSB.println("it's nice today");
            break;
        case COLD:
            SerialUSB.println("it's freezing!");
            break;
        }
    }

Such a ``switch`` statement would need no :ref:`default
<lang-switchcase-default>`, since we know that ``currentWeather`` must
be either ``HOT``, ``COMFY``, or ``COLD``.

See Also
--------

- :ref:`lang-switchcase`

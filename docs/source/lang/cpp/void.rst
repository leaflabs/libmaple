.. highlight:: cpp

.. _lang-void:

``void``
========

.. cpp:type:: void

   The ``void`` keyword is used in function declarations. It indicates
   that the function is expected to return no information to the
   function from which it was called, or that it expects no arguments
   from its caller.

Example
-------

::

    // actions are performed in the functions "setup" and "loop"
    // but  no information is reported to the larger program

    void setup() {
      // ...
    }

    void loop() {
      // ...
    }

.. include:: /arduino-cc-attribution.txt

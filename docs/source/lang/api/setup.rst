.. highlight:: cpp

.. _lang-setup:

setup()
=======

The ``setup()`` function is called when a sketch starts. Use it to
initialize :ref:`variables <lang-variables>`, :ref:`pin modes
<lang-pinmode>`, start using :ref:`libraries <libraries>`, etc. The
``setup()`` function will only run once, after each power-up or reset
of the Maple board.

Example
-------

::

    int buttonPin = 38;

    void setup() {
      pinMode(buttonPin, INPUT);
    }

    void loop() {
      // ...
    }

.. include:: /arduino-cc-attribution.txt

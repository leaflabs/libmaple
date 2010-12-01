.. _ide:

Maple IDE
=========

This page documents the basic functionality of the Maple IDE.
Specifically, it describes the operation of the buttons on the main
toolbar.  It is expected to become more comprehensive over time.

The :ref:`Maple Quickstart <maple-quickstart>` is another good source of
information on the IDE; it is especially useful for setting up a
computer for the first time.

.. figure:: /_static/img/ide-blinky.png
   :align: center
   :alt: Maple IDE

.. _ide-verify:

Verify
------

.. image:: /_static/img/button-verify.png
   :align: left

Click Verify to compile the current sketch.

.. _ide-stop:

Stop
----

.. image:: /_static/img/button-stop.png
   :align: left

Click Stop to cancel a compilation.

.. _ide-new:

New
---

.. image:: /_static/img/button-new.png
   :align: left

Click New to begin a fresh sketch.

.. _ide-open:

Open
----

.. image:: /_static/img/button-open.png
   :align: left

Click Open to open a new sketch.  By default, this will look in you
*sketchbook*, which is a directory on your system which contains all
of your sketches.  The default directory of your sketchbook varies by
operating system; you can change it in the IDE preferences.

.. _ide-save:

Save
----

.. image:: /_static/img/button-save.png
   :align: left

Click Save to save the currently opened sketch.

.. _ide-upload:

Upload
------

.. image:: /_static/img/button-upload.png
   :align: left

Click Upload to send the compiled sketch to your Maple to run.  Before
you click Upload, you must have a memory location and serial port
selected.  The memory location, either Flash or RAM, determines
whether the compiled sketch binary will be stored on the Maple.  You
can choose this using the Tools > Board menu.  The serial port
corresponds to the Serial-over-USB connection the Maple has
established with your computer.  This looks like "COM1", "COM2",
etc. on Windows, "/dev/tty.usbmodemXXX" on Mac (where "XXX" is some
sequence of letters and numbers), or "/dev/ttyACMXXX" on Linux (again,
where "XXX" is some sequence of letters and numbers).  You can choose
a serial port using the Tools > Serial Port menu.

If you click Upload without having made these choices; The IDE
*should* prompt you to do so.  However, if you're trying to upload and
are unsuccessful, make sure you've made choices for both board and
serial port.

For more help, the upload process is documented in more detail (with
screenshots) in the :ref:`quickstart <maple-quickstart-upload>`.

If all else fails, try putting your Maple in :ref:`perpetual
bootloader mode <troubleshooting-perpetual-bootloader>` before
uploading.

In any case, you can always find us on the `forum`_ or `contact us
directly`_.

.. _ide-serial-monitor:

Serial Monitor
--------------

.. image:: /_static/img/button-serial-monitor.png
   :align: left

Click Serial Monitor to open up a communications channel between your
PC and the Maple's :ref:`Serial-over-USB <lang-serialusb>`
(``SerialUSB``) virtual serial port.

If the serial monitor is open, any information sent to the computer
(e.g. using :ref:`SerialUSB.println() <lang-serialusb-println>` will
be displayed in the large text area.  You can send data to the Maple
(to be read with e.g. :ref:`SerialUSB.read() <lang-serialusb-read>`)
by typing into the small text box and either hitting the Enter key or
pressing the Send button.

Here is an example serial monitor session with the InteractiveTest
sketch (which you can load in the IDE by choosing menu item File >
Examples > Maple > InteractiveTest):

.. image:: /_static/img/serial-monitor.png

This is the result of typing "?" in the text box and clicking Send.

.. note:: You cannot upload a sketch while the serial monitor is open.
   If you click :ref:`Upload <ide-upload>` while the serial monitor is
   open, the IDE will close it for you before proceeding with the
   upload.

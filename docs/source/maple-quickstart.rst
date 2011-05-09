.. highlight:: sh

.. _maple-quickstart:

========================
 Maple Quickstart Guide
========================

.. TODO [0.1.0] Update the images; we've changed "to FLASH" -> "to Flash"

You'll need a `Maple board <http://leaflabs.com/store/>`_, a `Mini-B
USB cable <http://www.google.com/products?q=mini-b+usb+cable>`_, a
functional computer, and possibly root (or "administrator") access to
that computer.

If you have trouble along the way, try the :ref:`troubleshooting page
<troubleshooting>` for help with some common problems.  If all else
fails, try our `forum`_, or `contact`_ us directly!

.. contents:: Contents
   :local:

.. _maple-quickstart-get-ide:

Install and run the IDE
-----------------------

See the :ref:`IDE installation page <maple-ide-install>` for instructions.

.. _maple-quickstart-compile-blinky:

Compile a program!
------------------

Let's load up a simple example program that blinks the status LED.
From the File menu, select Examples > Digital > Blink:

.. image:: /_static/img/blinky.png
   :align: center
   :alt: Click "Blink"

Next, select Tools > Board > "LeafLabs Maple ... to FLASH":

.. image:: /_static/img/blinky-to-flash.png
   :align: center
   :alt: Upload to FLASH

.. note::

   You have the option between RAM and FLASH programming: FLASH saves
   the program into permanent memory so the program will be run every
   time the Maple is reset, while RAM simply injects the compiled
   program into the processor's memory.

   Programming to RAM is faster to upload and a buggy program can be
   wiped away with a simple reset, while FLASH memory is larger and is
   the only option for permanently uploading a program.

.. image:: /_static/img/verify_button.png
   :align: left
   :alt: Verify button

Now press the "Verify" button (the "play" symbol; see image at left)
to compile the code.  Some output should scroll by in the bottom
window, and then a confirmation message will appear:

.. image:: /_static/img/verify-success.png
   :align: center
   :alt: Code verified successfully.

.. _maple-quickstart-upload:

Upload that program!
--------------------

.. FIXME [0.1.0 Maple-specific image; add one for Native]

Now it's time to plug in your Maple.  Use a Mini-B cable, making sure
that the :ref:`power source jumper <maple-powering>` is on the USB
header first.  We ship Maples with the power source jumper configured
that way, so you shouldn't have to do anything.  For reference, it
should look like this (don't worry if a jumper is hanging half off of
the CHRG header):

.. image:: /_static/img/plugged-in-maple.png
   :align: center
   :alt: Correctly plugged in Maple

.. note::

   On OS X, a network interface dialog will pop up every time you plug in
   the Maple.

   .. image:: /_static/img/osx-unconfigured-popup.png
      :align: center
      :alt: Unconfigured modem popup

  If you click "Network Preferences..." and accept the default ("Not
  Configured"), the dialog won't pop up and everything will work fine.
  That is, from this window, click "Apply":

   .. image:: /_static/img/osx-network-prefs-unconfigured.png
      :align: center
      :scale: 75%
      :alt: Click "Apply"

The Maple should blink a short pattern on the blue status LED every
time it is plugged in, reset, or reprogrammed, just to let you know
it's there.  If it ever starts throbbing in a slow, smooth pattern,
then you've got a problem: see the :ref:`troubleshooting
<troubleshooting>` page for help.

If all systems are go, select the Maple's serial port in the Tools >
Serial Port menu.  The Maple will appear as something like
:file:`COMx`, :file:`/dev/ttyACMx`, or :file:`/dev/tty.usbmodemxxxxx`,
depending on your platform, like so:

Windows XP:

.. image:: /_static/img/serial-port-win.png
   :align: center
   :alt: Board type and serial port for Windows XP

Linux:

.. image:: /_static/img/serial-port-ubuntu.png
   :align: center
   :alt: Board type and serial port for Linux

OS X:

.. image:: /_static/img/serial-port-mac.png
   :align: center
   :alt: Board type and serial port for the OS X

Then press the "Upload" button to upload your program to the
Maple.

.. image:: /_static/img/upload-button.png
   :align: center
   :alt: Click the "Upload" button

You should see some text and a progress bar flash by in the status
window of the IDE, then some blinky patterns on the Maple, and then a
constant blinking on and off.  Congratulations!  You've successfully
uploaded your first program to the Maple.

Next, go ahead and modify the file a little bit.  If you change the
``delay(1000);`` lines to a different value, the speed of the blink
will change.  The value is a time in milliseconds to pause before
continuing with the program, so by default, the LED will be on for 1
second, then off for 1 second, etc.  Any time you make any changes, go
through the same Verify and Upload process to upload the new version
of your program to your Maple.

.. warning::

   The uploading step is the most common source of problems,
   especially on Windows.

   The situation is much improved over the past, but if you have
   trouble, try doing things again, unplugging your Maple and plugging
   it back in, using :ref:`perpetual bootloader mode
   <troubleshooting-perpetual-bootloader>`, or restarting the
   IDE.

   If nothing works, please report the problem in the `forum`_.

.. _maple-quickstart-serial-port:

Use the serial port monitor!
----------------------------

As a last step to make sure everything has been configured correctly,
let's upload a "Hello, world!" program that will send text from the
Maple back to the IDE over the USB connection. From the File menu,
select Examples > Stubs > HelloWorld (similarly to when you selected
the Blink program), and make sure the correct board and serial port
targets are selected from the Tools menu.

Open the Serial Monitor window (on the far right of the toolbar) and
make sure the 9600 baud speed is selected. Then go back to the code
editing window and upload your program (Upload will recompile your
code automatically if there's been any change since the last
Verify). You should get text spit at you over the serial monitor right
after the program is uploaded.  Shout back!  We can hear you!

Go forth exuberantly!
---------------------

We really hope you got this far and didn't frown or make a bitter
lemon face getting here. Where you go now is up to you: perhaps you've
got some crazy project cooking, or a longer tutorial to work through,
or maybe now is a good time for a trip to the kitchen for a delicious
`sandwich <http://everything2.com/title/Velvet+Elvis>`_.

If you blew through this guide and are the kind of person who drinks
their coffee straight, has more than a 100 lines of vim or emacs
customization, and doesn't even have a mouse plugged into their
computer, you may want to look at the :ref:`Unix toolchain quickstart
<unix-toolchain>` guide.  It's the tutorial for getting working with
your old friends :command:`make`, :command:`gcc`, and :command:`jtag`.

Let us know what you come up with! Tag us with #leaflabs on Twitter,
post in the `forum`_, post on `our wiki's Projects page
<http://wiki.leaflabs.com/index.php?title=Projects>`_, track us down
in the real world, whatever. We love projects!

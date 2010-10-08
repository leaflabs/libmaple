.. highlight:: sh

.. _maple-quickstart:

========================
 Maple Quickstart Guide
========================

You'll need a `Maple board <http://leaflabs.com/store/>`_, a `mini-b
USB cable <http://www.google.com/products?q=mini-b+usb+cable>`_, a
functional computer, and possibly root (or "administrator") access to
that computer.

If you have trouble along the way try the :ref:`install page
<maple-ide-install>` for more detailed download and installation
instructions, and the :ref:`troubleshooting page <troubleshooting>`
for help with some common problems.  If all else fails, try our `forum
<http://forums.leaflabs.com>`_, or `contact us directly
<http://leaflabs.com/contact>`_!

The major steps are:

* :ref:`Download and install the IDE <maple-quickstart-download>`

* :ref:`(Windows) Resolve driver issues <maple-ide-install-windows-drivers>`

* :ref:`Run the IDE <maple-quickstart-run-ide>`, then :ref:`compile
  and upload a simple Blink program <maple-quickstart-compile-blinky>`

* Test the USB serial connection with a HelloWorld 

.. _maple-quickstart-download:

1. Download the IDE
-------------------

Choose the correct version for your operating system:

.. list-table::
   :widths: 15 30 50
   :header-rows: 1

   * - Platform
     - Status
     - IDE Package
   * - Windows
     - Tested on 32bit Windows XP
     - `maple-ide-LATEST-windowsxp32.zip <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-LATEST-windowsxp32.zip>`_ (about 75mb)
   * - Linux
     - Tested on Ubuntu 9.10 (64bit) and 10.04 (32bit)
     - `maple-ide-LATEST-linux32.tgz <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-LATEST-linux32.tgz>`_ (about 30mb)

       `maple-ide-LATEST-linux64.tgz <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-LATEST-linux64.tgz>`_ (about 30mb)
   * - Mac OSX
     - Tested on Snow Leopard 10.6 (64bit and 32bit)
     - `maple-ide-LATEST-macosx-10_6.dmg <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-LATEST-macosx-10_6.dmg>`_ (about 40mb)

.. note::

  The Linux release requires that you have a Java runtime (JRE)
  installed. If you're on Linux, don't have a JRE, and don't know how
  to install one, see the :ref:`installation page
  <maple-ide-install-java>`.

The package bundles together a compiler, an upload utility, a software
library, and a simple GUI text editor. All this software is `free and
open <http://fsf.org/>`_; we are grateful to the `Arduino
<http://arduino.cc/>`_, `CodeSourcery
<http://www.codesourcery.com/>`_, `GNU <http://gnu.org/>`_, and
`OpenMoko <http://openmoko.com/>`_ developers, as well as many others,
who allow us to reuse their software.

2. Install the IDE
------------------

**Windows:**

First, extract all the files in the ZIP file to a suitable location on
your system (like your Desktop folder).

Next, you'll have to install drivers; see the :ref:`installation page
<maple-ide-install-windows-drivers>` for more details. Sorry!

**Linux:**

Extract the tarball to an appropriate location (like your
home directory or desktop).

Make sure you have a Java runtime (JRE) installed; if you can run
:command:`java` from the shell, you should be fine.  For instructions
on installing a JRE, try the :ref:`installation page
<maple-ide-install-java>` or searching the package manager for your
distribution.

Next, run the script :file:`install-udev-rules.sh` in the extracted
IDE directory.  It will ask for root permissions.  You now need to
restart udev::

  sudo /etc/init.d/udev restart

This will grant members of the group ``plugdev`` read/write access to
Maple devices over USB.  Make sure that you are in that group.  (For
more information on why this is part of the install process, see the
:ref:`Unix toolchain quickstart <toolchain-udev>`).

**OS X:**

Double-click on the :file:`.dmg` file you downloaded in :ref:`Step 1
<maple-quickstart-download>`.

Next, drag and drop the Maple IDE icon into your computer's
Applications folder.

.. _maple-quickstart-run-ide:

3. Run the IDE
--------------

**Windows:**

Double-click on the :command:`maple-ide` program from within the
extracted IDE directory.

**Linux:**

Run :file:`maple-ide` from the shell, or double click on it if your
window system supports it.

**OS X:**

Double-click the :command:`Maple IDE` application you dragged into
your computer's :file:`Applications` folder.

.. _maple-quickstart-compile-blinky:

4. Compile a program!
---------------------

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

Now press the "verify" button (furthest to the left with a "play"
arrow) to compile the code.  Some output should scroll by in the
bottom window, and then a confirmation message will appear:

.. image:: /_static/img/verify-success.png
   :align: center
   :alt: Code verified successfully.

5. Upload that program!
-----------------------

Now it's (finally!) time to plug in your Maple. Use a mini-b cable,
making sure that the power source jumper is on the USB header
first.

The Maple should blink a short pattern on the blue status LED every
time it is plugged in, reset, or reprogrammed, just to let you know
it's there. If it ever starts throbbing in a slow, smooth pattern that
means you've got a problem: see the troubleshooting page.

On OS X, a modem setup dialog will pop up every time you plug in the
Maple.  If you go to System Preferences Network Settings and accept
the default ("unconfigured") settings, the dialog won't pop up and
everything will work fine.

If all systems are go, select the Board type and Serial Port
(something like /dev/ttyACM0, /dev/cu.usbmodem5d21, or COM3 depending
on your platform) from the Tools menu. Then press the "upload" button
(right arrow to a bunch of dots) to upload your program to the
Maple. You should see some text and a progress bar flash by in the
status window of the IDE, then some blinky patterns on the Maple, and
then a constant blink with whatever time period you programmed in
above.

Go ahead and modify the file a little bit: if you change the
'delay(1000);' numbers to a different value the speed of the blink
will change. The value is a time in milliseconds to pause before
continuing with the program, so by default the LED will be on for 1
second, then off for 1 second, etc.

.. warning::

   This step is the most common source of problems, especially on
   Windows.

   The situation is much improved over the past, but if you have
   trouble, try doing things again, unplugging your Maple and plugging
   it back in, using :ref:`perpetual bootloader mode
   <troubleshooting-perpetual-bootloader>`, or restarting the
   IDE.

   Please report any problems in the forums.  If we don't know it's
   broken, we can't fix it!

6. Use the serial port monitor!
-------------------------------

As a last step to make sure everything has been configured correctly,
let's upload a hello world program that will send text from the Maple
back to the IDE over the USB connection. From File select Examples,
Stubs, HelloWorld, and make sure the correct board and serial port
targets are selected from the Tools pull-down. And of course you could
change the text to be printed out; make sure you leave the double
quotes around it though or you'll get a compile error.

Open the serial monitor window (button on the far right) and make sure
the 9600 baud speed is selected. Then go back to the code editing
window and upload your program (upload will recompile your code
automatically if there's been any change since the last "verify"). You
should get text spit at you over the serial monitor right after the
program is uploaded. Shout back! We can hear you!

7. Go forth exuberantly!
------------------------

We really hope you got this far and didn't frown or make a bitter
lemon face too often getting here. Where you go now is up to you:
perhaps you've got some crazy project cooking, or a longer tutorial to
work through, or maybe now is a good time for a trip to the kitchen
for a delicious sandwich.

If you blew through this guide and are the kind of person who drinks
their coffee straight and has more than a 100 lines of vim or emacs
customization and doesn't even have a mouse plugged into your computer
you may want to look at the Unix Toolchain quickstart guide to getting
working with your old friends make, jtag, and gcc.

Let us know what you come up with! Tag internet content with
#leaflabs, post in the forums, track us down in the real world,
whatever. We love projects!

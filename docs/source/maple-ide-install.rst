.. highlight:: c++

.. _maple-ide-install:

========================
 Maple IDE Installation
========================

If you still can't get the IDE installed after reading this page,
check the :ref:`troubleshooting page <troubleshooting>` for help with
some common problems. If all else fails, try our `forum`_, or `contact
us directly`_\ !

.. contents:: Contents
   :local:

Download
--------

The current release of the Maple IDE is version 0.0.9.  Choose the
correct version for your operating system:

.. list-table::
   :widths: 15 30 50
   :header-rows: 1

   * - Platform
     - Status
     - IDE Package
   * - Windows
     - Tested on 32bit Windows XP
     - `maple-ide-0.0.9-windowsxp32.zip <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-0.0.9-windowsxp32.zip>`_ (about 75mb)
   * - Linux
     - Tested on Ubuntu 9.10 (64bit) and 10.04 (32bit)
     - `maple-ide-0.0.9-linux32.tgz <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-0.0.9-linux32.tgz>`_ (about 30mb)

       `maple-ide-0.0.9-linux64.tgz <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-0.0.9-linux64.tgz>`_ (about 30mb)
   * - Mac OSX
     - Tested on Snow Leopard 10.6 (64bit and 32bit)
     - `maple-ide-0.0.9-macosx-10_6.dmg <http://static.leaflabs.com/pub/leaflabs/maple-ide/maple-ide-0.0.9-macosx-10_6.dmg>`_ (about 40mb)

The package bundles together a compiler, an upload utility, a software
library, and a simple GUI text editor. All this software is `free and
open <http://fsf.org/>`_; we are grateful to the `Arduino
<http://arduino.cc/>`_, `CodeSourcery
<http://www.codesourcery.com/>`_, `GNU <http://gnu.org/>`_, and
`OpenMoko <http://openmoko.com/>`_ developers, as well as many others,
who allow us to reuse their software.

**Looking for something older?** `Source archives and binaries
<http://static.leaflabs.com/pub/leaflabs/maple-ide/>`_ are available
for previously-released versions.

Installation
------------

* :ref:`Windows <maple-ide-install-windows>`
* :ref:`Linux <maple-ide-install-linux>`
* :ref:`OS X <maple-ide-install-osx>`

.. _maple-ide-install-windows:

Windows
^^^^^^^
First, extract all the files in the ZIP file to a suitable location on
your system (like your Desktop folder).  Next, you have to install
some drivers.  Sorry!

.. note:: Note that while these instructions work on Windows XP,
   changes in Windows 7 mean that you won't be able to install the IDE
   without disabling driver signing on your computer.  We're working
   on resolving this situation.  For now, `users on the forum have
   reported a workaround
   <http://forums.leaflabs.com/topic.php?id=73#post-788>`_.

First, install DFU drivers (for uploading code to your Maple) using
the following steps.

1. Plug your Maple into the USB port.

2. Hit the reset button on your Maple (it's the small button at the
   bottom left, labeled RESET).  Notice that it blinks quickly 6 times,
   then blinks slowly a few more times.

3. Hit reset again, and this time push and hold the other button
   during the 6 fast blinks (the button is on the top right; it is
   labeled BUT). You can release it once the slow blinks start.

4. Your Maple is now in :ref:`perpetual bootloader mode
   <troubleshooting-perpetual-bootloader>`.  This should give you a
   chance to install the DFU drivers.

5. Windows should now prompt you for some drivers. In the top level
   directory of the Maple IDE, point Windows to
   :file:`drivers/mapleDrv/dfu/`.

Next, install serial drivers (for communicating with your Maple using
serial over USB).

1. Reset your Maple and allow it to exit the bootloader (wait for the
   slow blinking to stop).  The Maple will next start running whatever
   program was uploaded to it last. (New Maples will start running the
   test program we upload to them before shipping them to you).

2. Once Maple is running some user code, Windows should prompt you for
   more drivers. Point windows to :file:`driver/mapleDrv/serial`.

You can now run the Maple IDE by double-clicking on the
:command:`maple-ide` program from within the extracted IDE directory.

.. _maple-ide-install-linux:

Linux
^^^^^

.. _maple-ide-install-java:
.. note::

   The IDE is written in Java and requires a compatible runtime (JRE).

   If you don't have one, they're usually pretty easy to install.  Sun
   Java 1.6 and OpenJDK 1.6 are known to work, and runtimes mostly
   compatible with Sun Java 1.5+ should probably get the job done.

   To install Java, try using your distribution's software packaging
   tool and search for "JRE" or "java". On Debian-based systems
   (including Ubuntu) you can try to install the OpenJDK 1.6 JRE
   with::

     $ sudo aptitude install openjdk-6-jre

Extract the tarball to an appropriate location (like your home
directory or desktop).

Make sure you have a Java runtime (JRE) installed; if you can run
:command:`java` from the shell, you should be fine.

Next, run the script :file:`install-udev-rules.sh` in the extracted
IDE directory.  It will ask for root permissions.  You now need to
restart udev::

  sudo /etc/init.d/udev restart

This will grant members of the group ``plugdev`` read/write access to
Maple devices over USB.  Make sure that you are in that group.  (For
more information on why this is part of the install process, see the
:ref:`Unix toolchain quickstart <toolchain-udev>`).

To run the Maple IDE, run :command:`maple-ide` from the shell, or
double-click on it if your window system supports it.

Feel free to put the IDE directory wherever you want.  As long as you
leave its internal structure unchanged, things should be fine.

.. _maple-ide-install-osx:

OS X
^^^^

Double-click on the :file:`.dmg` file you downloaded to mount the disk
image.  From the mounted image, drag and drop the Maple IDE icon into
your computer's Applications folder.

To run the Maple IDE, double-click the :command:`Maple IDE`
application you dragged into your computer's :file:`Applications`
folder.


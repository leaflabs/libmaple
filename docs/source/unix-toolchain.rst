.. highlight:: sh

.. _unix-toolchain:

===========================
 Unix Toolchain Quickstart
===========================

This is a tutorial for using the Maple with a standard Unix toolchain
(``make``, ``gcc``, etc.).  It's not necessary to do this in order to
program the Maple; you can always :ref:`install the Maple IDE
<maple-ide-install>` instead.  This document is intended for users who
are comfortable using C or C++ and would like to use :ref:`libmaple`
directly.

You'll need a Maple board, a Mini-B USB cable, a functional computer,
and root (or Administrator) access to that computer. This guide
assumes you've had success with the IDE on your machine and that you
are fairly comfortable with the Unix command line.  Some previous
experience with editing your shell startup script (.bashrc, .tcshrc,
etc.) and using `GCC <http://gcc.gnu.org/>`_ and `make
<http://www.gnu.org/software/make/>`_ is recommended.

For generic installation and setup issues, see the :ref:`IDE
installation <maple-ide-install>` and :ref:`troubleshooting` pages. If
all else fails, try our `forum`_, or `contact us directly`_\ !

We currently have instructions for 32- and 64-bit Linux and OS X Snow
Leopard. If you're on another Unix platform, Windows, or an earlier
version of OS X, we're guessing that you can translate/port these
directions on your own. As a jumping off point, you might want to
begin with these `stripped down distributions
<http://static.leaflabs.com/pub/codesourcery/>`_ of the `CodeSourcery
GCC compiler tools <http://www.codesourcery.com/sgpp/features.html>`_
(including Win32 versions). If you do have success on other platforms,
please post in the forums, so we can fold your tips into this
document!

.. contents:: Contents
   :local:

.. _toolchain-linux-setup:

Setup
-----

Linux
^^^^^

These instructions are oriented towards Linux users using a
contemporary Debian-based distribution.

**1. Collect and Install Tools**

Firs, you'll need some tools::

  $ sudo aptitude install build-essential git-core wget screen dfu-util \
                          openocd python python-serial

You'll want to install a bunch of developer "basics" like ``make``,
``tar``, etc.  A good catch-all for these tools is the
``build-essential`` meta-package on most Debian platforms: installing
this fake package will pull in dozens of useful tools without bogging
your system down too much.

`Git <http://git-scm.com/>`_ is a distributed code versioning system
we use to track changes in our source code; ``git-core`` is the
corresponding package. 

``wget`` is a simple tool to download files over http from the command
line; installing it is optional (you could pull in the required
downloads using a browser).

``screen`` is a screen manager; in the context of Maple, we use it to
connect to serial port devices.

``dfu-util`` is a tool from the `OpenMoko`_ project that we use to
upload programs to the Maple over USB.

.. _OpenMoko: http://openmoko.com/

``openocd`` is a `JTAG
<http://en.wikipedia.org/wiki/Joint_Test_Action_Group>`_ control
program used in conjunction with an ARM JTAG device to do in circuit
debugging (pause/resume program execution, upload and download code,
read out register status, etc). It's also optional.

Lastly, our reset script (which sends control signals over the
USB-serial connection to restart and enter the bootloader) is written
in `Python <http://python.org>`_, and requires the `PySerial
<http://pyserial.sourceforge.net/>`_ library available in the
``python-serial`` package.  This can also be installed with
`easy_install <http://peak.telecommunity.com/DevCenter/EasyInstall>`_.

**2. Fetch libmaple and Compiler Toolchain** ::

  $ cd ~
  $ git clone git://github.com/leaflabs/libmaple.git libmaple
  $ cd libmaple
  $ wget http://static.leaflabs.com/pub/codesourcery/gcc-arm-none-eabi-latest-linux32.tar.gz
  $ tar xvzf gcc-arm-none-eabi-latest-linux32.tar.gz
  $ export PATH=$PATH:~/libmaple/arm/bin # or wherever these tools ended up

This step is fairly straightforward: do a git clone of the `libmaple
repository <https://github.com/leaflabs/libmaple>`_ to some directory,
then download and extract the ARM compiler toolchain.

The :file:`arm/bin/` directory will need to be added to ``PATH``; you
can check that this worked by entering ``arm-none-`` and hitting tab
to auto-complete (your shell should show a bunch of results).
Regardless of where you put the toolchain, make sure to preserve its
internal directory layout, as the binaries make relative path calls
and references.

After you're done, you'll probably want to update your shell startup
script so :file:`~/libmaple/arm/bin` stays in your ``PATH``.

.. _toolchain-udev:

**3. Install udev Rules**

From the libmaple directory, ::

  $ groups # make sure it includes plugdev; if not add, yourself to it
  $ sudo cp support/scripts/45-maple.rules /etc/udev/rules.d/45-maple.rules
  $ sudo /etc/init.d/udev restart

As a security precaution on Linux, unknown USB devices can only be
accessed by root. This udev script identifies the Maple based on its
vendor and product IDs, mounts it to :file:`/dev/maple`, and grants
read/write permissions to the ``plugdev`` group. After restarting
``udev`` you'll need to fully unplug or power cycle any Maples
connected to the computer.

**So far, so good?**

Great! Test your setup by :ref:`compiling a sample program
<toolchain-test>`.

.. _toolchain-osx-setup:

OS X
^^^^

These instructions have been tested successfully on OS X 10.6.4. As
stated previously, this document assumes a general level of Unix
aptitude on the part of the reader; if you're uncomfortable using
Terminal (or if you don't know what that means), then you should
probably stick with using the `Maple IDE
<http://leaflabs.com/docs/maple-ide/>`_ to write programs.

**1. Collect and Install Tools**

You will need the following tools\ [#fpackman]_ to get started:

 1. `XCode <http://developer.apple.com/technologies/xcode.html>`_: If
 you're reading this, you've probably already got this. Provides
 compilers and other basic tools of the trade.  While XCode was once
 free of charge, Apple has since begun charging for it; if you'd
 rather not pay, you can probably get by with just a `make
 <http://www.gnu.org/software/make/>`_ binary.

 2. `Git <http://git-scm.com/>`_: All of our code is tracked by a
 distributed versioning system called Git. A `Mac installer
 <http://code.google.com/p/git-osx-installer/downloads/list?can=3>`_
 is available.

 3. ``dfu-util``: A tool from `OpenMoko`_ that we use to upload
 programs to the Maple over USB.  If you prefer to compile from
 source, OpenMoko provides instructions for `building dfu-util
 <http://wiki.openmoko.org/wiki/Dfu-util#Mac>`_.

 If you're in a hurry, you can steal a dfu-util binary from a program
 called `OpenMoko Flasher
 <http://www.handheld-linux.com/wiki.php?page=OpenMoko%20Flasher>`_. To
 do this, first `download OpenMoko Flasher
 <http://projects.goldelico.com/p/omflasher/downloads/>`_, then copy
 the OpenMoko application into your :file:`/Applications` folder (or
 wherever you like). Let's pretend you saved the .app to the directory

   :file:`/Applications/OpenMoko Flasher.app`

 Then the ``dfu-util`` binary resides in

   :file:`/Applications/OpenMoko Flasher.app/Contents/Mac OS/dfu-util`

 To get access to it from the command line, just make a symbolic link
 to the binary from some place on your ``PATH``::

   $ ln -s /Applications/OpenMoko\ Flasher.app/Contents/Mac\ OS/dfu-util \
           /somewhere/on/your/PATH/dfu-util

 .. note::
   Just copying the binary somewhere doesn't work, as it relies on
   dynamically linked libraries found elsewhere in the .app
   bundle. It's possible to pull just the relevant pieces out of the
   .app, but you're on your own.

 To make sure this worked, try plugging in your Maple, making sure
 it's in :ref:`perpetual bootloader mode
 <troubleshooting-perpetual-bootloader>` (do this by pressing RESET,
 then quickly pressing BUT and holding it for several seconds), then
 running ::

   $ dfu-util -l

 If you see some lines that look like ::

   Found DFU: [0x1eaf:0x0003] devnum=0, cfg=0, intf=0, alt=0, name="DFU Program RAM 0x20000C00"
   Found DFU: [0x1eaf:0x0003] devnum=0, cfg=0, intf=0, alt=1, name="DFU Program FLASH 0x08005000"

 then you're all set.

 4. PySerial: our reset script (which sends control signals over the
 USB-serial connection to restart and enter the bootloader) is written
 in Python and requires the `PySerial
 <http://pyserial.sourceforge.net/>`_ library. Download the `latest
 version <http://pypi.python.org/pypi/pyserial>`_. After you download
 and untar, install it with ::

   $ cd /path/to/pyserial-x.y
   $ python setup.py build
   $ sudo python setup.py install

 The package is also available via ``easy_install``, so if you're
 comfortable using that, you could also install it with ::

   $ easy_install pyserial

**2. Fetch libmaple and Compiler Toolchain**

You first need to clone libmaple::

  $ cd ~
  $ git clone git://github.com/leaflabs/libmaple.git libmaple

Then you need to get the cross-compilers we use to build a
project. These are just modified versions of GCC; you can `download
them for OS X here
<http://static.leaflabs.com/pub/codesourcery/gcc-arm-none-eabi-latest-osx32.tar.gz>`_. Assuming
you saved this file to

  :file:`~/Downloads/gcc-blah-blah-osx32.tar.gz`

you can then unpack the archive and let OS X know where the compilers
live with ::

  $ cd ~/Downloads
  $ tar -xvzf gcc-blah-blah-macosx32.tar.gz
  $ mv arm ~/libmaple/arm
  $ export PATH=$PATH:~/libmaple/arm/bin

After that's done, you'll probably want to update your shell startup
script so :file:`~/libmaple/arm/bin` stays in your ``PATH``.

**So far, so good?**

Great! Go on to the next section, where you test everything out.

.. _toolchain-test:

Test compilation
----------------

Get back into the libmaple directory (this tutorial assumes you put it
in :file:`~/libmaple`) and test that you've installed all the compilation
tools correctly::

  $ cd ~/libmaple
  $ cp main.cpp.example main.cpp
  $ make clean
  $ make

If it all works out, you should end up seeing something like this::

  find build -iname *.o | xargs arm-none-eabi-size -t
     text    data     bss     dec     hex filename
      482       4      24     510     1fe build/wirish/comm/HardwareSerial.o
      260       0       0     260     104 build/wirish/comm/HardwareSPI.o
       60       0       0      60      3c build/wirish/wirish.o

  [...]

     2196       0       1    2197     895 build/libmaple/usb/usb_lib/usb_core.o
     1904       0       0    1904     770 build/libmaple/usb/usb_lib/usb_regs.o
       56       0       0      56      38 build/libmaple/usb/usb_lib/usb_init.o
      344       0       0     344     158 build/libmaple/usb/usb_hardware.o
     6637       0      58    6695    1a27 build/main.o
    21499     201     391   22091    564b (TOTALS)

  Final Size:
  arm-none-eabi-size build/maple.out
     text    data     bss     dec     hex filename
    21824     200     552   22576    5830 build/maple.out
  Flash build

The ``dec`` field at the end gives the total program size in
bytes. The long listing of object files above the ``Final Size`` helps
to identify bloated code.  As you write larger projects, you may find
that they use too much space. If that happens, the file-by-file
listing will help you track down the culprits.

.. _toolchain-upload:

Upload a program
----------------

Let's blow away the little example program and upload the interactive
test session to your Maple.  This will let you interact with the Maple
over a :ref:`USB serial port <usb>`. If you're on Linux, then before
executing ``make install``, you'll want to have the udev rules setup
:ref:`as described above <toolchain-udev>`.

Plug in your Maple using the Mini-B USB cable; then run ::

  $ cd ~/libmaple
  $ cp examples/test-session.cpp main.cpp
  $ make clean
  $ make
  $ make install

A number of things can go wrong at this stage.  Simple debugging steps
include using :ref:`perpetual bootloader mode
<troubleshooting-perpetual-bootloader>`, restarting the Maple a couple
times, ``make clean``, etc. If nothing works, the `forum`_ is your
friend.

.. _toolchain-serialusb:

Communicate over USB-Serial interface
-------------------------------------

Now let's try out the interactive test session.  The serial port
device file should look something like :file:`/dev/ttyACMXXX` on Linux
or :file:`/dev/tty.usbmodemXXX` on OS X, but ``XXX`` will vary
depending on your system.  Try using one of these to find out which it
is::

  # Linux
  $ ls /dev/ttyACM*

  # OS X
  $ ls /dev/tty.usbmodem*

To open up a session, run ::

  $ screen /dev/ttyXXX

If the interactive test program built and uploaded correctly,
``screen`` won't report any errors, and will present you an empty
terminal.  Your board is now waiting for you to send it a command.
Type ``h`` to print a list of commands which demonstrate various
features; type any command's letter to run it.

To exit the screen session, type :kbd:`C-a C-\\` (control-a, followed
by control-backslash) on Mac, or :kbd:`C-a k` (control-a k) on Linux,
and type ``y`` when prompted if you're sure.

.. note:: 

   Using ``screen`` sometimes messes up your terminal session on OS X.
   If your shell starts acting funny after you exit ``screen``, you
   should be able to fix it with ::

       $ reset && clear

   If that doesn't work, just close the Terminal window and open up a
   new one.

.. _toolchain-projects:

Starting your own projects
--------------------------

So everything worked, and you want to start your own project? Great!
There are two ways to go about it.  

If your project is small, all you have to do is replace
:file:`~/libmaple/main.cpp` with your own code, and you're free to use
``make`` and ``make install`` in the same way you did when you first
:ref:`uploaded a program <toolchain-upload>`.

If you have a more complicated project, with its own Makefile and
multiple source files, or if you're using an IDE that creates its own
Makefile, you'll probably want to load libmaple from an archive (a
build-time library, not a DLL).

To create an archive, use the ``library`` Makefile target::

  $ cd ~/libmaple
  $ make library

This will produce a build-time library in the file
:file:`~/libmaple/build/libmaple.a`.  To use it, make sure that you
link against that library, and that the libmaple sources are in your
include path.  

At a minimum, your include path should contain the directories
:file:`~/libmaple/libmaple` and :file:`~/libmaple/wirish/`.  If you
want to use one of the officially supported :ref:`libraries
<libraries>`, those live under :file:`~/libmaple/libraries/`.  The
main include file for the Wirish library is
:file:`~/libmaple/wirish/wirish.h`.

Getting Updates
---------------

We update libmaple fairly frequently with bugfixes and other
improvements.  In order get access to these in your local copy of
the repository, you should periodically update it with::

  $ cd ~/libmaple
  $ git pull

We keep releases of libmaple and the Maple IDE in lockstep, so any
IDE updates will have corresponding library updates.  Our `blog
<http://leaflabs.com/blog/>`_ is the place to watch for major
releases; an `RSS feed <http://leaflabs.com/blog/feed/>`_ is
available.

You can sign up for a free `Github <https://github.com/plans>`_
account and `watch libmaple
<https://github.com/leaflabs/libmaple/watchers>`_ to receive
notifications about bleeding-edge development.

.. _toolchain-openocd:

Debug with OpenOCD
------------------

TODO. For now see `this great guide
<http://fun-tech.se/stm32/OpenOCD/index.php>`_ from fun-tech.se, and
the ``jtag`` Makefile target.  There is also a `JTAG How-To
<http://wiki.leaflabs.com/index.php?title=Maple_JTAG_How_To>`_ page on
our `wiki <http://wiki.leaflabs.com>`_ which you may find useful.

.. _toolchain-exuberantly:

Go forth exuberantly!
---------------------

Let us know what you come up with! Use #leaflabs on `Twitter
<http://twitter.com/leaflabs>`_, post in the `forum`_, join the the
#leafblowers IRC channel on `freenode
<http://freenode.net/irc_servers.shtml>`_, whatever. We love projects!

.. rubric:: Footnotes

.. [#fpackman] Some of these software packages might be available on
   `MacPorts <http://www.macports.org/>`_ or `Homebrew
   <http://mxcl.github.com/homebrew/>`_. The author had some bad
   experiences with MacPorts a few years ago, though, and hasn't
   touched a package manager on OS X since. Of course, your mileage
   may vary.

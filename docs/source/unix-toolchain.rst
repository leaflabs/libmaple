.. highlight:: sh

.. _unix-toolchain:

===========================
 Unix Toolchain Quickstart
===========================

This is a tutorial for using the Maple with a standard Unix toolchain.
It's not necessary to do this in order to program the Maple; you can
always use our `IDE <maple-ide-install>`_ instead.

You'll need a Maple board, a mini-b USB cable, a functional computer,
and root access to that computer. This guide assumes you've had
success with the IDE on your machine and that you are fairly
comfortable with the Unix command line; some previous experience with
editing your shell startup script (.bashrc, .tcshrc, etc.) and using
`make <http://www.gnu.org/software/make/>`_ is recommended. For
generic installation/setup issues, the `IDE install
<http://leaflabs.com/docs/libmaple/install/>`_ and
:ref:`troubleshooting` pages may be helpful. If all else fails, try
our `forum`_, or `contact us directly`_\ !

We currently have instructions for 32- and 64-bit Linux and OS X Snow
Leopard. If you're on another Unix platform, Windows, or an earlier
version of OS X, we're guessing that you can translate/port these
directions on your own. As a jumping off point, you might want to
begin with these `stripped down distributions
<http://static.leaflabs.com/pub/codesourcery/>`_ of the `CodeSourcery
GCC compiler tools <http://www.codesourcery.com/sgpp/features.html>`_
(including win32 versions). If you do have success on other platforms,
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

First I'll give the commands to run, then explain::

  $ sudo aptitude install build-essential git-core wget screen dfu-util \
                          openocd python python-serial

You'll want to install a bunch of developer "basics" like
:command:`make`, :command:`tar`, etc.  A good catch-all for these
tools is the "build-essential" meta-package on most debian platforms:
installing this fake package will pull in dozens of useful tools
without bogging your system down too much. ``git-core`` is the name of
the git package; `Git <http://git-scm.com/>`_ is a distributed code
versioning system we use to track changes in our source
code. :command:`wget` is a simple tool to download files over http
from the command line, and is optional (you could pull in the required
downloads using a browser). :command:`screen` is a really cool virtual
terminal program; in the context of Maple, we use it to connect to
serial port devices.

:command:`dfu-util` is a tool from the `OpenMoko`_ project that we use
to upload programs to the Maple over USB.

.. _OpenMoko: http://openmoko.com/

:command:`openocd` is a `JTAG
<http://en.wikipedia.org/wiki/Joint_Test_Action_Group>`_ control
program used in conjunction with an ARM JTAG device to do in circuit
debugging (pause/resume program execution, upload and download code,
read out register status, etc). (optional)

Lastly, our reset script (which sends control signals over the
USB-serial connection to restart and enter the bootloader) is written
in Python and requires the `PySerial
<http://pyserial.sourceforge.net/>`_ library (the ``python-serial``
package; this could also be installed with `easy_install
<http://peak.telecommunity.com/DevCenter/EasyInstall>`_).

**2. Fetch libmaple and Compiler Toolchain** ::

  $ cd ~
  $ git clone git://github.com/leaflabs/libmaple.git libmaple
  $ cd libmaple
  $ wget http://static.leaflabs.com/pub/codesourcery/gcc-arm-none-eabi-latest-linux32.tar.gz
  $ tar xvf gcc-arm-none-eabi-latest-linux32.tar.gz
  $ export PATH=$PATH:~/libmaple/arm/bin # or wherever these tools ended up

This step is fairly straightforward: do a git clone of the `libmaple
repository <http://github.com/leaflabs/libmaple>`_ to some directory,
then download and extract the ARM compiler toolchain.

The :file:`arm/bin/` directory will need to be added to ``PATH``; you
can check that this worked by entering ``arm-none-`` and hitting tab
to auto-complete (bash should show a bunch of results).  Regardless of
where you put the toolchain, make sure to preserve its internal
directory layout, as the binaries make relative path calls and
references.

.. _toolchain-udev:

**3. Install udev Rules**

From the libmaple directory, ::

  $ groups # make sure it includes plugdev; if not add, yourself to it
  $ sudo cp support/scripts/45-maple.rules /etc/udev/rules.d/45-maple.rules
  $ sudo /etc/init.d/udev restart

As a security precaution on linux, unknown USB devices can only be
accessed by the superuser. This udev script identifies the Maple based
on its vendor and product IDs, mounts it to :file:`/dev/maple`, and
grants read/write permissions to the ``plugdev`` group. After
restarting :command:`udev` you'll need to fully unplug or power cycle
any Maples connected to the computer.

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
<http://leaflabs.com/docs/maple-ide/>`_ to develop programs. Some of
these software packages might be available on `MacPorts
<http://www.macports.org/>`_. The author had some bad experiences with
MacPorts a few years ago, though, and hasn't touched it since. Of
course, your mileage may vary.

**1. Collect and Install Tools**

You will need the following tools to get started:

 1. `XCode <http://developer.apple.com/technologies/xcode.html>`_: If
 you're reading this, you've probably already got this. Provides
 compilers and other basic tools of the trade. It's a free download,
 but requires registration (gross, we know).

 2. `Git <http://git-scm.com/>`_: All of our code is tracked by a
 distributed versioning system called git. A `Mac installer
 <http://code.google.com/p/git-osx-installer/downloads/list?can=3>`_
 is available.

 3. :command:`dfu-util`: A tool from `OpenMoko`_ that we use to upload
 programs to the Maple over USB. If you're feeling masochistic, there
 are instructions for `building dfu-util from source
 <http://wiki.openmoko.org/wiki/Dfu-util#Mac>`_.

 However, if you've got better things to do, you can steal a dfu-util
 binary from a program called `Openmoko Flasher
 <http://www.handheld-linux.com/wiki.php?page=Openmoko%20Flasher>`_. To
 do this, first `download Openmoko Flasher
 <http://projects.goldelico.com/p/omflasher/downloads/>`_, then copy
 the .app into your :file:`/Applications` folder (or wherever you
 like). Let's pretend you saved the .app to the directory

   :file:`/Applications/OpenMoko Flasher.app`

 Then the :command:`dfu-util` binary resides in

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
 it's in bootloader mode (you can do this by pressing RESET, then
 quickly pressing BUT and holding it for several seconds), then
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

 The package is also available via :command:`easy_install`, so if
 you're comfortable using that, you could also install it with ::

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

Woo! It worked. The ``dec`` field at the end gives the total program
size in bytes. The long listing of object files above the ``Final
Size`` helps to identify bloated code.  As you write larger projects,
you may find that they use too much space. If that happens, the
file-by-file listing will help you track down the fatties porking up
your program.

.. _toolchain-upload:

Upload a program
----------------

Ok, let's blow away the little example program and upload the
interactive test session to your Maple.  This will let you interact
textually with the Maple via USB-serial. If you're on Linux, then
before executing :command:`make install`, you'll want to have the udev
rules setup :ref:`as described above <toolchain-udev>`.  Plug in your Maple
using the mini-b USB cable; then run ::

  $ cd ~/libmaple
  $ cp examples/test-session.cpp main.cpp
  $ make clean
  $ make
  $ make install

A number of things can go wrong at this stage.  Simple debugging steps
include using :ref:`perpetual bootloader mode
<troubleshooting-perpetual-bootloader>`, restarting the Maple a couple
times, :command:`make clean`, etc. If nothing works, the `forum`_ is
your friend.

.. _toolchain-serialusb:

Communicate over USB-serial interface
-------------------------------------

Okay, now that we've flashed the interactive test session to the
Maple, let's test it out. The device for the maple should look
something like :file:`/dev/ttyACMXXX` on Linux or
:file:`/dev/tty.usbmodemXXX` on OS X, but it might have a slightly
different name on your system. To open up a session, run ::

  $ screen /dev/tty-whatever-it-is

If the interactive test program built and uploaded correctly, you
should be able to connect without any errors reported by
:command:`screen`. Type ``h`` or hit the space bar to get a response;
there are a number of commands which demonstrate Maple peripheral
features. As of October 2010, the HardwareSerial library is blocking,
so using any commands which would write to the USART Serial ports will
cause the program to hang. To exit the screen session, type :kbd:`C-a
C-\\` (control-a, followed by control-backslash), and type ``y`` when
prompted if you're sure.

Using :command:`screen` in this way sometimes messes up your session.
If your shell starts acting up after you exit screen, you should be
able to fix it with ::

  $ reset && clear

.. _toolchain-projects:

Starting your own projects
--------------------------

So everything worked, and you want to start your own project? Great!
It's easy. Just set the environment variable ``LIB_MAPLE_HOME`` in
your shell startup script to point to the libmaple repository you
cloned (this tutorial assumes you put it in :file:`~/libmaple`). For
example, if you use bash as your shell, just put this line in your
:file:`~/.bashrc` or :file:`~/.bash_profile`::

  export LIB_MAPLE_HOME=~/libmaple

Now, in order to start your own projects, just grab a copy of the
:file:`Makefile` and skeleton :file:`main.cpp` we provided in the
libmaple repository, and you're good to go::

  $ cd
  $ mkdir my-awesome-project
  $ cp ~/libmaple/Makefile ~/libmaple/build-targets.mk my-awesome-project
  $ cp ~/libmaple/main.cpp.example my-awesome-project/main.cpp

(TEMPORARY: The file :file:`build-targets.mk` is where the rule to
build the object file for :file:`main.cpp` lives. If you have multiple
source files, you'll probably need to look at it and edit as
appropriate. We're sorry about that and will update the Makefile
structure later to remove this pain point.) Then hack away! You can
:command:`make`, :command:`make clean`, and :command:`make install`
from your new directory :file:`my-awesome-project` just like you did
in the libmaple repository.

.. note::

  We update the libmaple repository fairly frequently with bugfixes
  and other improvements.  In order get access to these in your local
  copy of the repository, you should periodically update it with::

    $ cd $LIB_MAPLE_HOME
    $ git pull

  The `commits page
  <http://github.com/leaflabs/libmaple/commits/master>`_ for the
  github repository is a good place to watch for bleeding-edge
  updates; our `blog <http://leaflabs.com/blog/>`_ is the place to
  watch for major releases.  We keep releases of libmaple and the
  Maple IDE in lockstep, so any IDE updates will have corresponding
  library updates.

.. _toolchain-openocd:

Debug with OpenOCD
------------------

TODO. For now see `this great guide
<http://fun-tech.se/stm32/OpenOCD/index.php>`_ from fun-tech.se, and
the ``jtag`` Makefile target.

.. _toolchain-codeblocks:

Do it all with Code::Blocks
---------------------------

.. TODO this really should reflect the new, more pleasant build system

Optional. `Code::Blocks <http://www.codeblocks.org/>`_ is a generic
cross platform IDE.  We don't personally use it for development, so we
haven't worked out all the kinks (e.g., debugging isn't integrated),
but it might be helpful for people who are allergic to `vim
<http://www.vim.org/>`_ and/or `Emacs
<http://www.gnu.org/software/emacs/>`_. The simple configuration
described here just calls down to the :file:`Makefile`, so follow the
above directions to get the command line tools configured (you'll
definitely need the arm-none-eabi-* tools on your ``PATH``), then
`install Code::Blocks <http://www.codeblocks.org/downloads/26>`_. You
can do this on Linux with::

  $ sudo aptitude install codeblocks

The first time it runs you'll maybe want to disable all the glitzy
"Getting Started" crap (when will they learn?). We've added a .cbp
"projects" file to the libmaple repository: you can try using that one
by copying it from :file:`support/codeblocks/libmaple.cbp` to the top
level directory, but no promises (it might be missing new source files
etc). It's probably worth reading through these instructions as well
to get a feel for how it all works.

To create your own "libmaple" project, start with an "Empty Project"
with the "Folder to create project in" set to your
``LIB_MAPLE_HOME``. Make sure that the "Resulting filename" is in the
top level directory as well.

.. image:: /_static/img/codeblocks_newproject.png
   :align: center
   :alt: Code::Blocks new project wizard

Select the "GNU GCC Compiler" (it won't be used, anyway) and disable
the "Debug" configuration in the next window. Now you should have a
project with no files; add files by right clicking on the project in
the left panel file hierarchy and "Add files recursively". Import both
the :file:`wirish` and :file:`libmaple` directories recursively, then
add :file:`main.cpp` separately.

.. image:: /_static/img/codeblocks_makefile.png
   :align: center
   :alt: Code::Blocks targets options

Next we have to configure the Makefile targets. Go to the
"Properties..." menu under "Project" and check the "This is a custom
Makefile" box. Then go to the "Build targets" tab and create "ram" and
"flash" targets, both of type "Console application" and without the
Auto-generated filename prefixes or extensions. Set the Output
filename to :file:`support/codeblocks/program_flash.sh` and
:file:`support/codeblocks/program_ram.sh` respectively; these scripts
just call the program_ram/program_flash make targets and are a hack to
get the "run" button to upload code to the Maple. The IDE will warn
that these files will be overwritten, but they won't be. For both the
"flash" and "ram" targets, click the "Build options..." button (below
"Virtual targets..." etc) and go to the far right tab ("'Make'
commands"). Edit the Clean project/target line so it's just "clean"
(not "clean$target"), and set the "Build project/target" and "Compile
single file" commands to ``$make -f $makefile MAPLE_TARGET=$target``
and ``$make -f $makefile MAPLE_TARGET=$target $file``, respectively.

.. image:: /_static/img/codeblocks_maketargets.png
   :align: center
   :alt: Code::Blocks make targets

Save all these changes, go back to the main IDE window, and try to
build/run. "Build" will compile everything, "Run" will run the upload
script in a terminal window (if there are problems they will flash by
very quickly; you can start Code::Blocks in a terminal window and
check the output in that base window if necessary), and "Rebuild" will
clean before rebuilding.

.. image:: /_static/img/codeblocks_build.png
   :align: center
   :alt: Success!

.. _toolchain-exuberantly:

Go forth exuberantly!
---------------------

Let us know what you come up with! Use #leaflabs on Twitter, post in
the `forum`_, track us down in the real world, whatever. We love
projects!

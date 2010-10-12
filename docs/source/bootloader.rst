.. highlight:: sh

==================
 Maple Bootloader
==================

The firmware which allows the Maple to be reprogrammed via a USB
connection. Every Maple board comes programmed with this by default,
and it is not overwritten by regular programs (it lives lower in the
Flash memory and only runs when the chip is reset).

**Check out the latest source code version:** ::

  git clone git://github.com/leaflabs/maple-bootloader.git

**Visit the github development project**: http://github.com/leaflabs/maple-bootloader

.. contents:: Contents
   :local:

Bootloader Schemes Explained!
-----------------------------

Maple Rev 3 (the version currently shipping) represents a drastic
remake of the core library as well as the upload process. Some of
these changes are aesthetic, refactoring and reorganization. Some are
performance minded. The changes to the bootloader, however, were
implemented to solve some really gritty cross platform issues.  Before
delving in to how the Rev 1 bootloader worked and how the Rev 3
bootloader works now, lets look at the features common to both of them
and touch a bit on the Arduino setup. This is a fairly involved
explanation, with a lot of details that are likely only interesting to
a few. If you just want to get the rough idea, skim this article. If
you want to start hacking on the bootloader, get in touch with us to
get even more info on how this all works.  Of course, you can always
`check out the code at github <http://github.com/leaflabs/libmaple>`_!

Arduino
-------

Arduino is based off of AVR series micro controllers, most of which
lack USB support. Thus, boards like the Duemilanove add USB capability
via an FTDI USB to Serial converter chip. This chip interfaces with
the AVR over…serial. When you plug an Arduino into a computer, only an
FTDI driver is needed. Since the FTDI chip is separate from the AVR,
you can reset the Arduino without closing this USB connection with the
FTDI chip. To program an Arduino, the host machine sends a command
over the USB pipe (reset DTR) which in turn resets the AVR. The AVR
will boot into a bootloader, which waits for a second for any upload
commands over serial. The host machine can either send those commands,
or do nothing. In which case the AVR will quickly jump to user code
and off you go.  The whole process is quick, the bootloader doesn’t
live for very long, and will exit almost immediately if no upload
commands are received.

Maple Rev 1: The Horror...
---------------------------

Maple is based off the STM32 (ARM cortex M3) series chips, which do
have embedded USB support. Thus, Maple doesn’t need the extra FTDI
chip. Firmware is uploaded via the standard DFU protocol (also used by
iPhone and openMoko). Since DFU is a standard, there is no need for
custom software running on the host to upload the firmware. Any DFU
compliant program will work. The maple ide is based around
:command:`dfu-util`, openMoko’s DFU utility. Using DFU came at a cost,
however. The USB port must additionally implement a separate serial
port at the same time (we use the CDC ACM class for serial
functionality).

Maple Rev 1 attempted to run both DFU and CDC ACM devices
simultaneously on the USB peripheral. On Linux, this worked great. The
OS would service the DFU driver during uploads, and the CDC ACM for
serial port transactions. There was no reset necessary for uploads. No
waiting.  The bootloader was always running the background, ready to
receive commands.

The problem was that *only* Linux did this.  Windows refused to attach
more than one driver to a single USB device without repackaging the
DFU and CDC ACM into a single IAD Compound Device. It's not terribly
important what this means, except for two things.

1. Four drivers were necessary to make everything work.
2. IAD is not supported by OS X.

Mac, on the other hand, only supported Compound USB, a different trick
that is not supported by Windows. While a perpetual background
bootloader was attractive, it became clear, after much toiling, we
were going to have to write some custom drivers across several
platforms to make everything work this way.

Maple Rev3
----------

Maple Rev 3 takes a completely different tack, more along the lines of
Arduino.  In Rev 3, the device resets into bootloader mode, which
stays alive for a few moments to receive commands, and then jumps to
user code. The bootloader is implemented as a DFU device -- just a DFU
device, no serial port. This requires one driver for Windows
(:file:`drivers/mapleDrv/dfu` in the Windows IDE directory). As part
of the :ref:`libmaple <libmaple>` library, user code is automatically
supplied with serial support via some behind the scenes work that
happens automatically when you compile (``setupUSB()`` is appended to
``setup()``). This user mode code only implements a CDC ACM class USB
device, giving you functions like ``Usb.print()``. Separating these
two modes fixed the driver issue, required no complicated compound USB
device nonsense, and works well across platforms, requiring only two
drivers (serial and DFU) on Windows.

However, it is no longer possible to upload code at will, since there
is no bootloader quietly listening in the background. Instead you have
to reset the board, then initiate a DFU transaction. This reset is
performed automatically by the IDE by sending a command over the USB
serial port. You can generate this reset on your own using a Python
script or some other scheme. All you need do is:

1. Pulse DTR (high and then low, so that you've created a negative
   edge)
2. Write "1EAF" in ASCII over the serial pipe. This will cause Maple
   to reset. Only the first 4 bytes after a negative edge of DTR are
   checked for this command, so it's important you actually create a
   negative edge, rather than just ensuring DTR is low.

After the reset, the host OS takes a few moments (.5-2 seconds) to
re-enumerate the device as DFU. This delay is unpredictable, and its
the reason the bootloader on Maple Rev3 stays alive for so
long. Sometimes the bootloader was exiting before the OS had even
enumerated the device! Once in bootloader mode, however,
:command:`dfu-util` uploads your sketch into either flash or RAM (DFU
alternate setting 0 or 1, respectively) and resets the board again.
This time, however, no DFU transaction is initiated, and the
bootloader gives way to user code, closing down the DFU pipe and
bringing up the USB serial.

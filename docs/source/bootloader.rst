.. highlight:: sh

.. _bootloader:

Maple Bootloader(s)
===================

The firmware which allows the Maple to be reprogrammed via a USB
connection. Every Maple board comes programmed with this by default,
and it is not overwritten by regular programs (it lives lower in the
Flash memory and only runs when the chip is reset).

**Check out the latest source code version:** ::

  git clone git://github.com/leaflabs/maple-bootloader.git

**Visit the github development project**: https://github.com/leaflabs/maple-bootloader

.. contents:: Contents
   :local:

Bootloader Schemes Explained
----------------------------

Maple Rev 3 and Rev 5 (Rev 5 is the version currently shipping)
represents a drastic remake of the core library as well as the upload
process. Thes changes to the bootloader, were implemented to resolve
platform-specific issues on Windows.  Before delving into how the Rev
1 bootloader worked and how the Rev 5 bootloader works now, we'll
discuss the features common to each and touch a bit on the Arduino
setup.

This is a fairly involved explanation, with a lot of details that are
likely only interesting to a few. If you just want to get the rough
idea, skim this article. If you want to start hacking on the
bootloader, get in touch with us to get even more info on how this all
works.  And finally, you can always `check out the code at github
<https://github.com/leaflabs/libmaple>`_!

Arduino
-------

Arduino is based off of AVR series microcontrollers, most of which
lack USB support. Thus, boards like the Duemilanove add USB capability
via an FTDI USB-to-Serial converter chip. This chip interfaces with
the AVR over an RS-232 serial interface. When you plug an Arduino into
a computer, only an FTDI driver is needed. Since the FTDI chip is
separate from the AVR, you can reset the Arduino without closing this
USB connection with the FTDI chip.

To program an Arduino, the host machine sends a command over the USB
pipe (reset DTR) which in turn resets the AVR. The AVR will boot into
a bootloader, which waits for a second for any upload commands over
serial. The host machine can either send those commands, or do
nothing. If it does nothing, the AVR will quickly jump to user code
and off you go.  The whole process is quick, the bootloader doesn’t
live for very long, and will exit almost immediately if no upload
commands are received.

Maple Rev 1
-----------

Maple is based off the STM32 (ARM cortex M3) series chips, which do
have embedded USB support. Thus, Maple doesn’t need the extra FTDI
chip. Firmware is uploaded via the standard DFU protocol (also used by
iPhone and openMoko). Since DFU is a standard, there is no need for
custom software running on the host to upload the firmware. Any DFU
compliant program will work. The Maple IDE is based around
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

Mac OS X, on the other hand, only supported Compound USB, a different
trick that is not supported by Windows. While a perpetual background
bootloader was attractive, it became clear, after much toiling, we
were going to have to write custom drivers across several platforms to
make everything work this way.

.. _bootloader-rev3:

Maple Rev3/Rev5 - DFU
---------------------

Maple Rev 3 takes a completely different tack, more along the lines of
Arduino.  In Rev 3, the device resets into bootloader mode, which
stays alive for a few moments to receive commands, and then jumps to
user code. The bootloader is implemented as a DFU device -- just a DFU
device, no serial port. This requires one driver for Windows
(:file:`drivers/mapleDrv/dfu` in the Windows IDE directory).

As part of the :ref:`libmaple <libmaple>` library, user code is
automatically supplied with serial support via some behind the scenes
work (``setupUSB()`` is called from ``init()``). This user mode code
only implements a CDC ACM class USB device, giving you functions like
:ref:`SerialUSB.read() <lang-serialusb-read>`. Separating these two
modes fixed the driver issues and works well across platforms,
requiring only two drivers (serial and DFU) on Windows.

However, it is no longer possible to upload code at will, since there
is no bootloader quietly listening in the background. Instead, you
must reset the board, then initiate a DFU transaction. The IDE
performs this reset automatically by performing a special sequence of
changes on the USB serial port:

1. Pulse DTR (high and then low, so that you've created a negative
   edge)
2. Write "1EAF" in ASCII over the serial pipe. This will cause Maple
   to reset. Only the first 4 bytes after a negative edge of DTR are
   checked for this command, so it's important you actually create a
   negative edge, rather than just ensuring DTR is low.

After the reset, the host OS takes a few moments (.5-2 seconds) to
re-enumerate the device as DFU. This delay is unpredictable, and is
the reason the bootloader on Maple Rev 3/Rev 5 stays alive for so
long. (Sometimes, the bootloader was exiting before the OS had even
enumerated the device.)

Once in bootloader mode, :command:`dfu-util` uploads your sketch into
either flash or RAM (DFU alternate setting 0 or 1, respectively) and
resets the board again.  This time, however, no DFU transaction is
initiated, and the bootloader gives way to user code, closing down the
DFU pipe and bringing up the USB serial port.

.. .. _bootloader-rev6:

.. Maple Rev6 - The Serial Bootloader (Tentative)
.. ----------------------------------------------

.. .. note:: This section documents an in-progress version of the Maple
..    bootloader.  **No Maples yet sold use this bootloader protocol**.
..    It has not been yet been publicly released, and its interface is
..    not stable.

.. The bootloader in Rev3/Rev5 works well on Linux, acceptably on Mac,
.. but was unsatisfactory on Windows. Unlike the other operating systems,
.. Windows needed to be manually pointed to both the driver to use for
.. programming (DFU, via `libusb <http://www.libusb.org/>`_) and the
.. driver to use for serial communication (usbser.sys, built in to
.. Windows). Since Maple operates in only one of these modes at a time,
.. driver installation was unnecessarily complicated. It was necessary to
.. bring Maple into the correct mode before installing each of the
.. drivers. Furthermore, because libusb is not bundled with Windows, and
.. its driver is not signed, Windows 7 users have been forced to
.. laboriously disable driver signing checks. Finally, Windows hates the
.. constant switching of the device between Serial and DFU modes (during
.. programming), and often prompts users to install drivers that are
.. already installed. We have therefore decided to abandon DFU.

.. In our new bootloader scheme, Maple is simply a serial device.
.. Windows comes bundled with usbser.sys, so no driver signing is
.. required.  The IDE installation process is greatly simplified, there
.. is no more switching back and forth between "modes", and we can build
.. in new functionality outside the DFU spec.

.. The first incarnation of this serial-only bootloader leaves libmaple
.. and user code untouched. However, during programming, instead of
.. calling :command:`dfu-util` to upload code we will now call a newly
.. written utility script similar to `avr-dude
.. <http://savannah.nongnu.org/projects/avrdude/>`_. The high level
.. operation of the bootloader will remain the same - come on at startup,
.. wait for an upload operation or timeout, and jump to user code.

.. The second version of this bootloader will eliminate this dependence
.. on resetting and timing out by having the bootloader run in the
.. background.  It will additionally own the serial port. In this scheme,
.. sending data over the COM port while DTR is pulled low results in that
.. packet being captured by the bootloader and interpreted as a
.. bootloader command. When the user uploads a new program, the
.. bootloader will overwrite the old one, reset the various peripheral
.. registers, and jump to user code. All of this will occur without
.. resetting the chip and thus causing Maple to connect and disconnect
.. from your computer (which seems to cause many problems).

.. The final version of this bootloader scheme will involve a separate
.. microcontroller, whose responsibilities are to drive the USB port,
.. program the main processor, and offer some amount of debugging
.. capability. This will allow user sketches to run on the bare metal of
.. the main processor, without any bootloader hiding underneath. This
.. approach is similar to the approaches taken by mbed and the Arduino
.. Uno.

.. Regardless of which generation of the new serial bootloader you are
.. working with, the command interface is the same. The low level
.. communication protocol is inspired by STK-500, the protocol used to
.. program many AVR-based development boards. The protocol is a
.. packetized query-response scheme. The host PC initiates every
.. transaction, and for every query sent to the bootloader, a single
.. response will be returned (or the system times out). Data is
.. transmitted over 115.2kbps, 8 data bits, 1 stop bit, no parity
.. bit. Every query or response follows the same packet format that looks
.. like this:

.. .. _bootloader-packet-structure:

.. Packet Structure
.. ^^^^^^^^^^^^^^^^

.. A bootloader packet is composed of a sequence of fields, as follows.

.. .. list-table::
..    :header-rows: 1

..    * - Field
..      - Length (bytes)
..      - Value
..      - Description

..    * - START
..      - 1
..      - 0x1B
..      - Magic constant, indicates bootloader packet

..    * - SEQUENCE_NUM
..      - 1
..      - 0--0xFF
..      - Queries and responses must have the same sequence number; rolls
..        over to 0 after 0xFF

..    * - MESSAGE_SIZE
..      - 2
..      - 0--0xFFFF
..      - Size of message body, currently limited to a 1024B=1KB maximum

..    * - TOKEN
..      - 1
..      - 0x7F
..      - Differs from STK500 value of 0x0E

..    * - MESSAGE_BODY
..      - Variable, determined by MESSAGE_SIZE field
..      - Command query or response
..      - See :ref:`next section <bootloader-commands>`

..    * - CHECKSUM
..      - 4
..      - XOR of all other 32-bit words in packet
..      - See :ref:`below <bootloader-checksum>`

.. .. _bootloader-checksum:

.. .. highlight:: cpp

.. .. note:: When computing the checksum, the words in a packet are
..    interpreted big-endian (as if the packet were a sequence of 32-bit,
..    big-endian unsigned integers).  If the end of the MESSAGE_BODY is
..    not aligned with a four-byte boundary, then the checksum will treat
..    it as if it was padded with zero bytes to a four-byte boundary.

..    As a concrete example, an entire GET_INFO query (see :ref:`below
..    <bootloader-get-info>`), including the packet structure, is
..    comprised of the byte sequence ::

..       {0x1B, 0x7F, 0x00, 0x01, 0x7F, 0x00, 0x64, 0x7F, 0x00, 0x01}

..    The SEQUENCE_NUM of this query is 0x7F.

.. .. highlight:: sh

.. .. _bootloader-commands:

.. Commands
.. ^^^^^^^^

.. The packet structure overhead is for reliability. The actual queries
.. and responses are transacted inside of the message body.  Following
.. the STK-500 protocol, each query or response begins with the single
.. byte command field. For each query, the resultant response must begin
.. with the same CMD byte. For each type of command, the structure of
.. queries and responses is of fixed size.

.. Also following STK-500, fields longer than 1 byte are transmitted MSB
.. first (big-endian). However, READ and WRITE commands operate byte-wise
.. (not word-wise); it is up to the host PC to ensure that alignment and
.. ordering issues are handled appropriately.

.. .. _bootloader-get-info:

.. GET_INFO
.. """"""""

.. Used to query device characteristics.

.. GET_INFO Query:

.. .. list-table::
..    :header-rows: 1

..    * - Field
..      - Bytes
..      - Comments

..    * - GET_INFO
..      - 1
..      - Value 0

.. GET_INFO Response:

.. .. list-table::
..    :header-rows: 1
..    :widths: 4 2 10

..    * - Field
..      - Bytes
..      - Comments

..    * - GET_INFO
..      - 1
..      - Value 0

..    * - Endianness
..      - 1
..      - 0 indicates little-endian, 1 indicates big-endian.
..        (Currently returns 0; this field allows for future
..        expansion).

..    * - Available Ram
..      - 4
..      - In bytes

..    * - Available Flash
..      - 4
..      - In bytes

..    * - Flash Page Size
..      - 2
..      - In bytes

..    * - Starting Address (FLASH)
..      - 4
..      - Usually 0x08005000

..    * - Starting Address (RAM)
..      - 4
..      - Usually 0x200000C0

..    * - Bootloader Version
..      - 4
..      - Current version 0x00060000 (MAJ,MIN)

.. .. _bootloader-erase-page:

.. ERASE_PAGE
.. """"""""""

.. Used to erase flash pages.

.. ERASE_PAGE query:

.. .. list-table::
..    :header-rows: 1
..    :widths: 4 2 10

..    * - Field
..      - Bytes
..      - Comments

..    * - ERASE_PAGE
..      - 1
..      - Value 1

..    * - ADDRESS
..      - 4
..      - Will erase whichever page contains ADDRESS

.. ERASE_PAGE response:

.. .. list-table::
..    :header-rows: 1
..    :widths: 3 2 10

..    * - Field
..      - Bytes
..      - Comments

..    * - ERASE_PAGE
..      - 1
..      - Value 1

..    * - SUCCESS
..      - 1
..      - Either 0 (failure) or 1 (success)

.. WRITE_BYTES
.. """""""""""

.. Used to write to RAM or flash.

.. WRITE_BYTES query:

.. .. list-table::
..    :header-rows: 1
..    :widths: 4 4 10

..    * - Field
..      - Bytes
..      - Comments

..    * - WRITE_BYTES
..      - 1
..      - Value 2

..    * - Starting Address
..      - 4
..      - Can address arbitrary RAM, or :ref:`cleared
..        <bootloader-erase-page>` flash pages.

..    * - DATA
..      - MESSAGE_SIZE - 5
..      - See :ref:`Packet Structure <bootloader-packet-structure>`

.. WRITE_BYTES response:

.. .. list-table::
..    :header-rows: 1
..    :widths: 2 2 10

..    * - Field
..      - Bytes
..      - Comments

..    * - WRITE_BYTES
..      - 1
..      - Value 2

..    * - SUCCESS
..      - 1
..      - Either 0 (failure) or 1 (success). Will fail if writes were
..        made to uncleared pages.  Does not clean up failed writes
..        (memory will be left in an undefined state).

.. READ_BYTES
.. """"""""""

.. Used to read from RAM or flash.

.. READ_BYTES query:

.. .. list-table::
..    :header-rows: 1
..    :widths: 2 2 10

..    * - Field
..      - Bytes
..      - Comments

..    * - READ_BYTES
..      - 1
..      - Value 3

..    * - ADDRESS
..      - 4
..      - Start of block to read.  Must be a multiple of 4.

..    * - LENGTH
..      - 2
..      - Maximum number of bytes to read (currently, this may be at most
..        1024 = 1KB). Must be a multiple of 4.

.. READ_BYTES response:

.. .. list-table::
..    :header-rows: 1
..    :widths: 2 2 10

..    * - Field
..      - Bytes
..      - Comments

..    * - READ_BYTES
..      - 1
..      - Value 3

..    * - DATA
..      - MESSAGE_SIZE - 1
..      - Contains read bytes.  The actual number of bytes read may be
..        less than the LENGTH field of the corresponding READ_BYTES
..        query. If this section is of length 0, this should be
..        interpreted as a read failure. See
..        :ref:`bootloader-packet-structure`.

.. JUMP_TO_USER
.. """"""""""""

.. Causes the bootloader to jump to user code's starting address.

.. JUMP_TO_USER query:

.. .. list-table::
..    :header-rows: 1
..    :widths: 2 1 10

..    * - Field
..      - Bytes
..      - Comments

..    * - JUMP_TO_USER
..      - 1
..      - Value 4

..    * - Location
..      - 1
..      - 0 means jump to flash starting address, 1 means jump to RAM
..        starting address.  See the :ref:`bootloader-get-info` command
..        for more information.

.. JUMP_TO_USER response:

.. .. list-table::
..    :header-rows: 1
..    :widths: 2 1 10

..    * - Field
..      - Bytes
..      - Comments

..    * - JUMP_TO_USER
..      - 1
..      - Value 4

..    * - SUCCESS
..      - 1
..      - Either 0 (failure) or 1 (success).  If successful, after the
..        response is sent, the bootloader ends this session and jumps to
..        the user code in flash or RAM as specified in the query's
..        Location field.


.. SOFT_RESET
.. """"""""""

.. Engages a full software reset.

.. SOFT_RESET query:

.. .. list-table::
..    :header-rows: 1
..    :widths: 2 1 10

..    * - Field
..      - Bytes
..      - Comments

..    * - SOFT_RESET
..      - 1
..      - Value 5

.. SOFT_RESET response:

.. .. list-table::
..    :header-rows: 1
..    :widths: 2 1 10

..    * - Field
..      - Bytes
..      - Comments

..    * - SOFT_RESET
..      - 1
..      - Value 5

..    * - SUCCESS
..      - 1
..      - Either 0 or 1 (FAILED and OK, respectively). Will end this
..        bootloader session and reset the processor.

.. _bootloader-reflashing:

Flashing A Custom Bootloader
----------------------------

.. warning:: This section is for users who want to put a fresh or
   custom bootloader on their board.  It's possible to make a mistake
   in this process and e.g. render your Maple unable to communicate
   with the IDE.  Know what you're doing, and proceed with caution.

The STM32 microprocessor on the Maple comes with a built-in serial
bootloader that can be used to flash a new (software) bootloader onto
the chip.  While the Maple bootloader is just a program, the built-in
serial bootloader is part of the STM32 hardware, so it's always
available.

This means that you can **always** follow these instructions to put a
new bootloader program on your board; it **doesn't matter** if there's
already a copy of the Maple bootloader on it or not.

This section applies to Maple Rev 3 or higher.  If you have a Maple
Rev 1; you don't have a BUT button, and won't be able to follow these
directions.  A workaround is detailed in `this forum posting
<http://forums.leaflabs.com/topic.php?id=32#post-126>`_.

.. highlight:: sh

Setup
^^^^^

In order to follow these instructions, you will need:

- A binary of the bootloader you want to upload
- Hardware for communicating between the Maple and your computer over
  serial.
- `Python <http://python.org>`_ version 2.5 or higher, with the
  `PySerial <http://pyserial.sourceforge.net/>`_ library installed.

**Step 1: Obtain a bootloader binary**. The first thing you'll need to
do is to compile your bootloader binary.  Note that an ASCII
representation of the binary, such as the Intel .hex format, won't
work.

.. FIXME [Mini, Native] links to precompiled bootloaders

If you just want to flash the default Maple bootloader (the one that
was installed on your Maple when it arrived), we host a `pre-compiled
copy
<http://static.leaflabs.com/pub/leaflabs/maple-bootloader/maple_boot-rev3-9c5f8e.bin>`_,
which works on all Maple Revs.

To obtain the latest development version, you can run (on a
:ref:`suitably configured system <unix-toolchain>`) the following to
obtain a binary of the bootloader currently used on the Maple::

    $ git checkout git://github.com/leaflabs/maple-bootloader.git
    $ cd maple-bootloader
    $ make
    $ ls -lh build/maple-boot.bin # this is the compiled bootloader binary

**Step 2: Connect Maple Serial1 to your computer**.
There are a variety of ways of doing this.  We use Sparkfun's `FTDI
breakout boards <http://www.sparkfun.com/products/718>`_, but you
could use another Maple, an Arduino, etc. -- anything that allows your
computer to communicate with the Maple you want to reprogram over a
serial interface.

.. FIXME [Maple-specific values]

If you do use an FTDI breakout board, first make sure your Maple is
disconnected from an external power source, be it battery, USB, or
barrel jack.  Then, connect the FTDI board's TX pin to ``Serial1``\ 's
RX pin (pin 8), FTDI RX to ``Serial1`` TX (pin 7), FTDI ground to
Maple's GND, and its 3.3V pin to Maple's Vin (use the Maple's
silkscreen for help locating these pins).

More information on ``Serial1`` is available :ref:`here
<lang-serial>`.

At this point, you're ready to plug the FTDI board into your computer
(via USB).

**Step 3: Put your Maple into serial bootloader mode**.  Do this by
pressing the RESET button, then *while RESET is held down*, pressing
and holding the BUT button.  Next, *making sure to keep BUT held
down*, release the RESET button and wait for a few seconds before
releasing BUT.

**Step 4: Get stm32loader.py**.  You can download it directly from
`libmaple's github page
<https://github.com/leaflabs/libmaple/raw/master/support/stm32loader.py>`_
(click the link, then save the file somewhere on your system).  If you
have set up the :ref:`Unix toolchain <unix-toolchain>`, it's the file
libmaple/support/stm32loader.py.

Flashing the new Bootloader
^^^^^^^^^^^^^^^^^^^^^^^^^^^

We'll use ``maple_boot.bin`` as the path to the bootloader binary from
Step 1, and ``ser-port`` as the Maple's serial port device file or COM
port.

* On **Linux**, ``ser-port`` will probably be something like
  ``/dev/ttyUSB0``, although the exact number could be different (it
  could be ``/dev/ttyUSB1``, ``/dev/ttyUSB2``, etc.).

* On **OS X**, ``ser-port`` will probably look like
  ``/dev/tty.usbserialXXXX``, where ``XXXX`` is some random string of
  characters.

* On **Windows**, ``ser-port`` will be something like ``COM1``, ``COM2``, etc.

.. highlight:: sh

To upload a bootloader binary, run this command from the Unix shell::

    python stm32loader.py -p ser-port -evw maple_boot.bin

Or this command from the Windows command prompt::

    python.exe stm32loader.py -p ser-port -evw maple_boot.bin

You can also run the following to get usage information::

    # Unix:
    python stm32loader.py -h

    # Windows:
    python.exe stm32loader.py -h

If all goes well, you'll see a bunch of output, then "Verification
OK".  If something goes wrong, the `forum`_ is probably your best bet
for obtaining help, with IRC (server irc.freenode.net, channel
#leafblowers) being another option.  If all else fails, you can always
`contact us directly`_!

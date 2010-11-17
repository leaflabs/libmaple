.. highlight:: sh

=====================
 Maple Bootloader(s)
=====================

.. TODO: [Stub] add a section on flashing your own bootloader

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

Maple Rev 3 and Rev 5 (the version currently shipping) represents a
drastic remake of the core library as well as the upload process. Some
of these changes are aesthetic, refactoring and reorganization. Some
are performance minded. The changes to the bootloader, however, were
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

.. _bootloader-rev3:

Maple Rev3/Rev5
---------------

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

.. _bootloader-rev6:

Maple Rev6 - The Serial Bootloader (Tentative)
----------------------------------------------

The bootloader in Rev3/Rev5 works quite well in linux, it works OK in
Mac, but in windows we had a few major issues. First off, unlike the
other operating systems, Windows needed to be manually pointed to both
the driver to use for programming (DFU, via libusb) and the driver to
use for serial communication (usbser.sys, built in to windows). Maple
operates in only one of these modes at a time, installation has been
quite tricky, involving getting Maple into the right mode and then
installing the driver/inf file during the windows prompt. Furthermore,
because libusb is not bundled with Windows, and its driver is not
signed, users of Windows 7 have been forced to laboriously disable
driver signing checks. Finally, the constant switching of the device
between Serial and DFU modes (during programming) really confuses
windows, often reprompting users to install drivers that are alrady
installed or generally not working well. We have therefore decided to
simplify things greatly, by simply abandoning DFU. In this new
bootloader scheme, Maple is, simply, a serial device. Windows comes
bundled with usbser.sys, so no driver signing is required. The
installation process will be greatly simplified, there will be no more
siwtching back and forth between "modes" and we get the chance to
build in a lot of new functionality that were outside the DFU spec.

The first incarnation of this serial-only bootloader leaves libmaple
and user code untouched. However, during programming, instead of
calling dfu-util to upload code we will now call a newly written
utility script similar to avr-dude used by arduino. The high level
operation of the bootloader will remain the same - come on at startup,
wait for an upload operation or timeout and jump to user code. The
second version of this bootloader will eliminate this dependence on
resetting and timing out by having the bootloader run in the
background all the time, and owning the serial port. In this scheme,
sending data over the COM port while DTR is pulled low results in that
packet being captured by the bootloader and interpreted as a
bootloader command. When the user uploads a new program, the
bootloader will overwrite the old one, reset the various peripheral
registers, and jump to user code. All of this will occur without every
resetting the chip and thus causing Maple to connect and disconnect
from your computer (which seems to cause many problems). The finaly
version of this new bootloader scheme will actually involve a separate
microcontroller, whose responsibilities are to drive the USB port,
program the main processor, and offer some amount of debugging
capability. This will allow user sketches to run on the "bare metal"
of the main processor, without any bootloader hiding underneath your
programs. This approach is similar to the approaches taken by mBed and
the new Arduino UNO.

Regardless of which generation of the new serial bootloader you are
working with, the command interface is the same. The low level
communication protocol is inspired by STK-500, the protocol used to
program Arduino's and many other AVR based development boards. The
protocol is a packetized query-response scheme. The host PC initiates
every transaction, and for every query sent to the bootloader, a
single response will be returned (or the system times out). Data is
transmitted over 115.2kbps, 8 data bits, 1 stop bit, no parity
bit. Every query or response follows the same packet format that looks
like this:

.. _bootloader-packet-structure:

The Packet
^^^^^^^^^^
.. csv-table::
   :header: Field, length (Bytes), value, description

   START, 2, 0x7EAF, A magic constant that indicates this is a
   bootloader packet

   SEQUENCE_NUM, 1, 0-255, Every response must have the same sequence
   number as its query

   MESSAGE_SIZE, 2, 0-65535, Size of the message body\, currently
   messages must be <= 512 Bytes

   MESSAGE_BODY, 0-65535, DATA, Self explanatory

   CHECKSUM, 4, VAL, The XOR of all bytes in the packet except the
   checksum byte

.. _bootloader-commands:

Commands
^^^^^^^^

The packet structure is really just overhead. The actual queries and
responses are transacted inside of the message body. Again following
in the footsteps of STK-500, each query or response begins with the
single byte CMD field. For each query, the resultant response must
begin with the same CMD byte. For each type of CMD, the structure of
queries and responses are well formed and of fixed size. Like STK-500,
fields longer than 1 byte are transmitted MSB first (big
endian). However, READ and WRITE commands operate bytewise (not word
wise), it is up to the host PC to ensure that alignment and ordering
issues are taken care of when appropriate (Maple uses a little endian
processor, LSB first).

.. list-table:: GET_INFO Query
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - GET_INFO
     - 1
     -
\ 

.. list-table:: GET_INFO Response
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - GET_INFO
     - 1
     -

   * - Available Ram
     - 4
     -

   * - Available Flash
     - 4
     -

   * - Flash Page Size
     - 2
     -

   * - Starting Address (FLASH)
     - 4
     - Usually 0x08005000

   * - Starting Address (RAM)
     - 4
     - Usually 0x200000C0

   * - Bootloader Version
     - 4
     - Current version 0x00060000 (MAJ,MIN)

\ 
\  

.. list-table:: ERASE_PAGE Query
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - ERASE_PAGE
     - 1
     - \ 

   * - ADDRESS
     - 4
     - Will erase whichever page contains ADDRESS

\ 

.. list-table:: ERASE_PAGE Response
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - ERASE_PAGE
     - 1
     -
   
   * - SUCCESS?
     - 1
     - Either 0 or 1, (FAILED and OK)

\
\

.. list-table:: ERASE_PAGE Response
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - WRITE_BYTES
     - 1
     - 

   * - Starting Address
     - 4
     - Can only write to RAM or addresses on cleared FLASH pages!

   * - DATA
     - Message Size - 5
     - 

\

.. list-table:: WRITE_BYTES Response
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - WRITE_BYTES
     - 1
     - 
   
   * - SUCCESS?
     - 1
     - Either 0 or 1 (FAILED, OK). Will fail if writes were made to uncleared pages, does not clean up failed writes (memory in unknown state)

\
\

.. list-table:: READ_BYTES Query
   :header-rows: 1

   * - Field
     - Bytes
     - Comments
   
   * - READ_BYTES
     - 1
     - 
 
   * - ADDRESS
     - 4
     - Start of block to read, must be a multiple of 4 (4 byte alignment)

   * - LENGTH
     - 2
     - Number of Bytes to Read (currently 512 byte max, must be a multiple of 4)

\

.. list-table:: READ_BYTES Response
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - READ_BYTES
     - 1
     -

   * - DATA
     - Message Size - 1
     - Returns data, if this section is of length 0, this should be interpreted as a read failure

\
\

.. list-table:: JUMP_TO_USER Query
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - JUMP_TO_USER
     - 1
     -

\

.. list-table:: JUMP_TO_USER Response
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - JUMP_TO_USER
     - 1
     -

   * - SUCCESS
     - 1
     - Either 0 or 1 (FAILED,OK). Will end this bootloader session and jump to user

\
\
    
.. list-table:: SOFT_RESET Query
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - SOFT_RESET
     - 1
     - Will engage a full software reset

\

.. list-table:: SOFT_RESET Response
   :header-rows: 1

   * - Field
     - Bytes
     - Comments

   * - SOFT_RESET
     - 1
     - Will engage a full software 

   * - SUCCESS
     - 1
     - Either 0 or 1 (FAILED,OK). Will end this bootloader session and reset the processor

\
\

.. highlight:: cpp

.. _timers:

Timers
======

.. FIXME [0.0.10] links to systick.h in a few places on this page

There are four general purpose timers in the Maple microcontroller
that can be configured to generate periodic or delayed events with
minimal work done by the microcontroller. For example, the :ref:`PWM
<pwm>` channels can generate regular square-wave signals on specific
output pins without consuming extra clock cycles. By attaching
interrupt handlers to these channels (instead of just changing the
voltage on an external pin), more complex events can be scheduled.

.. contents:: Contents
   :local:

Introduction
------------

.. _timers-prescale:

The four timers each have four separate compare channels. Each channel
has an associated 16-bit counter that can be configured with a 16-bit
prescaler and a 16-bit overflow value.  The prescaler determines how
fast the counter changes, while the overflow value determines when it
gets reset.

The prescaler acts as a divider of the 72MHz system clock.  That is,
with a prescaler of 1, the channel's counter increments with a
frequency of 72MHz, rolling over (passing the maximum 16-bit unsigned
integer value of 65,535) more than a thousand times a second.  With a
prescaler of 7200, it has a frequency of (72/7200) MHz = 10 KHz,
rolling over approximately every 6.55 seconds.

The overflow value is the maximum value the counter will go up to. It
defaults to the full 65,535; smaller values will cause the counter to
reset to zero more frequently.

Whenever a channel's counter reaches its overflow value, an "update
event" interrupt is generated.  You can configure the Maple to notify
you when this takes place, by registering an interrupt handler, which
is a function that will be called when the update event occurs.

By default, different compare values only change the relative offsets
between events on a single timer ("phase").  They don't control the
frequency with which they occur.  However, a common trick is to
increment the compare value manually in the interrupt handler so that
the event will fire again after the increment period.  There can be a
different increment value for each channel, so this trick allows
events to be programmed at 4 different rates on a single timer.  Note
that function call overheads mean that the smallest increment rate is
at least a few microseconds.

Function Reference
------------------

* :ref:`HardwareTimer <lang-hardwaretimer>`

Caveats
-------

Working with timers and interrupts can be tricky; they are a somewhat
"advanced" topic.  The following subsections explain some common
problems associated with using timers and timer interrupts.

In general: start simple, test with :ref:`ASSERT() <language-assert>`,
and don't try to do too much in your interrupt handlers!  Make sure
that what you're trying to do in a handler isn't going to block other
interrupts from firing, if those other interrupts are important for
your program.

.. _timers-pwm-conflicts:

PWM Conflicts
^^^^^^^^^^^^^

Because PWM functionality on a given pin depends on
the configuration of the timer and channel, you must chose your
channels carefully if you want to use both timer interrupts and PWM in
the same program.  Refer to your board's :ref:`Timer Pin Map
<gpio-pin-maps>` to match up timer channels and pin numbers.

Overhead
^^^^^^^^

There is some overhead associated with function and interrupt calls
(loading and unloading the stack, preparing state, etc.) and this
overhead can fudge your timing. Imperfect code branching also means
that, e.g., channel 1 interrupts may get called a couple clock cycles
sooner than a channel 4 interrupt, all other configuration being the
same.

Jitter
^^^^^^

Other interrupts can and will get called before or during the timer
interrupt routines, causing pseudorandom delays and other
frustrations.

Disabling the :ref:`USB <usb>` port (by calling ``SerialUSB.end()``,
or just running off a battery) helps a lot, but then you lose the
auto-reset and communications functionality.  This will require that
you put your Maple into :ref:`perpetual bootloader mode
<troubleshooting-perpetual-bootloader>` before uploading a new program
to it (or somehow causing your program to re-enable serial over USB
using :ref:`SerialUSB.begin() <lang-serialusb-begin>`).

The SysTick peripheral another way to perform periodic or delayed
events.  Its separate timer does not conflict with any other
peripherals, but the associated 1 kHz interrupt can jitter the general
purpose timer interrupts.  The SysTick peripheral can be disabled by
calling :ref:`systick_disable() <libmaple-systick_disable>`, and
re-enabled using :ref:`systick_resume() <libmaple-systick_resume>`.
However, be aware that calling ``systick_disable()`` will stop the
values coming from :ref:`lang-micros` and :ref:`lang-millis` from
increasing.

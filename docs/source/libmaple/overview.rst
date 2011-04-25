.. highlight:: c

.. _libmaple-overview:

Overview
========

This page is a general overview of the low-level aspects of libmaple
proper.  It provides a general perspective of the library's goals and
design.  Examples are given from the libmaple sources.

.. contents:: Contents
   :local:

Design Goals
------------

The central goal of the libmaple project is to provide a pleasant,
consistent set of interfaces for dealing with the various peripherals
on the STM32 line.

Let's start with the basics. If you're interested in low-level details
on the STM32, then you're going to spend a lot of quality time wading
through `ST RM0008
<http://www.st.com/stonline/products/literature/rm/13902.pdf>`_.
RM0008 is the single most important tool in your toolbox.  It is the
authoritative documentation for the capabilities and low-level
programming interfaces of ST's line of ARM Cortex M3 microcontrollers.

Perhaps you haven't read it in detail, but maybe you've at least
thumbed through a few of the sections, trying to gain some
understanding of what's going on.  If you've done that (and if you
haven't, just take our word for it), then you know that underneath the
covers, *everything* is controlled by messing with bits in the
seemingly endless collections of registers specific to every
peripheral.  The `USARTs <http://leaflabs.com/docs/usart.html>`_ have
data registers; (some of the) the `timers
<http://leaflabs.com/docs/timers.html>`_ have capture/compare
registers, the `GPIOs <http://leaflabs.com/docs/gpio.html>`_ have
output data registers, etc.

For the most part, Wirish does everything it can to hide this truth
from you.  That's because when you really just want to get your robot
to fly, your LEDs to blink, or your `FM synthesizer
<https://github.com/Ixox/preen>`_ to, well, `synthesize
<http://xhosxe.free.fr/IxoxFMSynth.mp3>`_, you probably couldn't care
less about messing with registers.

That's fine!  In fact, it's our explicit goal for Wirish to be good
enough that most people never need to know libmaple proper even
exists.  We want to make programming our boards as easy as possible,
after all.  But the day may come when you want to add a library for an
as-yet unsupported peripheral, or you want to do something we didn't
anticipate, or you'd like to squeeze a little more speed out of a
critical section in your program.  Or maybe you're just curious!

If anything in the above paragraph describes you, then you'll find
that you need a way to translate your knowledge of RM0008 into
software.  We imagine (if you're anything like us) you want to spend
the least amount of time you possibly can doing that
translation. Ideally, once you've finished your design, you want some
way to start reading and writing code right away, without having to
bushwhack your way through a thicket of clunky APIs.

The central abstractions we've chosen to accomplish the above goals
are *register maps* and *devices*.  Register maps are just structs
which encapsulate the layout of the IO-mapped memory regions
corresponding to a peripheral's registers.  Devices encapsulate a
peripheral's register map as well as any other necessary information
needed to operate on it.  Peripheral support routines generally
operate on devices rather than register maps.

Devices
-------

At the highest level, you'll be dealing with *devices*, where a
"device" is a general term for any particular piece of hardware you
might encounter.  So, for example, an analog to digital converter is a
device.  So is a USART.  So is a GPIO port.  In this section, we'll
consider some hypothetical "xxx" device.

The first thing you need to know is that the header file for dealing
with xxx devices is, naturally enough, called ``xxx.h``.  So if you
want to interface with the :ref:`ADCs <adc>`, just ``#include
"adc.h"``.

Inside of ``xxx.h``, there will be a declaration for a ``struct
xxx_dev`` type.  This type encapsulates all of the information we keep
track of for that xxx.  So, for example, in ``adc.h``, there's a
``struct adc_dev``::

    /** ADC device type. */
    typedef struct adc_dev {
        adc_reg_map *regs; /**< Register map */
        rcc_clk_id clk_id; /**< RCC clock information */
    } adc_dev;

The ADCs aren't particularly complicated.  All we keep track of for an
ADC device is a pointer to its register map (which keeps track of all
of its registers' bits; see :ref:`below <libmaple-overview-regmaps>`
for more details), and an identifying piece of information which tells
the RCC (reset and clock control) interface how to turn the ADC on and
reset its registers to their default values.

The timers on the STM32 line are more involved than the ADCs, so a
``timer_dev`` has to keep track of a bit more information::

    /** Timer device type */
    typedef struct timer_dev {
        timer_reg_map_union regs;
        rcc_clk_id clk_id;
        timer_type type;
        voidFuncPtr handlers[];
    } timer_dev;

However, as you can see, both ADC and timer devices are named
according to a single scheme, and store similar information.

``xxx.h`` will also declare pointers to the actual devices you need to
deal with, called ``XXX1``, ``XXX2``, etc. (or just ``XXX``, if
there's only one) [#fgpio]_.  For instance, on the Maple's
microcontroller (the STM32F103RBT6), there are two ADCs.
Consequently, in ``adc.h``, there are declarations for dealing with
ADC devices one and two::

    extern const adc_dev *ADC1;
    extern const adc_dev *ADC2;

In general, each device needs to be initialized before it can be used.
libmaple provides this initialization routine for each peripheral
``xxx``; its name is ``xxx_init()``.  These initialization routines
turn on the clock to a device, and restore its register values to
their default settings.  Here are a few examples::

    /* From dma.h */
    void dma_init(dma_dev *dev);

    /* From gpio.h */
    void gpio_init(gpio_dev *dev);
    void gpio_init_all(void);

Note that, sometimes, there will be an additional initialization
routine for all available peripherals of a certain kind.

Many peripherals also need additional configuration before they can be
used.  These functions are usually called something along the lines of
``xxx_enable()``, and often take additional arguments which specify a
particular configuration for the peripheral.  Some examples::

    /* From usart.h */
    void usart_enable(usart_dev *dev);

    /* From i2c.h */
    void i2c_master_enable(i2c_dev *dev, uint32 flags);

After you've initialized, and potentially enabled, your peripheral, it
is now time to begin using it.  The file ``xxx.h`` contains other
convenience functions for dealing with xxx devices.  For instance,
here are a few from ``adc.h``::

    void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate);
    uint32 adc_read(const adc_dev *dev, uint8 channel);

We aim to enable libmaple's users to interact with peripherals through
devices as much as possible, rather than having to break the
abstraction and consider individual registers.  However, there will
always be a need for low-level access.  To allow for that, libmaple
provides *register maps* as a consistent set of names and abstractions
for dealing with registers and their bits.

.. _libmaple-overview-regmaps:

Register Maps
-------------

A *register map* is just a C struct which names and provides access to
a peripheral's registers.  These registers are usually mapped to
contiguous regions of memory (though at times unusable or reserved
regions exist between a peripheral's registers).  Here's an example
register map, from ``dac.h`` (``__io`` is just libmaple's way of
saying ``volatile`` when referring to register values)::

    /** DAC register map. */
    typedef struct dac_reg_map {
        __io uint32 CR;      /**< Control register */
        __io uint32 SWTRIGR; /**< Software trigger register */
        __io uint32 DHR12R1; /**< Channel 1 12-bit right-aligned data
                                  holding register */
        __io uint32 DHR12L1; /**< Channel 1 12-bit left-aligned data
                                  holding register */
        __io uint32 DHR8R1;  /**< Channel 1 8-bit left-aligned data
                                  holding register */
        __io uint32 DHR12R2; /**< Channel 2 12-bit right-aligned data
                                  holding register */
        __io uint32 DHR12L2; /**< Channel 2 12-bit left-aligned data
                                  holding register */
        __io uint32 DHR8R2;  /**< Channel 2 8-bit left-aligned data
                                  holding register */
        __io uint32 DHR12RD; /**< Dual DAC 12-bit right-aligned data
                                  holding register */
        __io uint32 DHR12LD; /**< Dual DAC 12-bit left-aligned data
                                  holding register */
        __io uint32 DHR8RD;  /**< Dual DAC 8-bit left-aligned data holding
                                  register */
        __io uint32 DOR1;    /**< Channel 1 data output register */
        __io uint32 DOR2;    /**< Channel 2 data output register */
    } dac_reg_map;


There are two things to notice here.  First, if RM0008 names a
register ``DAC_FOO``, then ``dac_reg_map`` has a field named ``FOO``.
So, the Channel 1 12-bit right-aligned data register (RM0008:
DAC_DHR12R1) is the ``DHR12R1`` field in a ``dac_reg_map``.  Second,
if RM0008 describes a register as "Foo bar register", the
documentation for the corresponding field has the same description.
This consistency makes it easy to search for a particular register,
and, if you see one used in a source file, to feel sure about what's
going on just based on its name.

So let's say you've included ``xxx.h``, and you want to mess with some
particular register.  What's the name of the ``xxx_reg_map`` variable
you want?  That depends on if there's more than one xxx or not.  If
there's only one xxx, then libmaple guarantees there will be a
``#define`` that looks like like this::

    #define XXX_BASE                    ((xxx_reg_map*)0xDEADBEEF)

That is, you're guaranteed there will be a pointer to the (only)
``xxx_reg_map`` you want, and it will be called
``XXX_BASE``. (``0xDEADBEEF`` is the register map's *base address*, or
the fixed location in memory where the register map begins).  Here's a
concrete example from ``dac.h``::

    #define DAC_BASE                    ((dac_reg_map*)0x40007400)

How can you use these?  This is perhaps best explained by example.  

* In order to write 2048 to the channel 1 12-bit left-aligned data
  holding register (RM0008: DAC_DHR12L1), you could write::

      DAC_BASE->DHR12L1 = 2048;

* In order to read the DAC control register, you could write::

      uint32 cr = DAC_BASE->CR;

The microcontroller takes care of converting reads and writes from a
register's IO-mapped memory regions into reads and writes to the
corresponding hardware registers.

That covers the case where there's a single xxx peripheral.  If
there's more than one (say, if there are *n*), then ``xxx.h`` provides
the following::

    #define XXX1_BASE                   ((xxx_reg_map*)0xDEADBEEF)
    #define XXX2_BASE                   ((xxx_reg_map*)0xF00DF00D)
    ...
    #define XXXn_BASE                   ((xxx_reg_map*)0x13AF1AB5)

Here's a concrete example from ``adc.h``::

    /** ADC1 register map base pointer. */
    #define ADC1_BASE               ((adc_reg_map*)0x40012400)
    /** ADC2 register map base pointer. */
    #define ADC2_BASE               ((adc_reg_map*)0x40012800)
    /** ADC3 register map base pointer. */
    #define ADC3_BASE               ((adc_reg_map*)0x40013C00)

In order to read from the ADC1's regular data register (where the
results of ADC conversion are stored), you might write::

      uint32 converted_result = ADC1->DR;

Register Bit Definitions
------------------------

In ``xxx.h``, there will also be a variety of #defines for dealing
with interesting bits in the xxx registers, called *register bit
definitions*.  These are named according to the scheme
``XXX_REG_FIELD``, where "``REG``" refers to the register, and
"``FIELD``" refers to the bit or bits in ``REG`` that are special.

.. TODO image of the bit layout of a DMA_CCR register

Again, this is probably best explained by example.  Each Direct Memory
Access (DMA) controller's register map has a certain number of channel
configuration registers (RM0008: DMA_CCRx).  In each of these channel
configuration registers, bit 14 is called the ``MEM2MEM`` bit, and
bits 13 and 12 are the priority level (``PL``) bits.  Here are the
register bit definitions for those fields::

    /* From dma.h */

    #define DMA_CCR_MEM2MEM_BIT             14
    #define DMA_CCR_MEM2MEM                 BIT(DMA_CCR_MEM2MEM_BIT)
    #define DMA_CCR_PL                      (0x3 << 12)
    #define DMA_CCR_PL_LOW                  (0x0 << 12)
    #define DMA_CCR_PL_MEDIUM               (0x1 << 12)
    #define DMA_CCR_PL_HIGH                 (0x2 << 12)
    #define DMA_CCR_PL_VERY_HIGH            (0x3 << 12)

Thus, to check if the ``MEM2MEM`` bit is set in DMA controller 1's
channel configuration register 2 (RM0008: DMA_CCR2), you can write::

    if (DMA1_BASE->CCR2 & DMA_CCR_MEM2MEM) {
        /* MEM2MEM is set */
    }

Certain register values occupy multiple bits.  For example, the
priority level (PL) of a DMA channel is determined by bits 13 and 12
of the corresponding channel configuration register.  As shown above,
libmaple provides several register bit definitions for masking out the
individual PL bits and determining their meaning.  For example, to
check the priority level of a DMA transfer, you can write::

    switch (DMA1_BASE->CCR2 & DMA_CCR_PL) {
    case DMA_CCR_PL_LOW:
        /* handle low priority case */
    case DMA_CCR_PL_MEDIUM:
        /* handle medium priority case */
    case DMA_CCR_PL_HIGH:
        /* handle high priority case */
    case DMA_CCR_PL_VERY_HIGH:
        /* handle very high priority case */
    }

Of course, before doing that, you should check to make sure there's
not already a device-level function for performing the same task!

What Next?
----------

After you've read this page, you can proceed to the :ref:`libmaple API
listing <libmaple-apis>`.  From there, you can read documentation and
follow links to the current source code for those files on `libmaple's
Github page <https://github.com/leaflabs/libmaple>`_.

.. rubric:: Footnotes

.. [#fgpio] For consistency with RM0008, GPIO ports are given letters
            instead of numbers (``GPIOA`` and ``GPIOB`` instead of
            ``GPIO1`` and ``GPIO2``, etc.).

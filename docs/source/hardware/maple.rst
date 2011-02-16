.. highlight:: sh

.. _hardware-maple:

Maple
=====

.. contents:: Contents
   :local:

.. _maple-hardware-identify-rev:

Identifying your Rev
--------------------

We went through three versions ("Revs") of the Maple hardware: Rev 1,
Rev 3, and Rev 5 [#frev2_4]_; Rev 5, the final design, is currently on
sale.  The following sections will help you to help you identify your
Rev.  Known issues are listed in the :ref:`errata <errata>`.

Rev 1
^^^^^

A small number of Maple Rev 1 boards went on sale in late 2009.  They
have a light red silkscreen and a single pixelated leaf as a logo.

.. figure:: /_static/img/maple_rev1.png
   :align: center
   :alt: Maple Rev 1

Rev 3
^^^^^

This batch of boards went on sale beginning in May 2010. They have a
darker red silkscreen and the "infinity leaf" logo.  The Maple Rev 3
was the first version which includes the built-in button, labeled BUT.
It also includes a built-in LiPo battery charger.

.. figure:: /_static/img/maple_rev3.png
   :align: center
   :alt: Maple Rev 3

Rev 5
^^^^^

These boards went on sale in November 2010.  They have white buttons,
and "r5" in small print near the "LeafLabs Maple" text next to the
"infinity leaf" logo.  The Maple Rev 5 repositioned the double header
on the right hand side to better fit 0.1 inch pitch breadboard.  This
necessitated the removal of pins 21 and 22 from the double header;
they are still available, but don't have any headers installed on
them.

.. figure:: /_static/img/maple_rev5.png
   :align: center
   :alt: Maple Rev 5

.. _hardware-maple-powering:

Powering the Maple
------------------

The Maple's power source is determined by the header to the left of
the "LeafLabs" label on the silkscreen.  All versions of the Maple can
be powered from the barrel jack connector, USB, or a LiPo battery.  We
ship the Maple with a jumper on the USB selector.  In order to power
it off of an alternative source, unplug the Maple, then move the
jumper to the desired selector before reconnecting power.

You can also power the Maple via the pin labeled "Vin" on the lower
header.  However, don't do this while simultaneously powering the
Maple from another source, or you could damage the board.

Using the Built-in Battery Charger
----------------------------------

Maples Rev 3 and Rev 5 also have a built-in LiPo battery charger.  In
order to use it, put a jumper across the CHRG header on the power
selection header and across the USB, or EXT selectors, depending on
whether you're charging the battery via USB cable or barrel jack
connector.  The LED labeled CHRG will light up while the battery is
being charged.  When the battery is finished charging, the LED labeled
DONE will also light up.

Hardware Design Files
---------------------

The hardware schematics and board layout files are available in the
`Maple github repository <https://github.com/leaflabs/maple>`_.  The
design files for Rev 1, Rev 3, and Rev 5 are respectively in the
``maple-r1``, ``maple-r3``, and ``maple-r5`` subdirectories.  A
schematic for a JTAG adapter suitable for use with Maple is available
in the ``jtagadapter`` directory.

From the github repository main page, you can download the entire
repository by clicking the "Download" button.  If you are familiar
with `git <http://git-scm.com/>`_, you can also clone the repository
at the command line with ::

    $ git clone git://github.com/leaflabs/maple.git

.. rubric:: Footnotes

.. [#frev2_4] Revs 2 and 4 were prototypes that didn't pass internal
   testing.


.. highlight:: sh

.. _libmaple:

``libmaple`` Reference
======================

.. image:: /_static/img/libmaple-screenshot-small.png
   :align: center
   :alt: libmaple screenshot

`LeafLabs libmaple <libmaple-libmaple>`_ is the low level library we
have developed for for the ARM Cortex-M3 chips manufactured by
STMicroelectronics used in the Maple boards (the `STM32F103x`_
series). We found the generic peripheral libraries too painful to
build on top of, and reimplemented the functionality we needed in a
simpler (and less general) form.

.. _libmaple-libmaple: http://github.com/leaflabs/libmaple
.. _STM32F103x: http://www.st.com/stonline/stappl/productcatalog/app?path=/pages/stcom/PcStComPartNumberSearch.searchPartNumber&search=stm32f103

This library is transparently included in the `Maple IDE
<http://leaflabs.com/docs/maple-ide/>`_, but we develop it separately
using good old Unix command line tools and release it for advanced
users who might chafe at the "sketch" programming model of the
IDE. Included are some examples, a Makefile, and the compatibility
wrappers and code to imitate the Arduino programming library.

**Check out the latest source**::

    git clone git://github.com/leaflabs/libmaple.git

**Table of contents:**

.. toctree::
   :maxdepth: 2

   Unix Toolchain Quickstart <unix-toolchain>
   Guide to using GCC's ARM target <arm-gcc>

.. TODO LATER create, style, and host a pure Doxygen libmaple
.. reference docs.  This implies determining a stable API.

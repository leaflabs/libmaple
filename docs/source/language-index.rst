.. _language-index:

=======================
Complete Language Index
=======================

This is the index of Maple's :ref:`language reference
<language-lang-docs>` documentation.  The "Maple API" column provides
API references for documented libmaple functionality. The "C++ for
Maple" pages are intended as a minimal reference/refresher for
programmers familiar with the Arduino language.

.. admonition:: **Looking for Something Else?**

   - See the :ref:`libraries` for extra built-in libraries for dealing
     with different kinds of hardware.

   - If you're looking for something from the C standard library (like
     ``atoi()``, for instance): the :ref:`CodeSourcery GCC compiler
     <arm-gcc>` used to compile your programs is configured to link
     against `newlib <http://sourceware.org/newlib/>`_, and allows the
     use of any of its header files.  However, dynamic memory allocation
     (``malloc()``, etc.) is not available.

   - If you're looking for pointers to low-level details, see the
     :ref:`Language Recommended Reading
     <language-recommended-reading>` and :ref:`libmaple` pages.

.. _index-language-index-cpp:
.. _index-language-index-api:

+----------------------------------+------------------------------------+
|   Maple API                      |   C++ for Maple                    |
|                                  |                                    |
+==================================+====================================+
|                                  |                                    |
|  .. toctree::                    |  .. toctree::                      |
|     :maxdepth: 1                 |     :maxdepth: 1                   |
|     :glob:                       |     :glob:                         |
|                                  |                                    |
|     lang/api/*                   |     lang/cpp/*                     |
|                                  |                                    |
+----------------------------------+------------------------------------+

.. Unimplemented or not part of current release:

.. toctree::
   :hidden:

   lang/unimplemented/tone.rst
   lang/unimplemented/notone.rst
   lang/unimplemented/pulsein.rst
   lang/unimplemented/stringclass.rst
   lang/unimplemented/stringobject.rst

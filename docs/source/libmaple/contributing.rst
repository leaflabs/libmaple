.. _libmaple-contributing:

Contributing to libmaple
========================

First of all, thanks!  Community contributions are what makes open
source great.

If your patch is minor (you've found a typo, you've added a new
function, etc.), feel free to just make a `forum post
<http://forums.leaflabs.com>`_ describing your changes.

If your changes are larger (you wrote a new library, you added support
for a new peripheral, etc.), we'd prefer you submit a pull request on
Github or send us a nicely-formatted patch via email.

.. contents:: Contents
   :local:

.. _libmaple-faq-patches-preparing:

Preparing Your Patch
--------------------

Before submitting a patch, please make sure it complies with the
:ref:`coding standard <libmaple-coding-standard>`.  Consistent style throughout
the source tree is an important implementation objective for us, and a
patch that doesn't comply with the coding standard we've set forth is
likely to be sent back until it follows the standard.

We would prefer if you release each new file you submit under the `MIT
license <http://www.opensource.org/licenses/mit-license.php>`_. See
e.g. `bkp.h
<https://github.com/leaflabs/libmaple/blob/master/libmaple/bkp.h#L1>`_
for an example, and the coding standard for more details.  Code
released under the `Lesser GPL
<http://www.gnu.org/copyleft/lesser.html>`_ may be accepted for
Wirish, but will almost certainly be rejected for libmaple proper.  We
will not accept patches released under the `GPL
<http://www.gnu.org/licenses/gpl.html>`_. 

**We're not against the GPL**!  It just doesn't suit our purposes for
libmaple.  If you're interested in a GPLed library for ST
microcontrollers, check out `libopenstm32
<http://www.hermann-uwe.de/blog/libopenstm32-a-free-software-firmware-library-for-stm32-arm-cortex-m3-microcontrollers>`_.
Also note that :ref:`libraries <libraries>` released under the GPL are
fine, we just don't want any core libmaple or Wirish code to be GPLed.

.. _libmaple-faq-patches-github:

Submitting Via Github Pull Request (Preferred)
----------------------------------------------

The most convenient way for you to contribute patches is to submit a
pull request on `Github <https://github.com>`_.  Github provides
excellent code review interfaces, which will make it easy for us at
LeafLabs to communicate with you (and each other) about your patch.
It also makes it easy for us to merge your patch into the libmaple
source tree when the time comes.

The steps to submit a pull request are as follows:

1. If you don't already have one, get a `Github account
   <https://github.com/plans>`_ (free).

2. Fork libmaple, then clone your fork to the computer you code on.
   Github provides detailed instructions on `forking and cloning a
   repository <http://help.github.com/fork-a-repo/>`_.

3. Push your commits to your Github libmaple fork (see instructions
   linked in Step 2 for a step-by-step walkthrough on how to do this).

4. `Submit a pull request <http://help.github.com/pull-requests/>`_ to
   the LeafLabs version of libmaple.

.. _libmaple-faq-patches-email:

Submitting Via Email
--------------------

If you're unfamiliar with Git or would prefer not to use Github, you
can always send us a patch via email at info@leaflabs.com.  We'd love
it if you used the `Linux kernel patch format
<http://linux.yyz.us/patch-format.html>`_, but please at least include
the following information in your email:

1. How you generated your patch (arguments to ``diff``, etc.)

2. What git branch/commit or libmaple version your patch applies to

3. A one-line summary of your changes, along with any other details
   you think we should know.

4. A sign-off line certifying your `developer certificate of origin
   <http://elinux.org/Developer_Certificate_Of_Origin>`_.

That said, we'd really prefer a pull request.  If you'd like to learn
more about Git, we recommend the following resources:

* `The Git Community Book <http://book.git-scm.com/index.html>`_: A
  collaboratively edited book on Git.

* `Pro Git <http://progit.org/book/>`_: despite its title, this is a
  fairly beginner-friendly source of information.

* `Understanding Git Conceptually
  <http://www.eecs.harvard.edu/~cduan/technical/git/>`_: a good,
  introductory tutorial on Git's fundamental concepts.

* `Git for Computer Scientists
  <http://eagain.net/articles/git-for-computer-scientists/>`_: if
  you're comfortable with directed acyclic graphs, this resource
  explains Git's functionality in graph-theoretic terms.

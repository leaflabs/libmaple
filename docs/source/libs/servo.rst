.. highlight:: cpp

.. _libs-servo:

=======
 Servo
=======

This documents the Servo library for controlling RC servomotors.  It
is implemented as a thin layer over the built-in :ref:`timer
peripherals <timers>`.

You can use this library in the :ref:`IDE <ide>` by choosing the Servo
item under the Sketch > Import Library... menu.

If you are using the :ref:`Unix toolchain <unix-toolchain>`, the
library is located in ``$LIB_MAPLE_HOME/libraries/Servo/``.

Servo Class Reference
---------------------

You can construct a Servo object by including the declaration ::

     Servo servo;

in your sketch.  This will create a Servo object called ``servo``.
You can then use any of its methods; for instance, to control a
servomotor attached to pin 9, you could write ::

     servo.attach(9);

.. cpp:class:: Servo

   Class for controlling RC servomotors via :ref:`timers <timers>`.

.. _libs-servo-attach:

.. cpp:function:: bool Servo::attach(uint8 pin, uint16 min, uint16 max)

   Attach this Servo object to the given ``pin``.  The pin must be
   capable of PWM.  You can check this by seeing if "PWM" is written
   next to its number on the Maple silkscreen, or by consulting the
   :ref:`pwmWrite() <lang-pwmwrite>` documentation.

   Sets this pin's :ref:`mode <lang-pinmode>` to :ref:`PWM
   <lang-pinmode-wiringpinmode>`, and returns true if successful.
   Does nothing and returns false if the pin doesn't support PWM.

   Parameter ``min`` is the pulse width corresponding to 0 degrees;
   ``max`` is the pulse width corresponding to 180 degrees (both are
   in microseconds).

.. cpp:function:: bool Servo::attach(uint8 pin)

   Equivalent to :ref:`attach(pin, 544, 2400) <libs-servo-attach>`.

.. _libs-servo-attached:

.. cpp:function:: int Servo::attached() const

   If currently attached (via :ref:`attach() <libs-servo-attach>`) to
   a pin, returns that pin's number.  Returns ``NOT_ATTACHED``
   otherwise.

.. cpp:function:: bool Servo::detach()

   If this Servo object is currently attached to pin, stops driving
   the servo by setting a zero pulse width (this is accomplished by
   setting the associated :ref:`channel mode
   <lang-hardwaretimer-setchannelmode>` to ``TIMER_DISABLED``).

   Subsequently, calling :ref:`attached() <libs-servo-attached>` will
   return ``NOT_ATTACHED``.

.. cpp:function:: void Servo::write(unsigned int value)

   If ``value`` is less than ``SERVO_MAX_WRITE_ANGLE`` (which, for
   Arduino compatibility, is 200), it's interpreted as an angle in
   degrees.  Otherwise, it's treated as a pulse width in microseconds.

   Drives the servo to target the given angle, based on a linear
   interpolation of the ``min`` and ``max`` pulse widths determined
   when :ref:`attach() <libs-servo-attach>` was called.

   Be aware that some (especially lower-cost) servos have fairly
   non-linear maps between pulse width and target angle.  Make sure to
   test your motor before relying on this method.

.. cpp:function:: void Servo::writeMicroseconds(uint16 pulseWidth)

   Drives the servo using a ``pulseWidth``-microsecond pulse.

   If ``pulseWidth`` is outside of the [``min``, ``max``\ ] pulse
   width range set during :ref:`attach() <libs-servo-attach>`, it will
   be clamped to lie in this range.

.. cpp:function:: int Servo::read() const

   Returns the servo's target angle, in degrees.  This will be clamped
   to lie between 0 (when the pulse width is at most ``min``) and 180
   (when the pulse width is at least ``max``).

.. cpp:function:: uint16 Servo::readMicroseconds() const

   Returns the pulse width of the wave currently driving the servo, in
   microseconds.  This will be clamped to lie in the [``min``,
   ``max``\ ] pulse width range set during :ref:`attach()
   <libs-servo-attach>`.

#!/usr/bin/python

import serial
import time

ser = serial.Serial('/dev/ttyACM0', baudrate=115200)
ser.open()

# pull dtr and rts low
ser.setRTS(0)
ser.setDTR(0)

# toggle DTR
ser.setDTR(1)

# Some versions of python seem to throw an IOError on this line.
# I have no idea why and don't have any time to look at it.
# Just catch it for now.
#
# Error msg:
#
# Traceback (most recent call last):
#   File "./reset.py", line 15, in <module>
#     ser.setDTR(0)
#   File "/usr/lib/python2.6/dist-packages/serial/serialposix.py", line 388, in setDTR
#     fcntl.ioctl(self.fd, TIOCMBIC, TIOCM_DTR_str)
# IOError: [Errno 84] Invalid or incomplete multibyte or wide character

try:
   ser.setDTR(0)
except IOError:
   print "IOError caught"

# close
ser.close()

time.sleep(1)

print "Done"

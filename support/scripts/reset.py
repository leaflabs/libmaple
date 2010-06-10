#!/usr/bin/python

import serial
import os
from struct import pack
try:
    ser = serial.Serial('/dev/maple', baudrate=115200)
    ser.open()

    # try to toggle DTR/RTS (old scheme)
    ser.setRTS(0)
    ser.setDTR(0)
    ser.setDTR(1)
    ser.setDTR(0)

    # try magic number
    ser.setRTS(1)
    ser.setDTR(1)
    ser.setDTR(0)
    ser.write("1EAF")

    # ok we're done here
    ser.close()

except:
    print "Failed to open the serial port for reset, perhaps this is your first upload or the board was already in bootloader mode"


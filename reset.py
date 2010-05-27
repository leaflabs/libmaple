#!/usr/bin/python

import serial
import os

try:
    highest = 0
    # this totally won't work on Mac OSX! /dev/ttySOMETHINGELSE?
    for f in filter(lambda x: x.startswith('ttyACM'), os.listdir('/dev/')):
        if (int(f[6:]) > highest):
            highest = int(f[6:])

    print "Trying /dev/ttyACM%d..." % highest
    ser = serial.Serial('/dev/ttyACM%d' % highest, baudrate=115200)
    ser.open()

    # pull dtr and rts low
    ser.setRTS(0)
    ser.setDTR(0)

    # toggle DTR
    ser.setDTR(1)

    # close
    ser.close()

except:
    print "Failed to open the serial port for reset, perhaps this is your first upload or the board was already in bootloader mode"


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

# close
ser.close()


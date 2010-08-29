#!/usr/bin/python

# NOTE: On Mac OSX this script must be run as sudo?

import serial
import os
import sys
from struct import pack

def get_maple_device_path_osx():
    """Try to find the device file for the Maple on OS X.  If there
    are multiple possibilities, ask the user what to do.  If the user
    chooses not to say, returns None."""
    possible_maple_paths = [x for x in os.listdir('/dev') if \
                                'tty.usbmodem' in x]
    if len(possible_maple_paths) == 1:
        return possible_maple_paths[0]
    else:
        print 'Attempting to reset Maple, but found multiple ' + \
            'candidates for the Maple device:'
        for (i,p) in enumerate(possible_maple_paths):
            print '\t%d. %s' % (i+1,os.path.join('/dev',p))

        prompt = 'Enter a number to select one, or q to quit: '
        while True:
            resp = raw_input(prompt).strip().lower()
            if resp == 'q': return None

            try:
                i = int(resp, 10)
            except ValueError:
                pass
            else:
                if 0 <= i-1 < len(possible_maple_paths):
                    return os.path.join('/dev',possible_maple_paths[i-1])
            prompt = 'Please enter a number from the list, or q to quit: '

os_sysname = os.uname()[0]
if os_sysname == 'Linux':
    maple_path = '/dev/maple'
elif os_sysname == 'Darwin':
    maple_path = get_maple_device_path_osx()
    if maple_path is None: sys.exit()
else:
    # TODO [mbolivar] special cases for windows, BSD, whatever?
    maple_path = '/dev/maple'

try:
    ser = serial.Serial(maple_path, baudrate=115200, xonxoff=1)
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


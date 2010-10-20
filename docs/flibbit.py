import os
import shutil
import re
from os.path import *

src = '/Users/mbolivar/foo/arduino.cc/en/Reference'
dst = '/Users/mbolivar/hack/leaf/libmaple/docs/source/arduino'

fs = [x for x in os.listdir(src) if x.endswith('.rst')]

def process(line):
    if re.match('-+$', line.rstrip()):
        return '=' * (len(line) - 1) + '\n'
    elif re.match('\^+$', line.rstrip()):
        return '-' * (len(line) - 1) + '\n'
    return line

for f in fs:
    print 'processing:', f
    with open(join(src,f), 'r') as f_in:
        with open(join(dst, basename(f)), 'w') as f_out:
            label = '.. _arduino-%s:\n\n' % (f.split('.')[0])
            f_out.write(label)
            for line in list(f_in.readlines())[20:-22]:
                f_out.write(process(line))


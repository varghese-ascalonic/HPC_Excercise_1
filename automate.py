#!/usr/bin/python

import sys
from subprocess import Popen, PIPE

times = int(sys.argv[1])

for i in range(times):
    process = Popen(["./a.out", "100", "4"], stdout=PIPE)
    (output, err) = process.communicate()
    print(output)
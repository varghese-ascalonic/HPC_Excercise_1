#!/usr/bin/python

import sys
import numpy as np
from subprocess import Popen, PIPE

times = int(sys.argv[1])
n = '100'
s = '4'

try:
    n = sys.argv[2]
    s = sys.argv[3]
except IndexError:
    pass

execution_times = np.zeros(times)

for i in range(times):
    process = Popen(["./a.out", n, s], stdout=PIPE)
    (output, err) = process.communicate()
    execution_times[i] = int(output)

print("Minimum          :   " + str(np.amin(execution_times)))
print("25th percentile  :   " + str(np.percentile(execution_times, 25)))
print("50th percentile  :   " + str(np.percentile(execution_times, 50)))
print("75th percentile  :   " + str(np.percentile(execution_times, 75)))
print("Maximum          :   " + str(np.amax(execution_times)))
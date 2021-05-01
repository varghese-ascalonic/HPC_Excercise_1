#!/usr/bin/python

import sys
import numpy as np
from subprocess import Popen, PIPE

times = int(sys.argv[1])

execution_times = np.zeros(times)

for i in range(times):
    process = Popen(["./a.out", "100", "4"], stdout=PIPE)
    (output, err) = process.communicate()
    execution_times[i] = int(output)

print("Minimum : " + np.amin(execution_times))
print("Maximum : " + np.amax(execution_times))
#!/usr/bin/python

import sys
import numpy as np
from subprocess import Popen, PIPE

times = int(sys.argv[1])

execution_times = np.zeros(times)

with open('runtimes.txt', 'a') as runtime_file:
    for i in range(times):
        process = Popen(["./a.out", "9000000", "4"], stdout=PIPE)
        (output, err) = process.communicate()
        execution_times[i] = int(output)
        runtime_file.write(output + "\n")


print("Minimum          :   " + str(np.amin(execution_times)))
print("25th percentile  :   " + str(np.percentile(execution_times, 25)))
print("50th percentile  :   " + str(np.percentile(execution_times, 50)))
print("75th percentile  :   " + str(np.percentile(execution_times, 75)))
print("Maximum          :   " + str(np.amax(execution_times)))
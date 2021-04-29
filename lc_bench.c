#include <sched.h> // Requires compiling with -D_GNU_SOURCE !!!
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

// TODO implement function LC


int main(int argc, char *argv[])
{
  // Passing integers n and s as command line arguments.
  int n = atoi(argv[1]);
  int s = atoi(argv[2]);

  // Dynamically allocate datastructures. 
  // Using value 32 for paramenter aligment.
  double **F = aligned_malloc2d(s, n, 32);
  double **Y =  aligned_malloc2d(s, n, 32);
  double *y = aligned_malloc1d(n, 32);
  double **A = aligned_malloc2d(s, s, 32);

  // Initialize data structures.
  for (int i = 0; i < s; ++i)
    for (int j = 0; j < n; ++j)
      F[i][j] = i * 2.0 + j;

  for (int i = 0; i < s; ++i)
    for (int j = 0; j < n; ++j)
      Y[i][j] = 0.0;
  
  for (int i = 0; i < n; ++i)
    y[i] = 42.0 + i;
  
  for (int i = 0; i < s; ++i)
    for (int j = 0; j < s; ++j)
      A[i][j] = (double) i + j;
  
  // Ensures that the program is not moved between different CPU cores during its execution.
  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);
  sched_setaffinity(0, sizeof(cpu_set_t), &mask);
  
  // TODO: Start time measurement.

  // TODO: Call function LC.

  // TODO: End time measurement.
  
  // TODO: Print runtime.

  // Free data structures.
  free1d(y);
  free2d(F);
  free2d(A);
  free2d(Y);

  return 0;
}

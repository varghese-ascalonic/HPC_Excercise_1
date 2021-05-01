#include <sched.h> // Requires compiling with -D_GNU_SOURCE !!!
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

double const H_k = 5;
int const MICRO = 1000000;

// implement function LC
void LC(double **F, double **Y, double **A, double *y, int row, int col)
{
	//Calculating the array which stores the product of A and F. Storing the results back in array Y.
 
	for (int i = 0; i < row; i++)
	    for (int j = 0; j < col; j++)
	        Y[i][j] = A[i][j] * F[i][j];
 
	// Doing the consecutive sum of the rows in the same array Y.
	// So the new_row[i] = old_row[i] + old_row[i-1] except i=0
	// And then multiplying the constant H_k
 
	for (int i = 0; i < row; i++){
	    for (int j = 0; j < col; j++){
	    	if (i == 0)
	    	    continue;
	        Y[i][j] = Y[i][j] + F[i-1][j];
	        Y[i][j] = H_k * Y[i][j];
	    }    
	}
 
	// Finally adding array y to each row of Y to get the final result
 
 
	for (int i = 0; i < row; i++)
	    for (int j = 0; j < col; j++)
	    	Y[i][j] += y[j];	
}

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
  
  // Start time measurement.
  time_snap_t ts;
  time_snap_start(&ts);

  // Call function LC.
  compute_pirk(F, Y, A, y, s, n);

  // End time measurement.
  time_snap_stop(&ts);
  
  // Print runtime.
  printf("Execution Time : %ld\n microseconds", ts.tv_usec);

  // Free data structures.
  free1d(y);
  free2d(F);
  free2d(A);
  free2d(Y);

  return 0;
}

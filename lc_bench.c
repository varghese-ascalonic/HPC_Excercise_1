#include <sched.h> // Requires compiling with -D_GNU_SOURCE !!!
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

double const H_k = 0.05;
int const MICRO = 1000000;

// implement function LC
void compute_pirk(double **F, double **Y, double **A, double *y, int row, int col)
{
	//Calculating the array which stores the product of A and F. Storing the results back in array Y.
	int sum = 0;
	for ( i = 0 ; i < row ; i++ )
    {
      for ( j = 0 ; j < col ; j++ )
      {
        for ( k = 0 ; k < row ; k++ )
        {
          sum = sum + A[i][k]*F[k][j];
        }
 
        Y[i][j] = sum;
        sum = 0;
      }
    }
 
	// Finally adding array y to each row of Y to get the final result
 
 
	for (int i = 0; i < row; i++)
	    for (int j = 0; j < col; j++)
	    	Y[i][j] = H_k * Y[i][j] + y[j];	
}

void compute_pirk_2(double **F, double **Y, double **A, double *y, int row, int col)
{
  for(int i=0; i<row; i++) 
    Y[i][0] = y[i];

  for(int k=0; k<col; k++)
  {
    for(int l=0; l<row; l++)
    {
      double sum = 0.0;
      for(int i=0; i<row; i++)
      {
        if(k == 0) continue;
        sum += A[l][i] * F[i][k-1];
      }
      Y[l][k] = y[k] + H_k * sum;
    }
  }
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
  compute_pirk_2(F, Y, A, y, s, n);

  // End time measurement.
  time_snap_stop(&ts);
  
  // Print runtime.
  printf("%ld", ts.tv_usec);

  // Free data structures.
  free1d(y);
  free2d(F);
  free2d(A);
  free2d(Y);

  return 0;
}

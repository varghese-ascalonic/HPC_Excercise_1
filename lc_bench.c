#include <sched.h> // Requires compiling with -D_GNU_SOURCE !!!
#include<stdio.h>
#include<stdlib.h>

#include "util.h"

double const H_k = 5;
int const MICRO = 1000000;

// TODO implement function LC
 
void LC(double **F, double **Y, double **A, double *y, int row, int col)
{
	//Calculating the array which stores the product of A and F. Storing the results back in array Y.
	int sum = 0;
	for ( int i = 0 ; i < row ; i++ )
	{
	  for (int j = 0 ; j < col ; j++ )
	  {
		for ( int k = 0 ; k < row ; k++ )
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
 
 
void LC_reverse(double **F, double **Y, double **A, double *y, int row, int col)
{
	//Calculating the array which stores the product of A and F. Storing the results back in array Y.
	int sum = 0;
	for ( int j = 0 ; j < row ; j++ )
	{
	  for (int i = 0 ; i < col ; i++ )
	  {
		for ( int k = 0 ; k < row ; k++ )
		{
		  sum = sum + A[i][k]*F[k][j];
		}

		Y[i][j] = sum;
		sum = 0;
	  }
	}

	// Finally adding array y to each row of Y to get the final result


	for (int j = 0; j < row; j++)
		for (int i = 0; i < col; i++)
			Y[i][j] = H_k * Y[i][j] + y[j];	
}


// Print array function for checking purposes

void prettyPrint(double **arr, int row, int col)
{
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			printf("%f ",arr[i][j]);
		}
		printf("\n");
	}
}
 
 
int main(int argc, char *argv[])
{
	// TODO: Pass integers n and s as command line arguments.
	int n = atoi(argv[1]);
	int s = atoi(argv[2]);

	//printf("arguments = %d s = %d, n = %d", argc,s, n);

	// TODO: Dynamically allocate datastructures. 
	// Use value 32 for paramenter aligment.
	double **F = aligned_malloc2d(s, n, 32);
	double **Y = aligned_malloc2d(s, n, 32);
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
	time_snap_t start_time;
	time_snap_start(&start_time);

	// TODO: Call function LC.
	LC(F, Y, A, y, s, n);
	//prettyPrint(Y, s, n);


	// TODO: End time measurement.
	time_snap_t finish_time;
	int time_taken = time_snap_stop(&start_time);

	// TODO: Print runtime.
	printf("%d", time_taken);

	// TODO: Free data structures.
	free2d(F);
	free2d(Y);
	free1d(y);
	free2d(A);

	return 0;

}

#ifndef UTIL_H_
#define UTIL_H_

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>


#define ALIGN(X, Y) ((unsigned long) ((((X) + (Y) - 1)/(Y)) * (Y)) % 256 < (Y) ? ((((X) + (Y) - 1)/(Y)) * (Y)) + (Y) : ((((X) + (Y) - 1)/(Y)) * (Y)))


static double *aligned_malloc1d (size_t a, const size_t alignment)
{
  return (double *) aligned_alloc (alignment, a * sizeof (double));
}

static double **aligned_malloc2d (size_t a, size_t b, const size_t alignment)
{
  size_t i, row_size, row_count;
  double **x;
  row_size = ALIGN (b * sizeof (double), alignment);
  row_count = row_size / sizeof (double);
  x = (double **) aligned_alloc (alignment, a * sizeof (double *));
  x[0] = (double *) aligned_alloc (alignment, a * row_size);
  for (i = 1; i < a; i++)
    x[i] = x[0] + i * row_count;
  return x;
}

static void free1d(double *p)
{
  free((void *)p);
}

static void free2d(double **p)
{
  free((void *)p[0]);
  free((void *)p);
}


typedef struct timeval time_snap_t;

static void
time_snap_start (time_snap_t * ts)
{
  gettimeofday (ts, NULL);
}

// Returns time in micro seconds.
static uint64_t
time_snap_stop (const time_snap_t * ts1)
{
  time_snap_t ts2;
  gettimeofday (&ts2, NULL);

  return ((uint64_t) (ts2.tv_sec - ts1->tv_sec) * 1000000 +
	  (uint64_t) ts2.tv_usec - (uint64_t) ts1->tv_usec);
}

#endif

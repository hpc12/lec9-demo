#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "timing.h"




int main()
{
  int result = 0;
  const int n = 1024*1024;

  float *allocation;
  if (errno = posix_memalign((void **) &allocation, 64, n*sizeof(float) + 64))
    perror("allocating a");

  float __attribute__ ((aligned (1))) *b = malloc(n*sizeof(float));
  if (errno = posix_memalign((void **) &b, 64, n*sizeof(float) + 64))
    perror("allocating b");

  float __attribute__ ((aligned (64))) *a = (float *) (((char *) allocation) + 0);

  /*
  puts("write");
  for (int i = 0; i<n; ++i)
    a[i] = i;
    */

  timestamp_type t1;
  get_timestamp(&t1);

  for (int ntrips = 0; ntrips < 1000; ++ntrips)
  {
    for (int i = 0; i<n; ++i)
      b[i] = 2*a[i];
  }

  timestamp_type t2;
  get_timestamp(&t2);

  printf("elapsed time: %g s\n",
      timestamp_diff_in_seconds(t1, t2));

  // fake a dependency on a
  for (int i = 0; i<n; ++i)
    result += a[i];

  free(allocation);
  return result;
}


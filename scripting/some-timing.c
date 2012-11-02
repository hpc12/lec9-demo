#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "timing.h"




int main(int argc, char **argv)
{
  int result = 0;
  if (argc != 2)
  {
    fprintf(stderr, "need an arguments\n");
    abort();
  }
  const long n = atol(argv[1]);

  float *a = (float *) malloc(sizeof(float) * n*n);

  timestamp_type t1;
  get_timestamp(&t1);

  for (int ntrips = 0; ntrips < 1000; ++ntrips)
  {
    for (long i = 0; i < n*n; ++i)
      a[i]++;
  }

  timestamp_type t2;
  get_timestamp(&t2);

  free(a);

  printf("elapsed time: %g s\n",
      timestamp_diff_in_seconds(t1, t2));
}


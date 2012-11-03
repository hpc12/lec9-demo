#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <omp.h>
#include <math.h>
#include "timing.h"




int main()
{
  const int n = 10*1024*1024/omp_get_max_threads();

  /*
  puts("write");
  for (int i = 0; i<n; ++i)
    a[i] = i;
    */

  omp_lock_t my_lock;

  omp_init_lock(&my_lock);

  double x = 0;

  timestamp_type t1;
  get_timestamp(&t1);

#pragma omp parallel default(none) shared(my_lock) reduction(+:x)
  {
    x = 12;
    for (int ntrips = 0; ntrips < n; ++ntrips)
    {
#define DO \
      omp_set_lock(&my_lock); \
      omp_unset_lock(&my_lock);

      DO DO DO DO DO     DO DO DO DO DO
    }
  }

  timestamp_type t2;
  get_timestamp(&t2);

  double elapsed = timestamp_diff_in_seconds(t1, t2);
  printf("lock cycle rate: %g per s\n", n*10/elapsed);

  omp_destroy_lock(&my_lock);

  return x;
}









        /*
#define DO2 \
      x = sin(x);

      DO2 DO2 DO2 DO2  DO2 DO2 DO2 DO2
      */

// modified from Lin & Snyder
// http://books.google.com/books?id=iYghAQAAIAA

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "timing.h"


int main()
{
  const int array_size = 256*1000;

  int *array = malloc(array_size * sizeof(int));
  for (int i = 0; i < array_size; ++i)
    array[i] = rand() % 10;

  int num_threads = omp_get_max_threads();
  const int stride = 1;
  volatile int sums[num_threads*stride];

  timestamp_type t1;
  get_timestamp(&t1);

#pragma omp parallel default(none) shared(sums,num_threads) firstprivate(array,stride)
  {
    assert(omp_get_num_threads() == num_threads);

    int tid = omp_get_thread_num();

    for (int trp = 0; trp < 5000; ++trp)
    {
#pragma omp for
      for (int i = 0; i < array_size; ++i)
        sums[tid*stride] += array[i];
    }
  }

  timestamp_type t2;
  get_timestamp(&t2);

  double elapsed = timestamp_diff_in_seconds(t1, t2);
  printf("elapsed wall time: %g (%d threads)\n", elapsed, num_threads);

  free(array);
  return 0;
}

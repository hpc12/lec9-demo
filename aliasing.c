void copy_twice(float *a, float *b, int n)
{
  for (int i = 0; i < n; ++i)
  {
    b[2*i] = a[i];
    b[2*i+1] = a[i];
  }

}



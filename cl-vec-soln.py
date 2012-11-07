import pyopencl as cl
import pyopencl.array
import numpy as np

ctx = cl.create_some_context()
queue = cl.CommandQueue(ctx)

n = 80 * (2**10)**2

mf = cl.mem_flags
a = cl.array.zeros(queue, n, np.float32)
b = cl.array.zeros(queue, n, np.float32)
c = cl.array.empty_like(a)

prg = cl.Program(ctx, """//CL//
    #define OP(x) x

    kernel void sum(global const float *a,
      global const float *b, global float *c, int n)
    {
      for (int i = 0; i < n; ++i)
        c[i] = OP(a[i] + b[i]);
    }

    kernel void vec_sum(global const float *a,
      global const float *b, global float *c, const int n)
    {
      global float4 *a_vec = (global float4 *) a;
      global float4 *b_vec = (global float4 *) b;
      global float4 *c_vec = (global float4 *) c;

      for (int i = 0; i < n/4; ++i)
      {
        float4 res = a_vec[i] + c_vec[i];

        res = OP(res);

        c_vec[i] = res;
      }
    }

    kernel void unaligned_vec_sum(global const float *a,
      global const float *b, global float *c, const int n)
    {
      for (int i = 0; i < n/4; ++i)
      {
        float4 res = vload4(i, a) + vload4(i, b);
        res = OP(res);
        vstore4(res, i, c);
      }
    }
    """).build()

from time import time

ntrips = 10

prg.sum(queue, (1,), (1,), a.data, b.data, c.data, np.int32(n))

queue.finish()
t1 = time()
for i in xrange(ntrips):
    prg.sum(queue, (1,), (1,), a.data, b.data, c.data, np.int32(n))
queue.finish()
t2 = time()
print "single: M entries per sec: %g" % (ntrips*n/(t2-t1)*1e-6)

queue.finish()
t1 = time()
for i in xrange(ntrips):
    prg.vec_sum(queue, (1,), (1,), a.data, b.data, c.data, np.int32(n))
queue.finish()
t2 = time()
print "vectorized: M entries per sec: %g" % (ntrips*n/(t2-t1)*1e-6)

queue.finish()
t1 = time()
for i in xrange(ntrips):
    prg.unaligned_vec_sum(queue, (1,), (1,), a.data, b.data, c.data, np.int32(n))
queue.finish()
t2 = time()
print "unaligned vectorized: M entries per sec: %g" % (ntrips*n/(t2-t1)*1e-6)

# vim: filetype=pyopencl

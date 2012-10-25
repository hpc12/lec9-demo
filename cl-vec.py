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
    kernel void sum(global const float *a,
      global const float *b, global float *c, int n)
    {
      for (int i = 0; i < n; ++i)
        c[i] = a[i] + b[i];
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


# vim: filetype=pyopencl


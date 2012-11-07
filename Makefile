EXECUTABLES = \
	      mpi-bandwidth mpi-bi-bandwidth mpi-latency \
	      register-pressure.o aliasing.o \
	      alignment \
	      numa-test threads-vs-cache lock-contention

all: $(EXECUTABLES)

register-pressure.o: register-pressure.c
	gcc -c -O3 -std=gnu99 $(DEBUG_FLAGS) -o$@ $^

aliasing.o: aliasing.c
	gcc -c -O -std=gnu99 $(DEBUG_FLAGS) -o$@ $^

alignment: alignment.c
	gcc -ftree-vectorizer-verbose=2 -march=native -mtune=native -Ofast -std=gnu99 $(DEBUG_FLAGS) -lrt -o$@ $^

numa-test: numa-test.c
	gcc -O3 -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -lnuma -o$@ $^

threads-vs-cache: threads-vs-cache.c
	gcc -O0 -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -o$@ $^

lock-contention: lock-contention.c
	gcc -O0 -std=gnu99 -fopenmp $(DEBUG_FLAGS) -lrt -lm -o$@ $^

mpi%: mpi%.c
	mpicc -std=gnu99 $(DEBUG_FLAGS) -lrt -o$@ $^

clean:
	rm -f $(EXECUTABLES) *.o mpe-*

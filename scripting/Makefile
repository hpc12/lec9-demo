EXECUTABLES = some-timing

all: $(EXECUTABLES)

some-timing: some-timing.c
	gcc -O3 -std=gnu99 $(DEBUG_FLAGS) -o$@ $^ -lrt

clean:
	rm -f $(EXECUTABLES) *.o mpe-*

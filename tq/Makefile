logtq: main.h main.c
	gcc -o logtq main.c $(shell pkg-config --cflags --libs libnl-3.0) $(shell pkg-config --cflags --libs libnl-genl-3.0) -lm -lrt

clean:
	rm logtq
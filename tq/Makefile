logtq: main.h main.c
	gcc -o logtq main.c $(shell pkg-config --cflags --libs libnl-3.0) $(shell pkg-config --cflags --libs libnl-genl-3.0) -lm -lrt

install: logtq
	install -m 700 -o root -g root logtq /usr/local/bin/logtq

clean:
	rm logtq
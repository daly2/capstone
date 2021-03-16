FLAGS = $(shell pkg-config --cflags --libs libnl-3.0) $(shell pkg-config --cflags --libs libnl-genl-3.0) -lm -lrt

all: gettq logtq

gettq: gettq.o batman-adv.o netlink.o util.o
	gcc -o gettq gettq.o batman-adv.o netlink.o util.o $(FLAGS)

logtq: logtq.o batman-adv.o netlink.o util.o
	gcc -o logtq logtq.o batman-adv.o netlink.o util.o $(FLAGS)

batman-adv.o: batman-adv.h batman-adv.c
	gcc -c batman-adv.c $(FLAGS)

gettq.o: gettq.h gettq.c
	gcc -c gettq.c $(FLAGS)

logtq.o: logtq.h logtq.c
	gcc -c logtq.c $(FLAGS)

netlink.o: netlink.h netlink.c
	gcc -c netlink.c $(FLAGS)

util.o: util.h util.c
	gcc -c util.c $(FLAGS)

install: gettq logtq
	install -m 700 -o root -g root gettq /usr/local/bin/gettq
	install -m 700 -o root -g root logtq /usr/local/bin/logtq

clean:
	rm -f gettq logtq *.o

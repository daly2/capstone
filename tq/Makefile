FLAGS = $(shell pkg-config --cflags --libs libnl-3.0) $(shell pkg-config --cflags --libs libnl-genl-3.0) -lm -lrt

all: logtq gettq

logtq: main.o batman-adv.o util.o
	gcc -o logtq main.o batman-adv.o util.o $(FLAGS)

gettq: main.o batman-adv.o util.o

batman-adv.o: batman-adv.h batman-adv.c
	gcc -c batman-adv.c $(FLAGS)

main.o: main.h main.c
	gcc -c main.c $(FLAGS)

util.o: util.h util.c
	gcc -c util.c $(FLAGS)

install: logtq
	install -m 700 -o root -g root logtq /usr/local/bin/logtq

clean:
	rm logtq *.o
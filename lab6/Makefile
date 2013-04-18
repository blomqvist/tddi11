LIBS=-lSDL

all: example main

example: example.o system.o rims.h
	gcc -Wall -Wextra -pedantic -g -std=c99 $(LIBS) system.o example.o -o $@

main: main.o system.o rims.h
	gcc -Wall -Wextra -pedantic -g -std=c99 $(LIBS) system.o main.o -o $@

%.o: %.c
	gcc -Wall -Wextra -pedantic -g -std=c99 -c $<

clean:
	@\mv system.o system.o.bak
	\rm -f a.out example main *.o *~
	@\mv system.o.bak system.o
	@\cp /home/TDDI11/lab/skel/lab6/system.o .
	@\cp /home/TDDI11/lab/skel/lab6/rims.h .

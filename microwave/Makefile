LIBS=-lSDL -lSDL_image

all: main

main: main.o given_files/system.o given_files/rims.h
	gcc -Wall -Wextra -pedantic -g -std=c99 $(LIBS) given_files/system.o main.o -o $@

%.o: %.c
	gcc -Wall -Wextra -pedantic -g -std=c99 -c $<

clean:
	\rm -f a.out main *.o

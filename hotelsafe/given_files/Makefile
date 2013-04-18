LIBS=-lSDL -lSDL_image
CFLAGS=-Wall -Wextra -pedantic -g -std=c99 -Igiven_files

all: main ultimate-number

main: main.o given_files/system.o given_files/rims.h
	gcc  $(LIBS) given_files/system.o main.o -o $@

ultimate-number: ultimate-number.o
	gcc $(CFLAGS) $(LIBS) ultimate-number.o -o $@

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	\rm -f a.out main ultimate-number *.o *~

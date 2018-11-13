#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -std=c99 -O3

#  Sources
SOURCES = funcs.c map.c main.c

#  Objects
OBJECTS = funcs.o map.o main.o

main: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

map.o: map.h map.c

funcs.o: funcs.h defs.h funcs.c


clean::
	rm -f *.o core a.out main *~

# DO NOT DELETE

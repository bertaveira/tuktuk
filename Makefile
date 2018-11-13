#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -std=c99 -O3

#  Sources
SOURCES = funcs.c map.c main.c

#  Objects
OBJECTS = funcs.o map.o main.o

tuktuk: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

map.o: map.h defs.h map.c

funcs.o: funcs.h defs.h funcs.c


clean:
	rm tuktuk $(OBJECTS)

# DO NOT DELETE

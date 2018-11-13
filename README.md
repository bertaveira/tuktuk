# TukTuk

In this project we were asked to develop a program in C language that would find the best path from A to B. Each move has a cost so the program should find the cheapest path and not the shortest.

The pawn can only move like a horse in chess (L shape moves).

### Modes:
* A - Move from x1 to x2 minimizing the cost of the path.
* B - Move from x1 and go through all xn, until the last one in the given order, minimizing the cost.
* C - Move from x1 and go through all xn, until the last one not in any specific order, minimizing the cost.



## Getting Started

This is all made in C language and was tested using `gcc`

### Prerequisites

1. gcc
2. makefile


### Run The Program

First of all you should compile the Program.
The makefile already does it for you so all you have to do is use the command `make` in the right directory.

```
make
```

After that you can run the program using a command like this:

```
./tuktuk <name>.cities
```

## Input File

The file (<name>.cities) used as an argument to the program should be like the one bellow.

The first line is: heigh of map || width of map || mode || number of points of interest

The next lines with 2 numbers are the points of interest coordinates.

After that the rest is the map where the numbers are the cost (0 means you cant go there)

```
10 11 A 2
0 0
7 9
1 0 2 3 2 3 2 3 2 3 1
3 2 1 2 3 3 1 2 3 2 1
4 3 2 1 2 3 4 5 0 3 1
1 6 2 3 2 3 2 3 2 3 1
3 2 1 2 3 0 1 2 3 2 1
4 3 2 1 2 3 4 5 3 3 1
1 2 0 3 2 3 2 3 2 3 1
3 2 1 2 3 3 1 2 3 2 1
4 3 2 1 2 3 4 5 3 0 1
1 7 2 3 2 3 2 3 2 3 1
```

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

The file (name.cities) used as an argument to the program should be like the one bellow.

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


## Output File

The output file (name.walks) of the program should be like the one bellow.

The first line is the same as the input file in the first 4 arguments. The next two are: cost of the less expensive path || number of moves of the path.
It's important to note that if no path was found, the 5 argument (in this example with value = 11) will be -1 and the 6 (with value 6 in the example) will be 0.

After that the rest is the path (coordinates and cost)

```
10 11 A 2 11 6
1 2 1
2 4 2
3 6 2
4 8 3
5 10 1
7 9 2
```

## Using the autorun script

This script does the "make" comand and also runs the program for every .cities file in the directory testfiles/

Make sure you have a folder testfiles/ where all your .cities are.

Run the following comand to mae the scritp executable (you only have to do it once):
```
chmod 755 autorun
```
The you can execute the script normally
```
./autorun
```

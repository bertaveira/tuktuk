# TukTuk

In this project we were asked to develop a program in C language that would find the best path from A to B. Each move has a cost so the program should find the cheapest path and not the shortest.

The pawn can only move like a horse in chess (L shape moves).

### Modes:
A - Move from x1 to x2 minimizing the cost of the path
B - Move from x1 and go through all xn, until the last one in the given order, minimizing the cost
C - Move from x1 and go through all xn, until the last one not in any specific order, minimizing the cost

### Run The Program

First of all you should compile the Program.
The makefile already does it for you so all you have to do is use the command `make` in the right directory.

After that you can run the program using a command like this:

```
./tuktuk <nome>.cities
```

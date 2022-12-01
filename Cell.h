#include <stdlib.h>
#include <stdio.h>

typedef struct Cell_T Cell_T;
struct Cell_T
{
    int value;
    Cell_T* lft;
    Cell_T* rgt;
    int weight;

};

Cell_T* initCell();
Cell_T* initSCell(int);
Cell_T* initSWCell(int s, int w);

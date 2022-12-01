#include "stdlib.h"

typedef struct Sommet_T Sommet_T;
struct Sommet_T
{
    int val;
    int color;
    int distance;
    int father;
    int date;
    int datef;

};

Sommet_T * initSom(int s);
void showSommet(Sommet_T *);

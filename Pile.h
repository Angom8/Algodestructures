//
// Created by angom on 02/10/2020.
// PARTIELLEMENT REPRIS DU CODE EFFECTUE EN INFO0401 AVEC LUCA ALVARO
//

#include <stdlib.h>
#include <stdio.h>
#include "Sommet.h"
#define TAILLE_MAX 256

/*Pile de premier element first*/
typedef struct Pile_T Pile_T;
struct Pile_T
{
    Sommet_T ** pile;
    int t;
    int tail;
};

Pile_T* initPile(int);
void destroyPile(Pile_T*);
int isEmptyPile(Pile_T*);
int isFullPile(Pile_T*);
Sommet_T* top(Pile_T*);
void stack(Pile_T*, Sommet_T*);
Sommet_T* unstack(Pile_T*);

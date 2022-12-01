//
// Created by angom on 08/10/2020.
//

#include <stdio.h>
#include "Sommet.h"

/*Initialise un sommet à partir de sa valeur*/
Sommet_T* initSom(int s){
    Sommet_T *som = malloc(sizeof(Sommet_T));
    som->father = -1;
    som->color= 0;//BLANC PAR DEFAUT, 1 = GRIS et 2 = NOIR
    som->distance = 0;
    som->val = s;
    som->date = -1;
    som->datef = -1;
    return som;
}

/*Imprime les informations du sommet*/
void showSommet(Sommet_T *s){
    if(s) printf("Sommet de valeur %d, couleur %d, de pere %d et distance pere %d\n", s->val, s->color, s->father, s->distance);
}


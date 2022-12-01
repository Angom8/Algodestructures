#include "Pile.h"

/*Initialise et réinitialise la pile*/
Pile_T* initPile(int t){
    Pile_T* p = malloc(sizeof(Pile_T));
    p->t = t;
    p->pile = malloc(t * sizeof(Sommet_T*));
    p->tail= -1;
    return p;
}

/*Détermine si la pile est pleine*/
int isFullPile(Pile_T* p){
    return p->tail == p->t;
}

/*Détermine si la pile est vide*/
int isEmptyPile(Pile_T* p){
    return  (p->tail == -1);
}

/*Ajoute sur la pile le sommet s*/
void stack(Pile_T* p, Sommet_T * s){
    if (isFullPile(p) != 1){
        if(isEmptyPile(p) == 1){
            p->tail = 1;
            p->pile[0] = s;
        }
        else{
            p->pile[p->tail] = s;
            p->tail++;
        }
    }
}

/*Retire le sommet sommet de la pile*/
Sommet_T * unstack(Pile_T* p){
    Sommet_T * s = initSom(-1);
    if (isEmptyPile(p) != 1){
        if(p->tail == 1){
            free(s);
            s = p->pile[p->tail-1];
            p->tail = -1;
        }
        else{
            free(s);
            s = p->pile[p->tail-1];
            p->tail--;
        }
    }
    return s;
}

/*Détruit la pile*/
void destroyPile(Pile_T* p){
    for(int i = 0;i<p->t;i++){
        if(p->pile[i] != NULL){
            free(p->pile[i]);
        }
    }
    free(p->pile);
    free(p);
}

/*Retourne le sommet sommet de la pile sans le retirer*/
Sommet_T* top(Pile_T* p){
    return p->pile[p->tail-1];
}
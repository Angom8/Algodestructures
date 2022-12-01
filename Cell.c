//
// Created by angom on 02/10/2020.
//

#include "Cell.h"

/*Creation par défaut de la cellule de liste*/
Cell_T* initCell(){
    Cell_T* c= malloc(sizeof(Cell_T));
    c->value = -1;
    c->lft = NULL;
    c->rgt = NULL;
    c->weight = -1;
    return c;

}

/*Creation avec entrée Sommet de la cellule de liste*/
Cell_T* initSCell(int s){
    Cell_T* c= malloc(sizeof(Cell_T));
    c->lft = NULL;
    c->rgt = NULL;
    c->value = s;
    c->weight = -1;
    return c;
}
/*Creation avec entrée Sommet et Poids de la cellule de liste*/
Cell_T* initSWCell(int s, int w){
    Cell_T* c= malloc(sizeof(Cell_T));
    c->lft = NULL;
    c->rgt = NULL;
    c->value = s;
    c->weight = w;
    return c;
}


//
// Created by angom on 02/10/2020.
//

#include "List.h"

/*Initialise la liste*/
List_T* initList(){
    List_T * l = malloc(sizeof(List_T));
    l->head = NULL;
    l->tail = NULL;
    return l;

}

/*Detruit la liste recursivement*/
void destroyList(List_T* l){
    destroyCellList(l->head);
    l->head = NULL;
    l->tail = NULL;
    free(l);
}

/*Recursion à partir de la fonction ci-dessus*/
void destroyCellList(Cell_T* c){
    if(c != NULL){
        if(c->rgt != NULL) destroyCellList(c->rgt);
        c->rgt = NULL;
        c->lft = NULL;
        free(c);
    }
}

/* Prend en paramètre un pointeur sur une cellule et
 * insère cette cellule au début d’une liste */
void insertList(List_T* l, Cell_T* c){
    if(l->head == NULL) {
        l->head = c;
        l->tail = c;
        c->lft = NULL;
        c->rgt = NULL;
    }
    else{
        c->lft = NULL;
        c->rgt = l->head;
        c->rgt->lft= c;
        l->head = c;
    }

}

/* Recherche  un sommet dans une  liste et retourne
 * soit un pointeur sur la cellule qui contient le sommet, soit NULL
 */

Cell_T* searchList(List_T* l, int s){
    Cell_T* c = l->head;
    while(c != NULL && c->value != s){
        c = c->rgt;
    }
    return c;
}
/* Prend  en  paramètre  un  pointeur  sur  une  cellule  d'une  liste
 * et  supprime  cette cellule de la liste
 * */
void destroyCellFromList(List_T* l, Cell_T* c){

    //La cellule est la première de la liste ?
    if (l->head == c){//ou avec c_pred NULL
        l->head = c->rgt; //meme avec c->c_succ null

    }
    //La cellule est la dernière de la liste ?
    else if (c == l->tail){
        c->lft->rgt =  NULL;
        l->tail = c->lft;
    }
    //default
    else{
        c->lft->rgt = c->rgt;
        c->rgt->lft = c->lft;

    }
    //dans tous les cas, on élimine la Cellule
    c->lft = NULL;
    c->rgt = NULL;
    free(c);
}

/* Affiche à l’écran les informations relatives à une liste */

void showList(List_T* l){
    Cell_T* c = l->head;
    printf("(");

    if(c == NULL){
        printf("- none -");
    }
    while(c != NULL){
        printf("- %d -", c->value);
        c = c->rgt;
    }

    printf(")\n");
}



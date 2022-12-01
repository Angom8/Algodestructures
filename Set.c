#include "Set.h"

Set_H* initSet(int s){
    Set_H* e = malloc(sizeof(Set_H));
    e->value = s;
    e->lft = NULL;
    e->rgt = NULL;
    e->head = e;
    e->tail = e;
    return e;
}

/*Detruit la liste du Set recursivement*/
void destroySet(Set_H* x){
    destroySubSet(x->head);
    x->head = NULL;
    x->tail = NULL;
    free(x);
}

/*Recursion à partir de la fonction ci-dessus*/
void destroySubSet(Set_H* x){
    if(x != NULL){
        if(x->rgt != NULL) destroySubSet(x->rgt);
        x->rgt = NULL;
        x->lft = NULL;
        free(x);
    }
}

Set_H* findSet(Set_H* x){
    return x->head;
}

int inSameSet(Set_H* x, Set_H* y){
    int r = 0;
    if(findSet(x) == findSet(y)){
        r = 1;
    }
    return r;
}

void fuseSet(Set_H* x, Set_H* y){
    x->tail->rgt = y->head;
    x->tail = y->tail;
    Set_H* z = y->head;

    while(z != NULL){
        z->head = x->head;
        z = z->rgt;
    }
    free(z);

}


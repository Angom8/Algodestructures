
#include "Heap.h"

/*Retourne l'indice du parent de l'indice fourni*/
int parent(int i){
    return i/2;
}
/*Retourne la valeur gauche du parent de l'indice fourni*/
int lft(int i){
    return 2*i;
}
/*Retourne la valeur droite du parent de l'indice fourni*/
int rgt(int i){
    return 2*i+1;
}

/*Initialise un tas de taille t donnée*/
Heap_H* initHeap(int t){
    Heap_H* h = malloc(sizeof(Heap_H));
    h->size = 0;
    h->max_size = t;
    h->heap = malloc(h->max_size*sizeof(Ridge_T*));
    return h;
}

/*Entasse le tas*/
void stackHeap(Heap_H * h, int i){
    int l, r;
    int max;
    Ridge_T* ar;

    if(h != NULL && h->heap != NULL){
        l = lft(i);
        r = rgt(i);
        max = i;
        if(l < h->size && h->heap[l]->weight > h->heap[i]->weight){
            max = l;
        }
        if(r < h->size && h->heap[r]->weight > h->heap[max]->weight){
            max = r;
        }
        if(max != i){
            ar = h->heap[i];
            h->heap[i] = h->heap[max];
            h->heap[max] = ar;
            stackHeap(h, max);
        }
    }
}

Heap_H * buildMaxHeap(Ridge_T ** t_rid){
    int i;
    int size = countRidges(t_rid);
    Heap_H* h = initHeap(size);

    if(t_rid != NULL){
        h->size = size;
        for(i=0;i<size;i++){
            h->heap[i] = t_rid[i];
        }
        for(i=h->max_size/2 ;i>=0 ;i--){
            stackHeap(h, i);
        }
    }

    return h;
}

void sortHeap(Heap_H *h){
    int i;
    Ridge_T* r;
    if(h != NULL && h->heap != NULL){
        for(i=h->max_size-1;i>0;i--){
            r = h->heap[0];
            h->heap[0] = h->heap[i];
            h->heap[i] = r;
            h->size--;
            stackHeap(h, 0);
        }
    }
    h->size = h->max_size;
    
}

void destroyHeap(Heap_H* h) {
    if (h->heap != NULL) {
        for(int i=0;i<h->max_size;i++){
            if (h->heap[i] && h->heap[i] != NULL) free(h->heap[i]);
        }
    }
    free(h->heap);
    free(h);
}

void showHeap(Heap_H * h){
    for(int i=0;i<h->max_size;i++) {
        showRidge(h->heap[i]);
    }
}

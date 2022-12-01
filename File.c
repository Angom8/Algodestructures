//
// Created by angom on 08/10/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "File.h"

/*Creation de la file avec une taille précise*/
File_H * initFile(int size){
    File_H *f = malloc(sizeof(File_H));
    f->max_size = size;
    f->sommets = malloc(f->max_size * sizeof(Sommet_T*));
    f->head = 0;
    f->tail = 0;
    return f;
}
/*Renvoie 1 si la file est vide, 0 sinon*/
int isEmptyFile(File_H *f){
    int s = 0;
    if(f){
        if(((f->head == 0) & (f->head == f->tail)) || (f->sommets[f->head] == NULL)) s = 1;
    }
    return s;
}

/*Renvoie 1 si la file est pleine, 0 sinon*/
int isFullFile(File_H *f){
    int s = 0;
    if(f->tail == f->max_size) s = 1;
    return s;
}

/*Vide la file et la désalloue*/
void destroyFile(File_H *f){
    int i = 0;
    while(i<f->max_size){
        if(f->sommets[i] != NULL) free(f->sommets[i]);
        i++;
    }
    free(f->sommets);
    free(f);
}

/*Ajoute une valeur à la fin de la file*/
void enfiler(File_H * f , Sommet_T * s){
    if(isFullFile(f) != 1){
        f->sommets[f->tail] = s;
        f->tail++;
    }
}

/*Retire la permière valeur (FIFO, first in first out*/
Sommet_T* defiler(File_H * f){
    Sommet_T * s = initSom(-1);
    if(f->sommets != NULL && f->sommets[0] != NULL){
        if(isEmptyFile(f) != 1) {
            free(s);
            s = f->sommets[f->head];
            if(f->tail != f->head) f->head++;
        }
    }
    return s;
}

/*Imprime les informations de la liste*/
void showFile(File_H * f){
    int i = f->head;
    if((f->sommets != NULL) && (f->sommets[0] != NULL)) {
        printf("- La File de taille %d, tete %d et queue %d - \n", f->max_size, f->head, f->tail);
        while ((f->sommets[i] != NULL) & (i < f->tail)) {
            printf("%d : ", i);
            showSommet(f->sommets[i]);
            i++;
        }
        printf("- Fin de File -\n");
    }

}

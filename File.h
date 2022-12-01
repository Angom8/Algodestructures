//
// Created by angom on 08/10/2020.
//
#include "Pile.h"
#define TAILLE_MAX 256

typedef struct File_H File_H;
struct File_H
{
    Sommet_T ** sommets;
    int head;
    int tail;
    int max_size;

};

File_H * initFile(int);
void destroyFile(File_H*);
int isEmptyFile(File_H*);
int isFullFile(File_H*);
void enfiler(File_H*, Sommet_T*);
void showFile(File_H*);
Sommet_T * defiler(File_H*);


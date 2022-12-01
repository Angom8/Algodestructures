//
// Created by angom on 09/10/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "Ridge.h"

/*Pile de premier element first*/
typedef struct Heap_H Heap_H;
struct Heap_H
{
    Ridge_T ** heap;
    int size;
    int max_size;
};

int parent(int);
int lft(int);
int rgt(int);
Heap_H* initHeap(int);
void stackHeap(Heap_H*, int);
Heap_H * buildMaxHeap(Ridge_T**);
void showHeap(Heap_H*);
void destroyHeap(Heap_H*);
void  sortHeap(Heap_H*);

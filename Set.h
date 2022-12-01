#include <stdlib.h>
#include <stdio.h>

typedef struct Set_H Set_H;
struct Set_H
{
    int value;
    Set_H * lft;
    Set_H * rgt;
    Set_H * head;
    Set_H * tail;

};

Set_H* initSet(int);
void destroySet(Set_H*);
void destroySubSet(Set_H*);
int inSameSet(Set_H*, Set_H*);
Set_H* findSet(Set_H*);
void fuseSet(Set_H*, Set_H*);

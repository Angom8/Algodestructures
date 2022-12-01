#include "Cell.h"

typedef struct List_T List_T;
struct List_T
{
    Cell_T * head;
    Cell_T * tail;

};

List_T* initList();
void destroyList(List_T*);
void destroyCellList(Cell_T*);
void destroyCellFromList(List_T*, Cell_T*);
void insertList(List_T*, Cell_T*);
Cell_T* searchList(List_T*, int);
void showList(List_T*);


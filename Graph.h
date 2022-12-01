//
// Created by angom on 02/10/2020.
//
#include "List.h"
#include "File.h"
#include "Heap.h"
#include "Set.h"
#include <string.h>


#define TAILLE_MAX 256

typedef struct Graph_T Graph_T;
struct Graph_T
{
    List_T ** adja;
    int ** m_Adja;
    int orientation;
    int has_value;
    int count;

};


typedef struct  BandB_T BandB_T;
struct BandB_T
{
    Ridge_T ** t_rid;
    int weight;
    int best;

};


//TP1
Graph_T* initGraph(char *);
void showGraph(Graph_T*);
void destroyGraph(Graph_T*);

//TP2
void parcoursLargeur(Graph_T *, Sommet_T *s);
void afficherChemin(Graph_T*, Sommet_T*, int);
void parcours_profondeur(Graph_T *g);
void parcours_profondeur_iteratif(Graph_T *g);

//TP 3
Graph_T* initGraphWeight(char * f);
Ridge_T** getRidges(Graph_T *);

//TP 4
void genKruskalTab(Graph_T * g);
void genKruskalSet(Graph_T * g);


//DLC
int enumCyclesHam(Graph_T * g);
void plus_proche_voisin(Graph_T *g, Sommet_T *s) ;
Ridge_T **  genKruskalTabCut(Graph_T * g, int s);
void pikmin2(Graph_T* g, int s);
void isHamiltonien(Graph_T* g, Ridge_T ** t_rid);
void branch_and_bound(Graph_T* g);

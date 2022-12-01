//
// Created by angom on 09/10/2020.
//

#include <stdlib.h>
#include <stdio.h>

/*Arete*/
typedef struct Ridge_T Ridge_T;
struct Ridge_T
{
    int origin;
    int end;
    int weight;

};

//TP3

Ridge_T* initRidgeS(int, int, int);
Ridge_T* initRidge();
void showRidge(Ridge_T*);
void showAllRidges(Ridge_T**);
void sortInsert(Ridge_T **);
void destroyRidges(Ridge_T **);
void randomRidges(Ridge_T** , int);
void duplicateRidges(Ridge_T** , Ridge_T**);
int countRidges(Ridge_T** t_rid);

//TP4

int totWeightRidges(Ridge_T** t_rid);

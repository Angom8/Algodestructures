#include "Ridge.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*Initialise l'arete à partir du sommet de départ, d'arrivée et du poids*/
Ridge_T* initRidgeS(int a, int b, int c){
    Ridge_T* r = malloc(sizeof(Ridge_T));
    r->origin = a;
    r->end = b;
    r->weight = c;
    return r;
}

/*Initialisation par défaut*/
Ridge_T* initRidge(){
    Ridge_T* r = malloc(sizeof(Ridge_T));
    r->origin = -1;
    r->end = -1;
    r->weight = -1;
    return r;
}

/*Imprime les informations de l'arete*/
void showRidge(Ridge_T* r){
    printf("Arete avec début à %d, fin à %d et poids %d\n", r->origin, r->end, r->weight);
}

/*Imprime les informations du tableau d'aretes*/
void showAllRidges(Ridge_T** t_rid){
    int z = 0;
    while(t_rid[z] != NULL){
        showRidge(t_rid[z]);
        z++;
    }
}
/*Compte le nombre d'aretes présentes dans un tableau d'aretes*/
int countRidges(Ridge_T** t_rid){
    int z = 0;
    while(t_rid[z] != NULL){
    	z++;
    }
    printf("Taille : %d\n", z);
    return z;
}


/*Applique un tri par insertion sur un tableau d'aretes*/
void sortInsert(Ridge_T ** t_rid) {
    int size = countRidges(t_rid);
    int key,j;
    Ridge_T * r_key;
    for (int i = 0; i < size; i++) {
        key = t_rid[i]->weight;
        r_key = t_rid[i];
        j=i-1;
        while (j > -1 && t_rid[j]->weight > key) {
            t_rid[j+1] = t_rid[j];
            j--;
        }
        t_rid[j+1] = r_key;
    }
}


void randomRidges(Ridge_T ** t_rid, int s){
    srand( time( NULL ) );

    int z = 0;
    while(z < s){
        t_rid[z] = initRidgeS(rand() % 101,rand() % 101 ,rand() % 101 );
        z++;
    }
}

void duplicateRidges(Ridge_T ** t_rid, Ridge_T ** t_rid2){
    int z = 0;
    while(t_rid[z] != NULL){
        t_rid2[z] = initRidgeS(t_rid[z]->origin,t_rid[z]->end, t_rid[z]->weight);
        z++;
    }

}

//Detruit toutes les artes d'un tableau, et le tableau en lui-même
void destroyRidges(Ridge_T** t_rid){
    int z = 0;
    while(t_rid[z] != NULL){
    	free(t_rid[z]);
    	z++;
    }
    free(t_rid);
}


/*Compte le nombre d'aretes présentes dans un tableau d'aretes*/
int totWeightRidges(Ridge_T** t_rid){
    int comp = 0, z = 0;
    while(t_rid[z] != NULL){
        comp += t_rid[z]->weight;
        z++;
    }
    return comp;
}


#include "Graph.h"

#define CROSSOVER_PROBABILITY 0.15
#define MUTATION_PROBABILITY 0.50
#define POPULATION_SIZE 1000
#define ITERATION 10000
#define SUP 250000
#define MUTATION_INTENSITY 0.2
#define CROSSOVER_INTENSITY 0.2
#define ENABLE_CROSSOVER 1
#define SHOW_PATH 1
#define DEBUG_PRINT 0

typedef struct Individual_T {
	int * chemin;
	int taille_chemin;
} Individual_T;

typedef struct Population_T {
        Individual_T ** population;
	Graph_T *g;
} Population_T;

//--------------------------------------------------------------------------------------------------- STRUCTURES
//CREATE
Individual_T * creerIndividu(Graph_T *g);

//Avec du recul, pas forcément nécessaire, juste plus clair dans l'algorithme central et pour passer aux fonctions
Population_T * creerPopulation(Graph_T *g);
//INIT
void  initIndividu(Individual_T * ind);


void  initPopulation(Population_T * pop);

//DESTROY
void destroyIndividu(Individual_T * ind);

void destroyPopulation(Population_T * pop);

//Aléatoire sur la population initiale
void shuffle(Population_T * pop);


// APPLICATION DES EFFETS SUR POPULATION
int rechercheSommet(Individual_T * ind, int s);

void appliquerMutation(Individual_T * ind);

void appliquerCrossover(Individual_T * ind,Individual_T * ind2);

//CONCLUSION

//calcul des poids, ma galère sur le TP4 avec mon erreur sur Kruskal m'a donné l'idée du parcours "2 à 2"
int calculerPoidsArbre(Individual_T * ind, Graph_T *g);
//on parcourt tout à la recherche du minimum possible généré
Individual_T* pikmin(Population_T * pop);

//selection des individus
void evolve(Population_T * pop);

void afficherResultats(Population_T * pop);

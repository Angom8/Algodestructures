#include "Genetic.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//--------------------------------------------------------------------------------------------------- STRUCTURES
//CREATE
Individual_T * creerIndividu(Graph_T *g) {

	Individual_T* ind =  malloc(sizeof(Individual_T));
	ind->taille_chemin = g->count;
	ind->chemin = malloc(g->count*sizeof(int));
	
	return ind;
}

//Avec du recul, pas forcément nécessaire, juste plus clair dans l'algorithme central et pour passer aux fonctions
Population_T * creerPopulation(Graph_T *g) {
	Population_T * pop =  malloc(sizeof(Population_T));
	pop->population = malloc(POPULATION_SIZE*sizeof(Individual_T*));
	pop->g = g;

	return pop;

}

//DEBUG
void  showPop(Population_T * pop) {
	//on suppose les graphes bien ordonnés comme ceux des txt
	for (int i = 0; i < POPULATION_SIZE; i++) {
		for(int j=0;j<pop->population[i]->taille_chemin;j++){
			printf("%d ", pop->population[i]->chemin[j]);
		}
		printf("\n");
	}
}

//INIT
void  initIndividu(Individual_T * ind) {
	//on suppose les graphes bien ordonnés comme ceux des txt
	for (int i = 0; i < ind->taille_chemin; i++) {
		ind->chemin[i] = i;
	}
}


void  initPopulation(Population_T * pop) {
	for (int i = 0; i < POPULATION_SIZE; i++) {
		pop->population[i] =creerIndividu(pop->g);
		initIndividu(pop->population[i]);
	}
}

//DESTROY
void destroyIndividu(Individual_T * ind){
/*
	for (int i = 0; i < ind->taille_chemin; i++) {
		free(ind->chemin[i]);
	}
	*/
	free(ind->chemin);
	free(ind);
}

void destroyPopulation(Population_T * pop){
	for (int i = 0; i < POPULATION_SIZE; i++) {
		destroyIndividu(pop->population[i]);
		
	}
	free(pop->population);
	free(pop);
}

//Aléatoire sur la population initiale
void shuffle(Population_T * pop){
	size_t j;
	int t;
	//source rapide https://stackoverflow.com/questions/6127503/shuffle-array-in-c
	for (int i = 0; i < POPULATION_SIZE; i++) {
		for(int k = 0;k < pop->population[i]->taille_chemin;k++){
			j = k + rand() / (RAND_MAX / (pop->population[i]->taille_chemin - k) + 1);
		  	t = pop->population[i]->chemin[j];
		 	pop->population[i]->chemin[j] = pop->population[i]->chemin[k];
		  	pop->population[i]->chemin[k] = t;		
		}
	}
}


// APPLICATION DES EFFETS SUR POPULATION
int rechercheSommet(Individual_T * ind, int s){

	int r = -1, i = 0;
	while(i<ind->taille_chemin){
		if(ind->chemin[i] == s){
			r = i;
			i = ind->taille_chemin+1;//overkill
			break;
		}
		i++;
	}
	
	return r;
}

void appliquerMutation(Individual_T * ind){

	int n = ceil(MUTATION_INTENSITY*(ind->taille_chemin-1));
	int x,y;
	int t;
	for(int k = 0;k < n;k++){
		x = (int) (rand()%(ind->taille_chemin)) ;
		y = (int) (rand()%(ind->taille_chemin)) ;
		t = ind->chemin[x];
		ind->chemin[x] = ind->chemin[y];
		ind->chemin[y] = t;		
	}

}

void appliquerCrossover(Individual_T * ind,Individual_T * ind2){

	int n = ceil(CROSSOVER_INTENSITY*(ind->taille_chemin-1));
	int x,y,pos_x,pos_y;
	int t;
	for(int k = 0;k < n;k++){
		x = (int) (rand()%(n)) ;
		y = (int) (rand()%(n)) ;
		
		pos_x = rechercheSommet(ind, x);
		pos_y = rechercheSommet(ind2, y);
		
		if(pos_x != -1 && pos_y != -1){
			t = ind->chemin[pos_x];
			ind->chemin[pos_x] = ind2->chemin[pos_y];
			ind2->chemin[pos_y] = t;			
		}
	
	}

}

//CONCLUSION

//calcul des poids, ma galère sur le TP4 avec mon erreur sur Kruskal m'a donné l'idée du parcours "2 à 2"
int calculerPoidsArbre(Individual_T * ind, Graph_T *g) {
	int score = 0;
	int end, origin;
	for (int i = 0; i < ind->taille_chemin- 1; i++) {
		origin = ind->chemin[i];
		end = ind->chemin[i+1];
		score += g->m_Adja[origin][end];
	}
	
	//On oublie pas le cycle de la vie
	origin = ind->chemin[ind->taille_chemin-1];
	score += g->m_Adja[origin][0];
	
	return score;
}

//on parcourt tout à la recherche du minimum possible généré
Individual_T* pikmin(Population_T * pop){
	int min = SUP;
	int score;
	Individual_T* heureux_elu = pop->population[0];
	for (int i = 0; i < POPULATION_SIZE; i++) {
		score = calculerPoidsArbre(pop->population[i], pop->g);
		if(min > score){
			min = score;
			heureux_elu = pop->population[i];
		}
	}
	
	return heureux_elu;
}


//selection des individus
void evolve(Population_T * pop){
	/*
	Individual_T ** mutants;
	Individual_T ** enjambements; >>> trop lourd, on utilisera des int **/ 
	int * mutants = (int * ) malloc((POPULATION_SIZE)*sizeof(int));
	int * enjambements  = (int * ) malloc((POPULATION_SIZE)*sizeof(int));
	int i_m = 0, i_e = 0;
	int rm = 0,re =0;
	
	for (int i = 0; i < POPULATION_SIZE; i++) {
		rm = rand()%100;
		
		if(MUTATION_PROBABILITY*100 > rm){
			mutants[i_m] = i;
			i_m++;
		}
		
		#if ENABLE_CROSSOVER == 1
		re = rand()%100;
		
		if(CROSSOVER_PROBABILITY*100 > re){
			mutants[i_e] = i;
			i_e++;
		}		
		#endif
	}

	#if DEBUG_PRINT == 1
	printf("-- Mutants : %d", i_m);
	#endif
	for (int i = 0; i < i_m; i++) {
		appliquerMutation(pop->population[mutants[i]]);
	}
	#if ENABLE_CROSSOVER == 1
	#if DEBUG_PRINT == 1
	printf(" et Crossovers : %d", i_e);
	#endif
	for (int i = 0; i < i_e-1; i+=2) {
		//la position est en soi aléatoire
		appliquerCrossover(pop->population[enjambements[i]], pop->population[enjambements[i+1]]);
	}
	#endif
	#if DEBUG_PRINT == 1
	printf("\n");
	#endif
	free(mutants);
	free(enjambements);
}

void afficherResultats(Population_T * pop){
    Individual_T* heureux_elu = pikmin(pop);
    printf("Le meilleur chemin trouvé a un poids de %d\n", calculerPoidsArbre(heureux_elu, pop->g));
    #if SHOW_PATH == 1
    printf("-------------------\n");
    for (int i = 0; i < heureux_elu->taille_chemin- 1; i++) {
    	printf("%d - ", heureux_elu->chemin[i]);
    }
    printf("\n-------------------\n");
    #endif
}


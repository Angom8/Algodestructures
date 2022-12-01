#include "Genetic.h"
#include <time.h>
#include <sys/timeb.h>

int main(int argc, char **argv) {
    struct timeb tav, tap ;
    double te;
    
    if(argc < 2){
    	printf("Utilisation : ./main {nomfichier} {NBITERATIONS}\n");
    	return EXIT_FAILURE;
    }
    Graph_T *g = initGraphWeight(argv[1]);
    
    wait(0);
    
    int iteration = ITERATION;
    if(argc > 2){
    	iteration = atoi(argv[2]);
    }
    
    //pour les appels au random
    srand((unsigned)time(NULL)); 

    ftime(&tav);
    Population_T* pop = creerPopulation(g);
    initPopulation(pop);
    shuffle(pop);

    for(int i = 0; i < iteration; i++) {
    	printf("Genération %d\n", i);
    	evolve(pop);
    }
    
    ftime(&tap);
    te = (double)((tap.time*10000+tap.millitm)-(tav.time*10000+tav.millitm))/10000 ;
    printf("Temps d'execution : %f\n",  te);
    
    afficherResultats(pop);
    
    destroyPopulation(pop);
    destroyGraph(g);
    
    exit(EXIT_SUCCESS);

}




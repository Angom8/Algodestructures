//
// Created by angom on 02/10/2020.
//
#include <zconf.h>
#include "Graph.h"
#define SUP 250000

int date = 0;

Graph_T* initGraph(char * f) {
    Graph_T * g = malloc(sizeof(Graph_T));
    char chaine[TAILLE_MAX];
    char chaine2[TAILLE_MAX];
    int i, a, b, current_s = -1, k=0;
    List_T * insert_list = initList();
    Cell_T* reading_cell;
    int off;

    FILE * fichier = fopen(f, "r");
    if ( fichier == NULL ) {
        printf( "Cannot open file %s\n", f);
        exit(EXIT_FAILURE);
    }

    off = fscanf(fichier, "%s %d", chaine, &(g->count));
    off = fscanf(fichier, "%s %d", chaine, &(g->orientation));
    off = fscanf(fichier, "%s %d", chaine, &(g->has_value));
    off = fscanf(fichier, "%s", chaine);

    g->adja = malloc(g->count * sizeof(List_T));
    g->m_Adja = malloc(g->count * sizeof(int*));
    for(i=0;i<g->count;i++){
        g->m_Adja[i]= calloc(g->count, sizeof(int));
    }
    off = fscanf(fichier, "%s %s", chaine, chaine2);
    do{
        sscanf(chaine, "%d", &a);
        sscanf(chaine2, "%d", &b);

        if(current_s != a){
            if(current_s != -1) {
                g->adja[current_s] = insert_list;
                if(current_s + 1 != a){
                    while(current_s < a-1){
                        current_s ++;
                        g->adja[current_s] = initList();
                    }
                    current_s = a;
                }
                else {
                    current_s = a;
                }
            }
            else{
                current_s = a;
            }
            insert_list = initList();
        }
        reading_cell = initSCell(b);
        insertList(insert_list, reading_cell);

        g->m_Adja[current_s][b] = 1;
        if(g->orientation != 1) g->m_Adja[b][current_s] = 1;
        off = fscanf(fichier, "%s %s", chaine, chaine2);
    }while (strcmp(chaine,"FIN_DEF_ARETES") != 1 && feof(fichier) != 1 );

    g->adja[current_s] = insert_list;

    while(k<g->count){
        if( ! g->adja[k]) g->adja[k] = initList();
        k++;
    }

    return g;
}


//Affiche le graphe et toutes ses informations
void showGraph(Graph_T* g){
    printf("Nombre de sommets : %d\n", g->count);
    printf("Orienté ? : %d\n", g->orientation);
    printf("Avec valeurs ? : %d\n", g->has_value);

    if(g->adja != NULL){
        int z = 0;
        while(g->adja[z] != NULL){
            printf("%d ", z);
            showList(g->adja[z]);
            z++;
        }
        for(int i=0;i<g->count;i++){
            for(int j=0;j<g->count;j++){
                printf("%d ", g->m_Adja[i][j]);
            }
            printf("\n");
        }
    }


}

//Détruit le graph
void destroyGraph(Graph_T* g){

    int z = 0;
    while(g->adja[z] != NULL){
        destroyList(g->adja[z]);
        z++;
    }
    free(g->adja);

    for(int i=0;i<g->count;i++){
      free(g->m_Adja[i]);
    }
    free(g->m_Adja);
    free(g);

}


//-------------------------------------------------------------------------------------------------------------------- TP2


//Application pure et dure du code
void parcoursLargeur(Graph_T * g, Sommet_T* s){

    File_H *f = initFile(g->count*g->count);
    Sommet_T *u;
    int i, j, z=0;
    Sommet_T ** t_som = malloc(g->count * sizeof(Sommet_T*));
    while(z < g->count){
        if(z != s->val) {
            u = initSom(z);
            t_som[z] = u;
        }
        else{
            t_som[z] = initSom(s->val);
        }
        z++;
    }

    //Application de l'algorithme du cours
    t_som[s->val]->color = 1;
    t_som[s->val]->distance = 0;
    enfiler(f, t_som[s->val]);
   
    while(isEmptyFile(f) != 1){
        u = defiler(f);
        i = u->val;
        for(j=0;j<g->count;j++){
            if(g->m_Adja[i][j] >=1){
                if(t_som[j]->color == 0){
                    t_som[j]->color = 1;                 
                    t_som[j]->distance = u->distance + 1;
                    t_som[j]->father = u->val;
                    enfiler(f, t_som[j]);
                }
            }
        }
        t_som[i]->color = 2;

        
    }

    destroyFile(f);
    free(t_som);
}

/*Procédure récusrive de récupération du chemin*/
void afficherCheminSub(Sommet_T ** t_som, int s, int v){

    //application du code du cours
    if(s == v){
        printf("%d ", s);
    }
    else{
        if(t_som[v]->father == -1){

        }
        else{
            afficherCheminSub(t_som, s, t_som[v]->father);
            printf("%d ", v);
        }
    }

}

/*Affiche le chemin le plus court à partir d'un sommet donné*/
void afficherChemin(Graph_T * g, Sommet_T* s, int fin){

    //initialisation des variables
    File_H *f = initFile(g->count*g->count);
    int i, j, z=0;
    Sommet_T ** t_som = malloc(g->count * sizeof(Sommet_T*));
    Sommet_T * u;
    //récupération des sommets
    while(z < g->count){
        if(z != s->val) {
            t_som[z]  = initSom(z);
        }
        else{//le sommet s est déjà fourni
            t_som[z] = initSom(s->val);
        }
        z++;
    }

    //Application de l'algorithme du cours
    t_som[s->val]->color = 1;
    t_som[s->val]->distance = 0;
    enfiler(f, t_som[s->val]);
   

    while(isEmptyFile(f) != 1){
        u = defiler(f);
        i = u->val;
        for(j=0;j<g->count;j++){
            if(g->m_Adja[i][j] >=1){
                if(t_som[j]->color == 0){
                    t_som[j]->color = 1;                 
                    t_som[j]->distance = u->distance + 1;
                    t_som[j]->father = u->val;
                    enfiler(f, t_som[j]);
                }
            }
        }
        t_som[i]->color = 2;

        
    }

    afficherCheminSub(t_som,s->val, fin);
    printf("\n");
    z=0;

    
    while(z < g->count){
        if(t_som[z] != NULL) {
            free(t_som[z]);
        }
        z++;
    }

    free(t_som);

}

/*Procédure récursive du parcours en profondeur*/
void visiterpp(Graph_T *g, Sommet_T ** t_som, int u){

    //Application de l'algo du cours
    int v;
    t_som[u]->color = 1;

    date++;

    t_som[u]->date = date;
    for(v=0;v<g->count;v++){
        if(g->m_Adja[u][v] >=1){
            if(t_som[v]->color == 0){
                t_som[v]->father = u;
                visiterpp(g, t_som, v);
            }
        }
    }

    date++;

    t_som[u]->datef = date;
    t_som[u]->color = 2;
}

/*Parcourt en profondeur le Graphe*/
void parcours_profondeur(Graph_T *g){

    //initialisation des variables
    date = 0;
    Sommet_T *u;
    int i, z=0;

    //récupération des sommets
    Sommet_T ** t_som = malloc(g->count * sizeof(Sommet_T*));
    while(z < g->count){
        u = initSom(z);
        t_som[z] = u;
        z++;
    }

    //Appel de la fonction récursive
    for(i=0;i<g->count;i++){
        if(t_som[i]->color == 0){
            visiterpp(g, t_som, i);

        }
        
    }

    //désallocation
    z = 0;
    while(z < g->count){
    	printf("Sommet : %d, date debut : %d, date fin : %d, pere : %d\n", z, t_som[z]->date, t_som[z]->datef, t_som[z]->father);
        free(t_som[z]);
        z++;
    }
    free(t_som);
    
    date = 0;

}

//Parcourt le graphe en profondeur itérativement
void parcours_profondeur_iteratif(Graph_T *g){

    //initialisation des varaibles
    Sommet_T *u, *v;
    Pile_T * p;
    int i, w, z=0;

    //Conversion des sommets sous forme d'objets sommets
    Sommet_T ** t_som = malloc(g->count * sizeof(Sommet_T*));
    while(z < g->count){
        u = initSom(z);
        t_som[z] = u;
        z++;
    }

    p = initPile(g->count);

    //Application du code vu en cours
    for(i=0;i<g->count;i++){
        if(t_som[i]->color == 0){
            t_som[i]->color = 1;
            stack(p, t_som[i]);
            while(isEmptyPile(p) != 1) {
                v = unstack(p);

                for (w = 0; w < g->count; w++) {
                    if (g->m_Adja[v->val][w] >= 1) {
                        if (t_som[w]->color == 0) {
                            t_som[w]->color = 1;
                            t_som[w]->father = v->val;
                            stack(p, t_som[w]);
                        }
                    }
                }
                v->color = 2;

            }
        }
    }

    //désallocation
    z = 0;
    while(z < g->count){
	showSommet(t_som[z]);
        if(t_som[z]) free(t_som[z]);
        z++;
    }

    free(t_som);

}

//-------------------------------------------------------------------------------------------------------------------- TP3

//On pourrait faire un énorme if/else en passant à l'appel un booléen mais autant faire une nouvelle fonction traitant proprement les poids
Graph_T* initGraphWeight(char * f) {

    //Initialisations
    Graph_T * g = malloc(sizeof(Graph_T));
    char chaine[TAILLE_MAX];
    char chaine2[TAILLE_MAX];
    char chaine3[TAILLE_MAX];
    int i, a, b,c, current_s = -1, k=0;
    List_T * insert_list = initList();
    Cell_T* reading_cell;
    int off;

    //lecture du fichier
    FILE * fichier = fopen(f, "r");
    if ( fichier == NULL ) {
        printf( "Cannot open file %s", f);
        exit( 0 );
    }

    //Lecture des premiers paramètres
    off = fscanf(fichier, "%s %d", chaine, &(g->count));
    off = fscanf(fichier, "%s %d", chaine, &(g->orientation));
    off = fscanf(fichier, "%s %d", chaine, &(g->has_value));
    off = fscanf(fichier, "%s %d", chaine, &off);
    off = fscanf(fichier, "%s", chaine);

    //Initialisation des paramètres complexes
    g->adja = malloc(g->count * sizeof(List_T));
    g->m_Adja = malloc(g->count * sizeof(int*));
    for(i=0;i<g->count;i++){
        g->m_Adja[i]= calloc(g->count, sizeof(int));
    }

    //Lecture des aretes et sommets
    off = fscanf(fichier, "%s %s %s", chaine, chaine2, chaine3);
    do{

        //Lecture des deux sommets et du poids
        sscanf(chaine, "%d", &a);
        sscanf(chaine2, "%d", &b);
        sscanf(chaine3, "%d", &c);

        //Si on change de sommet, on ajoute un élément de liste adjacente ou une arete
        if(current_s != a){
            if(current_s != -1) {
                g->adja[current_s] = insert_list;
                if(current_s + 1 != a){
                    while(current_s < a-1){
                        current_s ++;
                        g->adja[current_s] = initList();
                    }
                    current_s = a;
                }
                else {
                    current_s = a;
                }
            }
            else{
                current_s = a;
            }
            insert_list = initList();
        }
        reading_cell = initSWCell(b,c);
        insertList(insert_list, reading_cell);

        //traitement de la matrice
        g->m_Adja[current_s][b] = c;
        if(g->orientation != 1) g->m_Adja[b][current_s] = c;
        off = fscanf(fichier, "%s %s %s", chaine, chaine2, chaine3);

    }while (strcmp(chaine,"FIN_DEF_ARETES") != 1 && feof(fichier) != 1 );

    //oui bon ça marche
    g->adja[current_s] = insert_list;

    //Ajoute les sommets n'ayant pas d'aretes propres
    while(k<g->count){
        if( ! g->adja[k]) g->adja[k] = initList();
        k++;
    }

    return g;
}

/*Lis la matrice d'ajacence pour récupérer les différentes arrêtes sous forme d'un tableau de structures d'aretes*/

Ridge_T** getRidges(Graph_T * g){
    //inialisation des variables
    Ridge_T** t_rid = malloc(g->count*g->count * sizeof(Ridge_T*));
    int z =0;

    //Le graphe est-il orienté ?
    if(g->orientation < 1){//on traite les cas où l'utilisateur a fait le malin à mettre d'autres valeurs que 0 et 1
        for(int i=0;i<g->count;i++){
            for(int j=i;j<g->count;j++){
                if(g->m_Adja[i][j] > 0) {//voir plus haut
                    t_rid[z] = initRidgeS(i, j, g->m_Adja[i][j]);
                    z++;
                }
            }
        }
    }
    else{
        //il est orienté
        for(int i=0;i<g->count;i++){
            for(int j=0;j<g->count;j++){
                if(g->m_Adja[i][j] > 0) {
                    t_rid[z] = initRidgeS(i, j, g->m_Adja[i][j]);
                    z++;
                }
            }
        }
    }

    return t_rid;
}

void genKruskalTab(Graph_T * g){
    int icc, i, j= 0, z = 0;
    Ridge_T ** t_rid_r = malloc(g->count*g->count*sizeof(Ridge_T*));
    Ridge_T ** t_rid = getRidges(g);
    int * cc = malloc(g->count * sizeof(int));
    
    printf(" --- ARETES DU GRAPHE TRIEES \n");
    
    sortInsert(t_rid); //ou avec sort Heap, différence négligeable pour le graph 5
    
    showAllRidges(t_rid);

    for(i = 0;i<g->count;i++){
        cc[i] = i;
    }
    while(t_rid[z] != NULL){
        if(cc[t_rid[z]->origin] != cc[t_rid[z]->end]){
            t_rid_r[j] = initRidgeS(t_rid[z]->origin, t_rid[z]->end, t_rid[z]->weight);
            j++;
            icc = cc[cc[t_rid[z]->end]];
            for(i=0;i<g->count;i++){
                if(cc[i] == icc){
                    cc[i] = cc[t_rid[z]->origin];
                }
            }
        }

        z++;
    }
    printf(" --- ARETES DE L'ARBRE COUVRANT \n");
    showAllRidges(t_rid_r);
    printf("||| Poids de l'arbre : %d\n", totWeightRidges(t_rid_r));

    destroyRidges(t_rid_r);
    destroyRidges(t_rid);
    free(cc);


}

void genKruskalSet(Graph_T * g){

    int i, j = 0, z = 0;

    Ridge_T ** E = malloc(g->count * sizeof(Ridge_T*));
    Set_H ** tmp = malloc(g->count * sizeof(Set_H));

    Ridge_T ** t_rid = getRidges(g);

    printf(" --- ARETES DU GRAPHE TRIEES \n");
    
    sortInsert(t_rid); //ou avec sort Heap, différence négligeable pour le graph 5
    showAllRidges(t_rid);

    for(i = 0;i<g->count;i++){
        tmp[i] = initSet(i);
    }

    while((t_rid[z] != NULL) & (j<g->count-1)) {
        if(inSameSet(tmp[t_rid[z]->origin], tmp[t_rid[z]->end]) != 1){
            E[j] = t_rid[z];
            j++;
            fuseSet(tmp[t_rid[z]->origin], tmp[t_rid[z]->end]);
        }
        z++;
    }

    printf(" --- ARETES DE L'ARBRE COUVRANT \n");
    showAllRidges(E);
    printf("||| Poids de l'arbre : %d\n", totWeightRidges(E));

    free(tmp);
    destroyRidges(t_rid);
    free(E);
}


void afficherCycleHam(int *t, int n, int longueur) {
	int i;
	printf("\nLongueur : %d | ", longueur);

	for (i = 0; i < n; i++){
		printf("%d ", t[i]);
		
	}
	
	printf("\n");
}
void permuter(int *t, int i, int j) {
	int temp = t[i];
	t[i] = t[j];
	t[j] = temp;
}
	
void permutationsCycles(int *t, int i, int n, int longueur, Graph_T *graphe, int *tabMin, int *min) {
	int j, fin = 0;

	if (i == n) {
		longueur += graphe->m_Adja[t[n-1]][t[0]];
		afficherCycleHam(t, n, longueur);
		if (longueur < *min) {
			*min = longueur;
			for (j = 0; j < n; j++) {
				tabMin[j] = t[j];
			}
		}
	}
	else {
		j = i;
		while (!fin && j < n) {
			permuter(t, i, j);
			longueur += graphe->m_Adja[t[i-1]][t[i]];
			permutationsCycles(t, i+1, n, longueur, graphe, tabMin, min);
			longueur -= graphe->m_Adja[t[i-1]][t[i]];
			permuter(t, i, j);
			if (t[1] == n - 1) fin = 1;
			j++;
		}
	}
}

int enumCyclesHam(Graph_T *graphe) {
	
	int n = graphe->count, i, longueur = 0, longueurMin = INT_MAX;

	int *tabSommets = (int *) malloc(sizeof(int) * n);
	int *tabCycleHamMin = (int *) malloc(sizeof(int) * n);
	
	for (i = 0; i < n; i++) {
		tabSommets[i] = i;
		tabCycleHamMin[i] = 0;
	}
	
	permutationsCycles(tabSommets, 1, n, longueur, graphe, tabCycleHamMin, &longueurMin);
	printf("\nCycle hamiltonien minimum :\n");
	
	for (i = 0; i < n; i++) printf("%d ", tabCycleHamMin[i]);
	printf("\nLongueur : %d\n", longueurMin);
	free(tabSommets);
	free(tabCycleHamMin);
	return 0;
}

/*L'heuristique du plus proche voisin consiste à : Choisir un sommet de départ X, Tant que tous les sommets ne sont pas encore visités faire l'opération suivante se rendre au sommet le plus proche pas encore visité.*/
void plus_proche_voisin(Graph_T *g, Sommet_T *s) {
	    int i, j, t_weight = 0, z=0;
	    Sommet_T ** t_som = malloc(g->count * sizeof(Sommet_T*));
	    Sommet_T ** t_som_result = malloc(g->count * sizeof(Sommet_T*));
	    Sommet_T * u;
	    
	    int min = SUP;
	    int s_min = 0;
	    
	    int count_col=1;
	    //récupération des sommets
	    while(z < g->count){
		if(z != s->val) {
		    t_som[z]  = initSom(z);
		}
		else{//le sommet s est déjà fourni
		    t_som[z] = initSom(s->val);
		    u =  t_som[z];
		    t_som_result[count_col-1] =  t_som[z];
		}
		z++;
	    }


		
	    //Application de l'algorithme du cours (CHPS0501)
	    t_som[s->val]->color = 1;
	    
	    //Tant que tous les sommets ne sont pas parcourus
	    while(count_col !=  g->count){
	        s_min = 0;
	    	min = SUP;
	    	i = u->val;
	    	//parcours de la matrice d'adjacence
	    	for(j=0;j<g->count;j++){
		    if(g->m_Adja[i][j] >0){
		        //si non parcouru
		        if(t_som[j]->color == 0){
		        //si min
		            if(g->m_Adja[i][j]< min){
		            	min = g->m_Adja[i][j];
		            	s_min = j;
		      
		            }
		        }
		    }
		}
		t_som[s_min]->color = 1;
		u = t_som[s_min];
		count_col++;
		t_som_result[count_col-1] = u;
		t_weight += min;
		
	    }
	    
	    printf("Parcours : ");
	    for(i=0;i<g->count;i++){
	    	if(i== g->count-1){
	    		printf("%d, total : %d\n",t_som_result[i]->val, t_weight);
	    	}
	    	else{
	    		printf("%d - ",t_som_result[i]->val);
	    	}
	    }
	    
	    z=0;
	    while(z < g->count){
		if(t_som[z] != NULL) {
		    free(t_som[z]);
		}
		z++;
	    }
	    
	    free(t_som);
	    free(t_som_result);
}


Ridge_T ** genKruskalTabCut(Graph_T * g, int s){
    int icc, i, j= 0, z = 0;
    Ridge_T ** t_rid_r = malloc(g->count*g->count*sizeof(Ridge_T*));
    Ridge_T ** t_rid_f = malloc((g->count-2)*sizeof(Ridge_T*));
    Ridge_T ** t_rid = getRidges(g);
    int * cc = malloc(g->count * sizeof(int));
    
    
    sortInsert(t_rid); //ou avec sort Heap, différence négligeable pour le graph 5
   

    for(i = 0;i<g->count;i++){
        cc[i] = i;
    }
    while(t_rid[z] != NULL){
        if(cc[t_rid[z]->origin] != cc[t_rid[z]->end]){
            t_rid_r[j] = initRidgeS(t_rid[z]->origin, t_rid[z]->end, t_rid[z]->weight);
            j++;
            icc = cc[cc[t_rid[z]->end]];
            for(i=0;i<g->count;i++){
                if(cc[i] == icc){
                    cc[i] = cc[t_rid[z]->origin];
                }
            }
        }

        z++;
    }
    i = 0, j = 0;
    while(i<g->count-1){
    	if(t_rid_r[i]->end != s && t_rid_r[i]->origin != s){
    	
    		printf("%d, %d\n", t_rid_r[i]->origin , t_rid_r[i]->end);
    		t_rid_f[j] = t_rid_r[i];
    		j++;
    	}
    	i++;
    }
    
    printf(" --- ARETES DE L'ARBRE COUVRANT \n");
    showAllRidges(t_rid_f);
    printf("||| Poids de l'arbre : %d\n", totWeightRidges(t_rid_f));


    //destroyRidges(t_rid);
    free(cc);
    return(t_rid_f);

}

void pikmin2(Graph_T* g, int i){
	    int j, z=0;
	    Sommet_T ** t_som = malloc(g->count * sizeof(Sommet_T*));
	    
	    int min = SUP;
	    int s_min = 0;
	    
	    //récupération des sommets
	    while(z < g->count){
	 	t_som[z]  = initSom(z);
		z++;
	    }
	    z = 0;
	    printf("Sommets à ajouter pour cycler : ");
	    //Tant que tous les sommets ne sont pas parcourus
	    while(z < 2){
	        s_min = 0;
	    	min = SUP;
	    	//parcours de la matrice d'adjacence
	    	for(j=0;j<g->count;j++){
		    if(g->m_Adja[i][j] >0 && i!=j){
		        //si non parcouru
		        if(t_som[j]->color == 0){
		        //si min
		            if(g->m_Adja[i][j]< min){
		            	min = g->m_Adja[i][j];
		            	s_min = j;
		      
		            }
		        }
		    }
		}
		t_som[s_min]->color = 1;
		z++;
	   }
	    
	   printf("\n");
	   free(t_som);
}

int * pikmin2Opti(Graph_T* g, int i){
	    int j,ic = 0, z=0;
	    Sommet_T ** t_som = malloc(g->count * sizeof(Sommet_T*));
	    
	    int min = SUP;
	    int s_min = 0;
	    
	    int * retour  = malloc(2*sizeof(int));
	    
	    //récupération des sommets
	    while(z < g->count){
	 	t_som[z]  = initSom(z);
		z++;
	    }
	    z = 0;
	    //Tant que tous les sommets ne sont pas parcourus
	    while(z < 2){
	        s_min = 0;
	    	min = SUP;
	    	//parcours de la matrice d'adjacence
	    	for(j=0;j<g->count;j++){
		    if(g->m_Adja[i][j] >0 && i!=j){
		        //si non parcouru
		        if(t_som[j]->color == 0){
		        //si min
		            if(g->m_Adja[i][j]< min){
		            	min = g->m_Adja[i][j];
		            	s_min = j;
		      
		            }
		        }
		    }
		}
		t_som[s_min]->color = 1;
		retour[ic] = min;
		ic++;
		z++;
	   }
	   
	 
	   free(t_som);
	   return retour;
}

void isHamiltonien(Graph_T* g, Ridge_T ** t_rid){

 	int * cc = calloc(g->count,sizeof(int));
 	int r = 1;
 	
	//n - 1 sommets, n-2 aretes dans le cycle à tester
	for(int i = 0;i<g->count-2;i++){
		cc[t_rid[i]->end] ++;
		cc[t_rid[i]->origin] ++;
		
		if(cc[t_rid[i]->end]  > 2 || cc[t_rid[i]->origin] > 2){
			r = 0;
			break;
		}
	}
	if(r==1){
		  printf("Cycle hamiltonien : oui !\n");
	}
	else{
		printf("Cycle hamiltonien : non !\n");
	}
	
	
}


int isHamiltonienOpti(Graph_T* g, Ridge_T ** t_rid){

 	int * cc = calloc(g->count,sizeof(int));
 	int r = 1;
 	
	//n - 1 sommets, n-2 aretes dans le cycle à tester
	for(int i = 0;i<g->count-2;i++){
		cc[t_rid[i]->end] ++;
		cc[t_rid[i]->origin] ++;
		
		if(cc[t_rid[i]->end]  > 2 || cc[t_rid[i]->origin] > 2){
			r = 0;
			break;
		}
	}
	return r;
	
	
}



int findBreaker(Graph_T* g, Ridge_T ** t_rid){

 	int * cc = calloc(g->count,sizeof(int));
 	int r = 1;
 	
	//n - 1 sommets, n-2 aretes dans le cycle à tester
	for(int i = 0;i<g->count-2;i++){
		cc[t_rid[i]->end] ++;
		cc[t_rid[i]->origin] ++;
		
		if(cc[t_rid[i]->end] > 2){
			r = t_rid[i]->end;
			break;
		}
		if(cc[t_rid[i]->origin] > 2){
			r = t_rid[i]->origin;
			break;
		}
	}
	return r;
	
	
}

//FONCTION POUR LE BRANCH and BOUND
BandB_T * solve_recurse(Graph_T * g, int s, Ridge_T ** t_rid){
    int icc, i, j= 0, end, origin, z;
    int * chemin = malloc(g->count * sizeof(int));
    int s_min, min, current_s;
    
    BandB_T * retour = malloc(sizeof(BandB_T*));
    retour->t_rid = malloc((g->count-1)*sizeof(Ridge_T*));
    int count_col = 1;
    chemin[0] = s;

    int * t_color = calloc(g->count, sizeof(int));
   
    //Application de l'algorithme du cours
    t_color[s] = 1;
     current_s = s;
     //Tant que tous les sommets ne sont pas parcourus
     while(count_col !=  g->count){
	        s_min = 0;
	    	min = SUP;
	    	i = current_s;
	    	//parcours de la matrice d'adjacence
	    	for(j=0;j<g->count;j++){
		    if(g->m_Adja[i][j] >0){
		        //si non parcouru
		        if(t_color[j]== 0){
		        //si min
		            if(g->m_Adja[i][j]< min){
		            	min = g->m_Adja[i][j];
		            	s_min = j;
		      
		            }
		        }
		    }
		}
		t_color[s_min] = 1;
		current_s = s_min;
		chemin[count_col]= s_min;
		count_col++;
    }
    
    
    icc = 0;
   //on commence sans le premier sommet, sans le dernier PAS DU TOUT OPTI
    for(i = 1;i<g->count-1;i++){
    	origin = chemin[i];
    	end = chemin[i+1];	
    	z=0;
    	while(t_rid[z] != NULL){
    		if((t_rid[z]->end == end && t_rid[z]->origin == origin) || (t_rid[z]->end == origin && t_rid[z]->origin == end)){
    			retour->t_rid[icc] = t_rid[z];
    			retour->weight += t_rid[z]->weight;
    			icc++;
    		}
    		z++;
    	}
    	
    
    }

    //destroyRidges(t_rid);
    free(chemin);
    return(retour);

}

int branch_and_bound_recurse(Graph_T* g, int best, int sommet,Ridge_T ** t_rid_global){
	int breaker;
	int save_weight;
	int r_best = best;
	int * add_on;
	//Évaluer le sommet par la fonction d'évaluation
	BandB_T * current = solve_recurse(g,sommet,t_rid_global);
	
	//aretes manquants
	add_on = pikmin2Opti(g, 0);
	current->weight += add_on[0] + add_on[1];
	free(add_on);	
	
	//Si l'évaluation obtenue est plus petite que la borne
	printf("- Sans amélioration de base\n");
	if(current->weight < r_best){
		
		//Vérifier si le graphe obtenu est un cycle hamiltonien
		if(isHamiltonienOpti(g, current->t_rid) == 1){
			//Mettre à jour la borne avec la longueur du cycle
			r_best = current->weight;
			printf("- Nouvelle borne trouvée : %d\n", r_best);
		}
		else{
			printf("- Pas Hamiltonien\n");
			//Trouver dans le graphe un sommet de degré strictement supérieur à 2
			breaker = findBreaker(g, current->t_rid);
				
			//pour toutes ses aretes
			for(int a=0;a<g->count;a++){
				if(current->t_rid[a]->origin != breaker  && current->t_rid[a]->end != breaker){
					/*Interdire l'arête Mettre un poids infini*/
					save_weight = current->t_rid[a]->weight;
					current->t_rid[a]->weight = SUP;
					g->m_Adja[current->t_rid[a]->origin][current->t_rid[a]->end] = SUP;
					
					printf("- Résolution %d (appel par : %d)\n", breaker, sommet);
					printf("- -");
					/*Separation-Evaluation Avec l'arête interdite*/
					r_best = branch_and_bound_recurse(g, best,breaker, t_rid_global);
					
					/*Lever l'interdiction de l'arête Remettre le poids initial*/
					current->t_rid[a]->weight = save_weight ;
					g->m_Adja[current->t_rid[a]->origin][current->t_rid[a]->end]  = save_weight;
				}

			}
		}
		
	}
	free(current->t_rid);
	free(current);
	
	return r_best;
}

void branch_and_bound(Graph_T* g){
	int sommet = 0;
	int best;
	int a = 0;
	int save_weight;
	int * add_on;
	//pour éviter d'en regen en boucle
	Ridge_T ** t_rid_global = getRidges(g);
	
	//contient le tableau d'aretes, le poids sans l'origine, les 2 deux aretes manquantes
	BandB_T* current;
	printf("Première évaluation, ");
	current = solve_recurse(g,sommet,t_rid_global);
	
	//aretes manquants
	add_on = pikmin2Opti(g, 0);
	current->weight += add_on[0] + add_on[1];
	free(add_on);	
	
	//première évaluation
	best = current->weight;
	
	printf("Borne : %d\n", best);
	printf("Arbre récursif de résolution\n");	
	for(sommet;sommet<g->count;sommet++){
		printf("- Résolution %d (premier appel)\n", sommet);
		printf("- ");
		best = branch_and_bound_recurse(g ,best, sommet,t_rid_global);
		
		
	}
	printf("Best : %d\n", best);
	
	free(current);
	destroyRidges(t_rid_global);

}




			

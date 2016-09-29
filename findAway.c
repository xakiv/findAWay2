#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "findAway.h"
#include "minpriorityqueue.h"
#include "readGraph.h"


void writeSolution(Solution_t *sol, char *logsolFile)
{
    int i;
    FILE* file = fopen(logsolFile, "w");
    if(!file)
    {
        printf("File did not opened");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s \n", sol->graphName);
    fprintf(file, "%s \n", sol->algoName);
    fprintf(file, "%d %s %d \n", sol->origin, "to", sol->destination);
    fprintf(file, "%s %d %s \n","Found in", sol->nSteps, "steps");
    fprintf(file, "%s %.6f \n", "length", sol->distance);
    //fprintf(file, "Sommets qui composent le chemin trouvé par l'algorithme \n");
    for(i=0; i<=sol->nVertices; i++)
    {
        (i>0) ? fprintf(file,", %d",sol->vertices[i]) : fprintf(file,"%d",sol->vertices[i]);
    }
    fprintf(file,"\n%d %s \n", sol->nExploredVertices, "explored nodes");
    //fprintf(file, "liste des sommets visités \n");
    for(i=0; i<sol->nExploredVertices; i++)
    {
        (i>0) ? fprintf(file,", %d",sol->exploredVertices[i]) : fprintf(file,"%d",sol->exploredVertices[i]);
    }
    fclose(file);
}

Solution_t *dijkstra(char *graphFile,Graphe *G, int idOr, int idDest){
    //Allocation memoire
    Solution_t *solDij=NULL;
    solDij = calloc(1, sizeof(Solution_t));
    if ( solDij == NULL )
    {
        fprintf(stderr,"Allocation solDij impossible \n");
        exit(EXIT_FAILURE);
    }else{
        solDij->graphName=calloc((strlen(graphFile) + 1),sizeof(char));
        solDij->algoName=calloc((strlen("Dijkstra") + 1),sizeof(char));
        if ( solDij->graphName != NULL && solDij->algoName != NULL )
        {
            solDij->graphName=graphFile;
            solDij->algoName="Dijkstra";
        }else {
            fprintf(stderr,"Allocation Names impossible \n");
            exit(EXIT_FAILURE);
        }
        solDij->origin=idOr;
        solDij->destination=idDest;
        solDij->vertices=calloc(G->nbSommet,sizeof(int));
        solDij->exploredVertices=calloc(1,sizeof(int));
    }
    //Initialisation variables solution
    solDij->distance=0.0;
    solDij->nExploredVertices=0;
    solDij->nSteps=0;
    solDij->nVertices=0;
    //Declaration variables
    int i, idMin;
    float dist[G->nbSommet]; //attribue provisoirement un poids entre S[origine] et un sommet S[i]
    int parent[G->nbSommet]; //contiendra l'id du dernier parent du sommet visité
    bool vu[G->nbSommet];
    Sommet sCourant;
    Arc *tabAdja=NULL;

    //Etape 1a: les distances sont initilisés a l'infini et les parents à -1
    for(i=0; i < G->nbSommet; i++)
    {
        //d[v] ← ∞
        dist[i] = FLT_MAX;
        //p[v] ← NULL
        parent[i] = -1;
        //E ← FALSE
        vu[i] = false;
    }
    //Etape 1b: le point d'origine initialisé (d[s] ← 0)
    dist[idOr]=0.0;
    parent[idOr] = -1;

    //Etape 2:
    heap_t *Tas = create_heap(G->nbSommet);
    push_heap(Tas, idOr, dist[idOr]);

    /*Étape 3: Parmi les sommets dont le poids n'est pas définivement fixé
    choisir le sommet S_voisin de poids p minimal.*/
    while (!isEmpty(Tas)){
       idMin= extract_min(Tas);
       solDij->nSteps++;
       //en fonction de extract_min(Tas) choisir l'indice du sommet au poids le plus faible
       sCourant=G->tabSommets[idMin];
       //on indique le nouveau sommet exploré et incremente le nb de sommet visité
       solDij->exploredVertices[solDij->nExploredVertices]=sCourant.id;
       solDij->nExploredVertices++;
       solDij->exploredVertices=realloc(solDij->exploredVertices,((solDij->nExploredVertices+1)*sizeof(int)));
       //on explore les sommet adjacents de sCourant
       tabAdja=neighbours(G,sCourant.id);
       for (i=0; i<sCourant.nbAdj; i++){
            //on compare les distances
            if (vu[tabAdja[i].idDest]==false && dist[tabAdja[i].idDest]>(dist[sCourant.id]+tabAdja[i].valueE))
            {
                //d[v] ← d[u] + w(u, v)
                dist[tabAdja[i].idDest] = dist[sCourant.id] + tabAdja[i].valueE;
                //p[v] ← u
                parent[tabAdja[i].idDest] = sCourant.id;
                //F ← F ∪ {v}
                push_heap(Tas, tabAdja[i].idDest, dist[tabAdja[i].idDest]);
                vu[tabAdja[i].idDest]=true;
            }
       }
       vu[sCourant.id]=true;
       //Condition de sortie
       if (idMin==idDest){
            vu[idDest]=true;
            break;
       }
    }
    //liberaton des alloc inutiles
    free(tabAdja);
    free_heap(Tas);

    //Cas ou le sommet destination a ete visité
    if(vu[idDest]==true){
        //Etape 4: ecrire le chemin le plus court dans vertices
        solDij->distance=dist[idDest];
        //4a------remonter le chemin depuis le sommet destination
        sCourant.id=idDest;
        int tmpPath[G->nbSommet];
        while (sCourant.id != idOr){
            tmpPath[solDij->nVertices]=sCourant.id;
            sCourant.id=parent[sCourant.id];
            solDij->nVertices++;
        }
        //4b------ajouter le sommet d'origine en fin de tableau
        tmpPath[solDij->nVertices]=idOr;
        //--------Inverser le tableau de vertices
        int h=0, j=solDij->nVertices, tmp;
        while (h<j)
        {
            tmp=tmpPath[h];
            tmpPath[h]=tmpPath[j];
            tmpPath[j]=tmp;
            h++;
            j--;
        }
        //4c------Remplir solDij->vertices avec tableau inversé
        int k;
        for (k=0; k<=solDij->nVertices;k++){
            solDij->vertices[k] = tmpPath[k];
        }
    }else{
        printf("Pas de chemin entre %d & %d \n", idOr, idDest);
        solDij->vertices=realloc(solDij->vertices, (3)*sizeof(int));
        solDij->vertices[0] = idOr;
        solDij->vertices[1] = -1;
        solDij->vertices[2] = idDest;
        solDij->nVertices=2;
        solDij->distance=FLT_MAX;
    }
    //Test Solution:
    printf("sol fic base-------- %s \n", solDij->graphName);
    printf("sol fic base-------- %s \n", solDij->algoName);
    printf("id origine---------- %d \n", solDij->origin);
    printf("id destination------ %d \n", solDij->destination);
    printf("nExploredVertices--- %d \n", solDij->nExploredVertices);
    printf("nSteps-------------- %d \n", solDij->nSteps);
    printf("nbSommets----------- %d \n",G->nbSommet);
    printf("Distance------------ %.6f \n",solDij->distance);

    //exit
    return solDij;
}

Solution_t *astar(char *graphFile,Graphe *G, int idOr, int idDest){
    //Allocation memoire et init solution
    Solution_t *solAs=NULL;
    solAs = calloc(1, sizeof(Solution_t));
    if ( solAs != NULL )
    {
        solAs->origin=idOr;
        solAs->destination=idDest;
        solAs->vertices=calloc(G->nbSommet,sizeof(int));
        solAs->exploredVertices=calloc(1,sizeof(int));
        solAs->graphName=calloc((strlen(graphFile) + 1),sizeof(char));
        solAs->algoName=calloc((strlen("A*") + 1),sizeof(char));
        if ( solAs->graphName != NULL && solAs->algoName != NULL )
        {
            solAs->graphName=graphFile;
            solAs->algoName="A*";
        }else {
            fprintf(stderr,"Allocation Names impossible \n");
            exit(EXIT_FAILURE);
        }
    }else{
        fprintf(stderr,"Allocation solAs impossible \n");
        exit(EXIT_FAILURE);
    }
    //Initialisation variables solution
    solAs->distance=0.0;
    solAs->nExploredVertices=0;
    solAs->nSteps=0;
    solAs->nVertices=0;
    //Declaration variables
    int i;
    int p[G->nbSommet];
    heap_t *openlist=create_heap(G->nbSommet); //cout= dist[p[s]]+dist[s]+getDistance(s,idDest)
    heap_t *closelist=create_heap(G->nbSommet);
    int minOpen;
    float minClose=0.0;
    float euclH=0.0;
    Arc *tabAdj=NULL;
    bool vu[G->nbSommet];

    //Algo A*:
    //pour chaque sommet v de G faire
    for(i=0; i < G->nbSommet; i++)
    {
        //p[v] ← NULL
        p[i]=0;
        vu[i] = false;
    }
    //openlist ← { (s ; 0) } == push_heap(openlist, s, 0)
    push_heap(openlist, idOr, 0.0);
    //closedlist ← { (s ; 0) }
    push_heap(closelist, idOr, 0.0);
    //Ajout du sommet d'origine comme premier sommet exploré
    solAs->exploredVertices[solAs->nExploredVertices]=idOr;
    solAs->nExploredVertices++;
    solAs->exploredVertices=realloc(solAs->exploredVertices,((solAs->nExploredVertices+1)*sizeof(int)));
    //tant que openlist n'est pas vide faire
    while (!isEmpty(openlist)){

        //u ← EXTRAIRE-MIN(openlist)
        minOpen=extract_min(openlist);
        solAs->nSteps++;
        //si u == d alors
        if (minOpen == idDest){
            vu[idDest]=true;
            break;
        }
        //pour chaque sommet v de Adj[u] faire
        tabAdj=neighbours(G,minOpen);
        for (i=0; i<G->tabSommets[minOpen].nbAdj; i++)
        {
            //c = priorité de u dans closedList + w(u, v) //
            minClose=get_priority(closelist, minOpen)+(tabAdj[i].valueE);

            //si v pas dans closedList OU c < priorité de v dans closedList
            if (vu[tabAdj[i].idDest]==false && (!is_in(closelist,tabAdj[i].idDest) || minClose<(get_priority(closelist, tabAdj[i].idDest))))
            {
                //closedlist ← closedlist U { (v ; c) }
                push_heap(closelist, tabAdj[i].idDest, minClose);
                //f = c + H(v, d)
                euclH=minClose+getDistance(G,tabAdj[i].idDest,idDest);
                //openlist ← openlist U { (v ; f) }
                push_heap(openlist, tabAdj[i].idDest, euclH);
                //p[v] = u
                p[tabAdj[i].idDest]=minOpen;
                vu[tabAdj[i].idDest]=true;
                //Ajout sommet exploré
                solAs->exploredVertices[solAs->nExploredVertices]=tabAdj[i].idDest;
                solAs->nExploredVertices++;
                solAs->exploredVertices=realloc(solAs->exploredVertices,((solAs->nExploredVertices+1)*sizeof(int)));
            }
        }
        vu[minOpen]=true;
    }

    //Cas ou le sommet destination a ete visité
    if(vu[idDest]==true){
        //ecrire le chemin le plus court dans vertices
        solAs->distance= get_priority(closelist, idDest);
        //------remonter le chemin depuis le sommet destination
        int idCourant=idDest;
        int tmpPath[G->nbSommet];
        while (idCourant != idOr){
            tmpPath[solAs->nVertices]=idCourant;
            idCourant=p[idCourant];
            solAs->nVertices++;
        }
        //------ajouter le sommet d'origine en fin de tableau
        tmpPath[solAs->nVertices]=idOr;
        //--------Inverser le tableau de vertices
        int h=0, j=solAs->nVertices, tmp;
        while (h<j)
        {
            tmp=tmpPath[h];
            tmpPath[h]=tmpPath[j];
            tmpPath[j]=tmp;
            h++;
            j--;
        }
        //------Remplir solAs->vertices avec tableau inversé
        int k;
        for (k=0; k<=solAs->nVertices;k++){
            solAs->vertices[k] = tmpPath[k];
        }
    }else{
        printf("Pas de chemin entre %d & %d \n", idOr, idDest);
        //solAs->vertices=realloc(solAs->vertices, (3)*sizeof(int));
        solAs->vertices[0] = idOr;
        solAs->vertices[1] = -1;
        solAs->vertices[2] = idDest;
        solAs->nVertices=2;
        solAs->distance=FLT_MAX;
    }
    //liberaton des alloc inutiles
    free(tabAdj);
    free_heap(openlist);
    free_heap(closelist);
    //Test Solution:
    printf("sol fic base-------- %s \n", solAs->graphName);
    printf("sol algo name-------- %s \n", solAs->algoName);
    printf("id origine---------- %d \n", solAs->origin);
    printf("id destination------ %d \n", solAs->destination);
    printf("nExploredVertices--- %d \n", solAs->nExploredVertices);
    printf("nSteps-------------- %d \n", solAs->nSteps);
    printf("nbSommets----------- %d \n",G->nbSommet);
    printf("Distance------------ %.6f \n",solAs->distance);

    //exit
    return solAs;
}
void processSol(Resultat *TabR){
    Graphe *G=NULL;
    G=readGraph(TabR->FicGraph);

    //Dijskstra
    Solution_t *SolD=NULL;
    SolD=dijkstra(TabR->FicGraph, G, TabR->origine, TabR->destination);
    writeSolution(SolD, TabR->FicSolD);
    freeSol(SolD);

    //Astar
    Solution_t *SolA=NULL;
    SolA=astar(TabR->FicGraph, G, TabR->origine, TabR->destination);
    writeSolution(SolA, TabR->FicSolA);
    freeSol(SolA);

    freegraph(G);
}

void freeSol(Solution_t *S)
{
    free(S->algoName);
    free(S->graphName);
    free(S->exploredVertices);
    S->exploredVertices=NULL;
    free(S->vertices);
    S->vertices=NULL;
    free(S);
    S=NULL;
}


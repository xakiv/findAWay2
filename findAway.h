#ifndef FINDAWAY_H_INCLUDED
#define FINDAWAY_H_INCLUDED
#include "graphDef.h"



/*RESULTATS
Fichier résultat à fournir          Resultats
A_27_141_Dijkstra.path              19.7279
A_138_182_Dijkstra.path             17.2426
B_57_74_Dijkstra.path               24.3137
B_28_155_Dijkstra.path              13.656854
C_14_168_Dijkstra.path              dist=F_MAX Pas de chemin OK
01_992_1092_Dijkstra.path           dist=F_MAX Pas de chemin ??????
01_1107_1092_Dijkstra.path          69.0832 erreur ecriture fichier resultat!!!
02_837_1674_Dijkstra.path           63.5973
02_837_931_Dijkstra.path            40.8700
03_868_869_Dijkstra.path            84.254860
03_868_1427_Dijkstra.path           98.154366
box_64_16_Dijkstra.path             28.485281
maze_16_27_Dijkstra.path            20.656855
*/
typedef struct  {
    char* FicGraph; // nom du graphe
    char* FicSolD; // nom du fichier solution Disjkstra
    char* FicSolA; // nom du fichier solution Astar
    int origine; //id du sommet d'origine
    int destination; //id du sommet de destination
} Resultat;

typedef struct {
    char* graphName; // nom du graphe
    char* algoName; // nom de l'algorithme qui a construit la solution
    int origin; //id du sommet d'origine
    int destination; //id du sommet de destination
    int* vertices; // liste des sommets qui composent le chemin trouvé par l'algorithme
    int nVertices; // nombre de sommets dans le chemin
    float distance; // longueur du chemin
    int nSteps; // nombre d'itérations de l'algorithme pour trouver le chemin
    int* exploredVertices; // liste des sommets visités
    int nExploredVertices; // nombre de sommets visités
} Solution_t;

void writeSolution(Solution_t *sol, char *logsolFile);

Solution_t *dijkstra(char *graphFile, Graphe *G, int idOr, int idDest);

Solution_t *astar(char *graphFile,Graphe *G, int idOr, int idDest);

void processSol(Resultat *TabR);

void freeSol(Solution_t *S);

#endif // FINDAWAY_H_INCLUDED

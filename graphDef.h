#ifndef GRAPHDEF_H_INCLUDED
#define GRAPHDEF_H_INCLUDED
#include <stdbool.h>
//Structures de donnée
typedef struct Sommet
{
    int id; //id unique pour chaque nouveau sommet
    int dataS;
    int coordX;//valeur associer au sommet
    int coordY;
    int nbAdj; //Nombre  de sommets adjacents
    struct Arc *adjacents;//tableau de structures: { idDEST | valueE }
} Sommet;

typedef struct Arc
{
    int idDest; //id du sommet sur lequel l'arc pointe
    float valueE; //contient la valeur associé a l'arc (ex:distance)
}Arc;

typedef struct Graphe
{
    int nbSommet; //Nombre  de sommets dans le graphe
    int nbArc;
    int primKey; //Pour palier au probleme d'attribution des idSommet. primKey n'est pas décrémenter lorsque on supprime un sommet
    int type; //Reste a implementer le type (orienté=0; non-orienté=1)
    Sommet *tabSommets; //Pointe sur un tableau de Sommets
} Graphe;


//Opérations
//teste s'il existe dans G un arc allant du sommet x vers y;
bool is_adjacent(Graphe *G, int idOR, int idDEST);

//liste tous les sommets de G pouvant etre atteint directement depuis x
Arc *neighbours (Graphe *G, int idS);

//ajoute le sommet x a G s'il n'existe pas déja;
void add_vertex(Graphe *G);

//ote le sommet x de G, s'il existe;
void remove_vertex(Graphe *G, int idS);

//ajoute l'arc x vers y, s'il n'existe pas déja dans G;
void add_edge(Graphe *G, int idOR, int idDEST);

//ote l'arc x vers y, s'il existe dans G;
void remove_edge(Graphe *G, int idOR, int idDEST);

//retourne la valeur associee au sommet x dans G;
int get_vertex_value(Graphe *G, int idS);

//retourne la coordonnéeX associee au sommet d'indice S_id dans G;
int get_vertex_coordX(Graphe *G, int idS);

//retourne la coordonnéeY associee au sommet d'indice S_id dans G;
int get_vertex_coordY(Graphe *G, int idS);

//definit la valeur v associee au sommet x dans G;
void set_vertex_value(Graphe *G, int idS, int data);

//definit la valeur coordX associee au sommet d'indice S_id dans G;
void set_vertex_coordX(Graphe *G, int idS, int coordX);

//definit la valeur coordY associee au sommet d'indice S_id dans G;
void set_vertex_coordY(Graphe *G, int idS, int coordY);

//retourne la valeur associee a l'arc (x,y);
int get_edge_value(Graphe *G, int idOR, int idDEST);

//definit la valeur associee a l'arc (x,y);
void set_edge_value(Graphe *G, int idOR, int idDEST, float data);

//Allouer la mémoire
Graphe *initgraph(int nbS, int Orientation);

//Liberer la mémoire
void freegraph(Graphe *G);

//Rechercher indice ds tabSommet d'un idRec (-1 sinon)
int findS(Graphe *G, int idRec);

//Recherche indice de idDEST ds table d'adjacence de idOR  (-1 sinon)
int findA(Graphe *G, int idOR, int idDEST);

//Calcule distance
float getDistance(Graphe *G, int id_A, int id_B);

#endif // GRAPHDEF_H_INCLUDED

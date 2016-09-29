#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "graphDef.h"

bool is_adjacent(Graphe* G, int idOR, int idDEST)
{
    bool linked = false;
    //Parcourir tabSommet de G pour trouver idOR et idDEST
    int posOR=findS(G,idOR);
    int posDEST=findS(G,idDEST);
    //A condition que idOR et idDEST soit dans G.
    if(posOR>-1 && posDEST>-1){
        // On parcours le tab des adja d'idOR en utilisant posOR
        int i;
        for (i=0;i<G->tabSommets[posOR].nbAdj;i++){
            if(G->tabSommets[posOR].adjacents[i].idDest == idDEST ){
                linked = true;
                break;
            }
        }
    }
    return linked;
}

Arc* neighbours(Graphe* G, int idS)
{
    Arc *tabAdj=NULL;
    int posS=findS(G,idS);
    if (posS>-1){
        tabAdj=calloc(G->tabSommets[posS].nbAdj,sizeof(Arc));
        int i;
        for (i=0;i<G->tabSommets[posS].nbAdj;i++){
            tabAdj[i].idDest=G->tabSommets[posS].adjacents[i].idDest;
            tabAdj[i].valueE=G->tabSommets[posS].adjacents[i].valueE;
        }
    }else {printf("Sommet absent du graph\n");}
    return tabAdj;
}

void add_vertex(Graphe* G)
{
    G->tabSommets = realloc(G->tabSommets, (G->nbSommet+1)*sizeof(Sommet));
    if(G->tabSommets == NULL){
        printf("realloc impossible\n");
        exit(EXIT_FAILURE);
    }else{
        printf("realloc ok\n");
        G->tabSommets[G->nbSommet].id=G->primKey; //on creer les id en fonction d'une clé unique, non decrementé a la destruction
        G->tabSommets[G->nbSommet].dataS=0;
        G->tabSommets[G->nbSommet].nbAdj=0;
        G->tabSommets[G->nbSommet].adjacents=calloc(1,sizeof(Arc));
        if(G->tabSommets[G->nbSommet].adjacents == NULL){
            printf("calloc impossible\n");
            exit(EXIT_FAILURE);
        }else{
            printf("calloc ok\n");
            G->tabSommets[G->nbSommet].adjacents[0].idDest=-1;
            G->tabSommets[G->nbSommet].adjacents[0].valueE=-1.0;
            G->nbSommet++;
            G->primKey++;
        }
    }
}

void remove_vertex(Graphe* G, int idS)
{
    //verifie si le sommet existe et retourne son indice
    int posS =findS(G,idS);
    if(posS>-1)
    {
        //Decaler les cases de tabSommets
        int i;
        for (i=posS;i<G->nbSommet-1;i++){
            G->tabSommets[i]=G->tabSommets[i+1];
        }
        G->nbSommet--;
        G->tabSommets=realloc(G->tabSommets,G->nbSommet*sizeof(Sommet));

        //Supprimer la reference de ce sommet dans les tableau d'adja des autres Sommets
        int j;
        for (j=0;i<G->nbSommet;j++){

            if(is_adjacent(G,G->tabSommets[j].id,idS)){
                remove_edge(G,G->tabSommets[j].id,idS);
            }
        }
    }
}

void add_edge(Graphe* G, int idOR, int idDEST)
{
    //verifie si l'arc n'existe pas deja
    if(is_adjacent(G,idOR,idDEST) == false)
    {
        int posOR =findS(G,idOR);
        int posDEST =findS(G,idDEST);
        if (posOR>-1 && posDEST>-1){
            G->tabSommets[posOR].adjacents=realloc(G->tabSommets[posOR].adjacents, (G->tabSommets[posOR].nbAdj+1)*sizeof(Arc));
            G->tabSommets[posOR].adjacents[G->tabSommets[posOR].nbAdj].idDest=idDEST;
            G->tabSommets[posOR].adjacents[G->tabSommets[posOR].nbAdj].valueE=-1.0;
            G->tabSommets[posOR].nbAdj++;
            if (G->type==1)
            {
                add_edge(G, idDEST, idOR);
            }
        }
    }else{
        //printf("Un arc existe deja entre %d et %d\n",idOR,idDEST);
    }
}

void remove_edge(Graphe* G, int idOR, int idDEST)
{
    if(is_adjacent(G,idOR,idDEST)){
        //cherche si idOr existe ds G et retourne son indice ds tabSommet
        int posOR =findS(G,idOR);
        //cherche si idDESt existe et retourne son indice dans tabAja de idOR
        int posDEST =findA(G,idOR,idDEST);
        if (posOR>-1 && posDEST>-1){
            //decaler les case de tabAdja
            int i;
            for (i=posDEST;i<G->tabSommets[posOR].nbAdj-1;i++){
                G->tabSommets[posOR].adjacents[i]=G->tabSommets[posOR].adjacents[i+1];
            }
            //realloc de tabAdja
            G->tabSommets[posOR].nbAdj--;
            G->tabSommets[posOR].adjacents=realloc(G->tabSommets[posOR].adjacents, (G->tabSommets[posOR].nbAdj)*sizeof(Arc));
        }
    }
}

int get_vertex_value(Graphe* G, int idS)
{
    int posS=findS(G,idS);
    if (posS>-1)return G->tabSommets[posS].dataS;
    else return -1;
}

void set_vertex_value(Graphe* G, int idS, int data)
{
    int posS=findS(G,idS);
    if (posS>-1){
        G->tabSommets[posS].dataS=data;
    }
}

int get_edge_value(Graphe* G, int idOR, int idDEST)
{
    int posOR=findS(G,idOR);
    int posDEST=findA(G,idOR,idDEST);
    if (posOR>-1 && posDEST>-1)return G->tabSommets[posOR].adjacents[posDEST].valueE;
    else return -1;
}

void set_edge_value(Graphe* G, int idOR, int idDEST, float data)
{
    int posOR=findS(G,idOR);
    int posDEST=findA(G,idOR,idDEST);
    if (posOR>-1 && posDEST>-1){
        G->tabSommets[posOR].adjacents[posDEST].valueE=data;
    }
}

Graphe *initgraph(int nbS, int Orientation)
{
    Graphe *G=NULL;
    G = calloc(1,sizeof(Graphe));
    G->nbSommet=nbS;
    G->nbArc=0;
    G->type=Orientation; //(orienté=0; non-orienté=1)
    G->primKey=nbS; //Fixe la valeur des id des sommet ajouté aposteriori. primKey n'est pas décrémenter lorsque on supprime un sommet
    G->tabSommets=calloc(nbS,sizeof(Sommet));
    int i;
    for(i=0;i<G->nbSommet;i++){
        G->tabSommets[i].id=i;
        G->tabSommets[i].dataS=0;
        G->tabSommets[i].nbAdj=0;
        G->tabSommets[i].adjacents=calloc(1,sizeof(Arc));
        //On initialise les arcs d'indice 0, les valeurs seront modifié avec add_edge
        G->tabSommets[i].adjacents[0].idDest=-1;
        G->tabSommets[i].adjacents[0].valueE=-1.0;
    }
    return G;
}

void freegraph(Graphe* G)
{
//    int i;
//    for(i=0;i<G->nbSommet;i++){
//        free(G->tabSommets[i].adjacents);
//    }
    free(G->tabSommets);
    G->tabSommets=NULL;
    free(G);

}

int findS(Graphe *G, int idRec)
{
    int indice=-1;
    int i;
    for (i=0;i<G->nbSommet;i++){
        if (G->tabSommets[i].id == idRec){
            indice=i;
        }
    }
    return indice;
}

int findA(Graphe *G, int idOR, int idDEST)
{
    int posOR=findS(G,idOR);
    int indice=-1;
    int i;
    for (i=0;i<G->tabSommets[posOR].nbAdj;i++){
        if (G->tabSommets[posOR].adjacents[i].idDest == idDEST){
            indice=i;
        }
    }
    return indice;
}

int get_vertex_coordX(Graphe* G, int idS)
{
    int posS=findS(G,idS);
    if (posS>-1) return G->tabSommets[posS].coordX;
    else return -1;
}

int get_vertex_coordY(Graphe* G, int idS)
{
    int posS=findS(G,idS);
    if (posS>-1) return G->tabSommets[posS].coordY;
    else return -1;
}

void set_vertex_coordX(Graphe* G, int idS, int coordX)
{
    int posS=findS(G,idS);
    if (posS>-1){
        G->tabSommets[posS].coordX=coordX;
    }
}

void set_vertex_coordY(Graphe* G, int idS, int coordY)
{
    int posS=findS(G,idS);
    if (posS>-1){
        G->tabSommets[posS].coordY=coordY;
    }
}

float getDistance(Graphe* G, int idOR, int idDEST)
{
	//cast: (double)( n * m + l...) avec n m et l int, le résultat de l'expression convertit en double
	int coordXA = get_vertex_coordX(G,idOR);
    int coordYA = get_vertex_coordY(G,idOR);
    int coordXB = get_vertex_coordX(G,idDEST);
    int coordYB = get_vertex_coordY(G,idDEST);
	double exp1 = pow((coordXB - coordXA),2);
	double exp2 = pow((coordYB - coordYA),2);
	return sqrt(exp1+exp2);
}


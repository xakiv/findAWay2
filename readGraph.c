#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readGraph.h"
#include "graphDef.h"

//Lecture de fichier decrivant un graphe
Graphe *readGraph(char *dbFileName)
{
    //initialiser un graphe
    Graphe *newGraph=NULL; //calloc(1 , sizeof(Graphe));
    /*if (newGraph == NULL){
        //Sortie de la fonction
        printf("L'allocation a échouée");
        exit(EXIT_FAILURE);
    }*/
    //fopen file
    FILE* file = fopen(dbFileName, "r");
    if(!file)
    {
        printf("L'argument doit être un nom de fichier.");
        exit(EXIT_FAILURE);
    }
    //Initialisation des variables de parcours des ligne du fichier DB
    char line[256];  // contiendra la chaine de caractères d'une ligne
    char *substr;    // contiendra la chaine de caractères extraite de la ligne
    int nbSommets;
    int nbArc;
    int i = 1;
    //Tant qu'il y'a une ligne a lire
    while (fgets(line, sizeof(line), file))
    {
        // affichage de la ligne courante
        //printf("%s", line);

        //lire le nombre de sommets
        if (i==1)
        {
            //printf("Nombre de sommets = %d\n", atoi(line)); //afficher la première valeur lue (un entier).
            nbSommets=atoi(line);
            //initialiser le graphe NON orienté en fonction de nbSommets
            newGraph=initgraph(nbSommets,1);
            i++;
        }

        //lire le nombre d'arretes
        else if (i==2)
        {
            //printf("Nombre d'arcs = %d\n", atoi(line));// afficher la première valeur lue (un entier).
            nbArc=atoi(line);
            newGraph->nbArc=nbArc;
            i++;
        //continuer la suite du traitement dans le cas ou i>3
        }else{
            //lire les coordonnees de chaque sommet des lignes 3 à nbSommets+2
            while (i>2 && i<nbSommets+3)
            {

                substr = (char*) strtok (line, ",");
                int j=0;
                int idCourant;
                while(substr != NULL)
                {
                    j++;
                    if (j==1)
                    {
                        idCourant=atoi(substr);
                        //printf("S:%d(",idCourant);
                    }
                    else if (j==2)
                    {
                        int coordX=atoi(substr);
                        //printf("%d;",coordX);
                        set_vertex_coordX(newGraph,idCourant,coordX);
                    }
                    else if (j==3)
                    {
                        //printf("%d)\n",atoi(substr));
                        int coordY=atoi(substr);
                        set_vertex_coordY(newGraph,idCourant,coordY);
                        j=0;
                    }
                    substr = (char*)strtok (NULL, ",");
                }
                fgets(line, sizeof(line), file);
                i++;
            }

            //Tq on se situe dans la tranche de ligne des liste d'adja [nbSommet/nbEdge/Coord:X*nbSommet/Adja:X*nbSommet]
            while (i>nbSommets+2 && i<(3+2*nbSommets))
            {
                //Tq la sous-chaine lue est limitée par ':' on la considere comme id du sommet courant
                substr = (char*) strtok (line, ":");
                while(substr != NULL)
                {
                    int idCourant, id_Y;
                    idCourant=atoi(substr);
                    //printf("S:%d ->",idCourant);
                    //Il m'a fallut utiliser strtok avec NULL pour retourner le reste de la chaine:
                    //On a decoupé [1:2,3,4,5,6] jusqu'au delimiteur ':' maintenant on retourne [2,3,4,5,6]
                    substr = (char*)strtok (NULL, ",");
                    while (substr!=NULL)
                    {
                        id_Y=atoi(substr);
                        //printf(" Adj:%d ->",id_Y);
                        substr = (char*)strtok (NULL, ",");
                        //On ajoute finalement les arcs correspondant:
                        add_edge(newGraph,idCourant,id_Y);
                        //On ajoute la distance entre idCourant et idY
                        int posOR =findS(newGraph,idCourant);
                        int posDEST=findA(newGraph,idCourant,id_Y);
                        newGraph->tabSommets[posOR].adjacents[posDEST].valueE = getDistance(newGraph,idCourant,id_Y);
                        //printf("test posOR %d posDEST %d idDest %d dist %.6f\n",posOR,posDEST,newGraph->tabSommets[posOR].adjacents[posDEST].idDest,newGraph->tabSommets[posOR].adjacents[posDEST].valueE);

                    }
                    //printf("NULL\n");
                    substr = (char*)strtok (NULL, ":");
                }
                fgets(line, sizeof(line), file);
                i++;
            }
        }
    }
    // fermeture du fichier
    fclose(file);
    return newGraph;
}

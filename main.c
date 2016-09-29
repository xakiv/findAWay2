#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphDef.h"
#include "minpriorityqueue.h"
#include "readGraph.h"
#include "findAway.h"

int main(){

    Resultat TabResult[14];

    TabResult[0].FicGraph="graph_A.grph";
    TabResult[0].FicSolD="A_27_141_Dijkstra.path";
    TabResult[0].FicSolA="A_27_141_Astar.path";
    TabResult[0].origine=27;
    TabResult[0].destination=141;

    TabResult[1].FicGraph="graph_A.grph";
    TabResult[1].FicSolD="A_138_182_Dijkstra.path";
    TabResult[1].FicSolA="A_138_182_Astar.path";
    TabResult[1].origine=138;
    TabResult[1].destination=182;

    TabResult[2].FicGraph="graph_B.grph";
    TabResult[2].FicSolD="B_57_74_Dijkstra.path";
    TabResult[2].FicSolA="B_57_74_Astar.path";
    TabResult[2].origine=57;
    TabResult[2].destination=74;

    TabResult[3].FicGraph="graph_B.grph";
    TabResult[3].FicSolD="B_28_155_Dijkstra.path";
    TabResult[3].FicSolA="B_28_155_Astar.path";
    TabResult[3].origine=28;
    TabResult[3].destination=155;

    TabResult[4].FicGraph="graph_C.grph";
    TabResult[4].FicSolD="C_14_168_Dijkstra.path";
    TabResult[4].FicSolA="C_14_168_Astar.path";
    TabResult[4].origine=14;
    TabResult[4].destination=168;

    TabResult[5].FicGraph="graph01.grph";
    TabResult[5].FicSolD="01_992_1092_Dijkstra.path";
    TabResult[5].FicSolA="01_992_1092_Astar.path";
    TabResult[5].origine=992;
    TabResult[5].destination=1092;

    TabResult[6].FicGraph="graph01.grph";
    TabResult[6].FicSolD="01_1107_1092_Dijkstra.path";
    TabResult[6].FicSolA="01_1107_1092_Astar.path";
    TabResult[6].origine=1107;
    TabResult[6].destination=1092;

    TabResult[7].FicGraph="graph02.grph";
    TabResult[7].FicSolD="02_837_1674_Dijkstra.path";
    TabResult[7].FicSolA="02_837_1674_Astar.path";
    TabResult[7].origine=837;
    TabResult[7].destination=1674;

    TabResult[8].FicGraph="graph02.grph";
    TabResult[8].FicSolD="02_837_931_Dijkstra.path";
    TabResult[8].FicSolA="02_837_931_Astar.path";
    TabResult[8].origine=837;
    TabResult[8].destination=931;

    TabResult[9].FicGraph="graph03.grph";
    TabResult[9].FicSolD="03_868_869_Dijkstra.path";
    TabResult[9].FicSolA="03_868_869_Astar.path";
    TabResult[9].origine=868;
    TabResult[9].destination=869;

    TabResult[10].FicGraph="graph03.grph";
    TabResult[10].FicSolD="03_868_1427_Dijkstra.path";
    TabResult[10].FicSolA="03_868_1427_Astar.path";
    TabResult[10].origine=868;
    TabResult[10].destination=1427;

    TabResult[11].FicGraph="box.grph";
    TabResult[11].FicSolD="box_64_16_Dijkstra.path";
    TabResult[11].FicSolA="box_64_16_Astar.path";
    TabResult[11].origine=64;
    TabResult[11].destination=16;

    TabResult[12].FicGraph="maze.grph";
    TabResult[12].FicSolD="maze_16_27_Dijkstra.path";
    TabResult[12].FicSolA="maze_16_27_Astar.path";
    TabResult[12].origine=16;
    TabResult[12].destination=27;

    int i;
    for (i=0;i<13;i++){
    processSol(&TabResult[i]);
    printf("\n");
    }



    return 0;
}

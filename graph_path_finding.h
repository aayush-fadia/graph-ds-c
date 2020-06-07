//
// Created by aayush on 6/1/20.
//

#ifndef DSPD3_GRAPH_PATH_FINDING_H
#define DSPD3_GRAPH_PATH_FINDING_H

#include "graph_basics.h"

typedef struct dijkstra_element {
    Node *index_node;
    int dist;
    int prev;
} DijkstraElement;

typedef struct dijkstra_queue {
    DijkstraElement **queue;
    DijkstraElement **indexed;
    int pos;
    int node_count;
} DijkstraQueue;


typedef struct floyd_warshall_element {
    int dist;
    int prev;
} FElement;

typedef struct floyd_warshall_matrix {
    FElement **matrix;
    int n;
} FMatrix;

typedef struct all_paths_state {
    int writer;
    int *path;
    int n;
    int total_weight;
} AllPathsState;

void printQueue(DijkstraQueue *q);

DijkstraQueue *dijkstrasShortestPaths(Graph *g, int source_id);

void printAllPathsDijkstra(DijkstraQueue *q);

FMatrix *initFMatrix(Graph *g);

void printFMatrix(FMatrix *matrix);

FMatrix *updateFMatrix(FMatrix *oldFMatrix, int permit);

FMatrix *APSP(Graph *g);

void destroyFMatrix(FMatrix *toDestroy);

void printShortestPath(Graph *g, int source_id, FMatrix *matrix, int dest_id);

void printAllPaths(Graph *g, int source_id, int dest_id);

#endif //DSPD3_GRAPH_PATH_FINDING_H

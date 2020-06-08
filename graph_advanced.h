//
// Created by aayush on 5/30/20.
//

#ifndef DSPD3_GRAPH_ADVANCED_H
#define DSPD3_GRAPH_ADVANCED_H

#include "graph_basics.h"

typedef struct mst_edges_ll_item {
    int source_id;
    Edge *edge;
    struct mst_edges_ll_item *next;
} MSTEdgeItem;

int isStronglyConnected(Graph *g);

int hasCycle(Graph *g);

Graph *minimumSpanningTree(Graph *g);

#endif //DSPD3_GRAPH_ADVANCED_H

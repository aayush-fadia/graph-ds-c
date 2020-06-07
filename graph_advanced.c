//
// Created by aayush on 5/30/20.
//

#include "graph_advanced.h"

void depthFirstConnectivityStep(Graph *g, Node *node) {
    if (node->visited == 0) {
        node->visited = 1;
        Edge *edge_iter = node->edges;
        while (edge_iter != NULL) {
            Node *dest_node = edge_iter->destNode;
            if (dest_node->visited == 0) {
                depthFirstConnectivityStep(g, dest_node);
            }
            edge_iter = edge_iter->next;
        }
    }
}

int isConnected(Graph *g) {
    indexate(g);
    depthFirstConnectivityStep(g, g->nodes);
    Node *nodes_iter = g->nodes;
    int connected = 1;
    while (nodes_iter != NULL && connected == 1) {
        if (nodes_iter->visited == 0) {
            connected = 0;
        }
        nodes_iter = nodes_iter->next;
    }
    return connected;
}
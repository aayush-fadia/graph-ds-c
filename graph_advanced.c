//
// Created by aayush on 5/30/20.
//

#include "graph_advanced.h"

Graph *reverseGraph(Graph *g) {
    Graph *r = createEmptyGraphDirected();
    r->directed = 1;
    Node *ni = g->nodes;
    while (ni != NULL) {
        addNode(r, ni->id);
        ni = ni->next;
    }
    ni = g->nodes;
    while (ni != NULL) {
        Edge *edges_iter = ni->edges;
        while (edges_iter != NULL) {
            addEdgeToGraph(r, edges_iter->dest, ni->id, edges_iter->weight);
            edges_iter = edges_iter->next;
        }
        ni = ni->next;
    }
    return r;
}

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

int isStronglyConnected(Graph *g) {
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
    if (connected == 1) {
        Graph *r = reverseGraph(g);
        indexate(r);
        depthFirstConnectivityStep(r, r->nodes);
        nodes_iter = r->nodes;
        while (nodes_iter != NULL && connected == 1) {
            if (nodes_iter->visited == 0) {
                connected = 0;
            }
            nodes_iter = nodes_iter->next;
        }
        freeGraph(r);
    }
    return connected;
}

int depthFirstCycleStep(Graph *g, Node *node) {
    int retval = 0;
    if (node->visited == 0) {
        node->visited = 1;
        Edge *edge_iter = node->edges;
        while (edge_iter != NULL) {
            Node *dest_node = edge_iter->destNode;
            if (dest_node->visited == 0) {
                retval = depthFirstCycleStep(g, dest_node);
            }
            edge_iter = edge_iter->next;
        }
    } else {
        retval = 1;
    }
    return retval;
}


int hasCycle(Graph *g) {
    indexate(g);
    Node *nodes_iter = g->nodes;
    int cyclic = 0;
    while (cyclic == 0 && nodes_iter != NULL) {
        indexate(g);
        cyclic = depthFirstCycleStep(g, nodes_iter);
        nodes_iter = nodes_iter->next;
    }
    return cyclic;
}

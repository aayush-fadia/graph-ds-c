//
// Created by aayush on 6/8/20.
//

#include "graph_search.h"
#include "graph_traversal.h"

int depthFirstSearchStep(Graph *g, Node *node, int search_id) {
    int found = 0;
    if (node->id == search_id) {
        found = 1;
    } else {
        if (node->visited == 0) {
            node->visited = 1;
            Edge *edge_iter = node->edges;
            while (edge_iter != NULL) {
                Node *dest_node = edge_iter->destNode;
                if (dest_node->visited == 0) {
                    found = depthFirstSearchStep(g, dest_node, search_id);
                }
                edge_iter = edge_iter->next;
            }
        }
    }
    return found;
}

int searchDepthFirst(Graph *g, int search_id) {
    indexate(g);
    Node *nodes_iter = g->nodes;
    int found = 0;
    while (nodes_iter != NULL && found == 0) {
        found = depthFirstSearchStep(g, nodes_iter, search_id);
        nodes_iter = nodes_iter->next;
    }
    return found;
}


int breadthFirstSearchStep(Graph *g, BreadthFirstQueue *bft_q, int search_id) {
    Node *node = bft_q->nodes_queue[bft_q->reader];
    int found = 0;
    if (node->id == search_id) {
        found = 1;
    } else {
        node->visited = 1;
        bft_q->reader = bft_q->reader + 1;
        Edge *edge_iter = node->edges;
        while (edge_iter != NULL) {
            Node *dest_node = edge_iter->destNode;
            if (dest_node->visited == 0) {
                bft_q->nodes_queue[bft_q->writer] = dest_node;
                bft_q->writer = bft_q->writer + 1;
                dest_node->visited = 1;
            }
            edge_iter = edge_iter->next;
        }
        if (bft_q->reader < bft_q->writer) {
            found = breadthFirstSearchStep(g, bft_q, search_id);
        }
    }
    return found;
}


int searchBreadthFirst(Graph *g, int search_id) {
    int found = 0;
    indexate(g);
    BreadthFirstQueue bft_q;
    bft_q.nodes_queue = (Node **) malloc(g->node_count * sizeof(Node *));
    bft_q.reader = 0;
    bft_q.writer = 0;
    Node **nodePtrs = (Node **) malloc(g->node_count * sizeof(Node *));
    Node *nodes_iter = g->nodes;
    while (nodes_iter != NULL && found == 0) {
        if (nodes_iter->visited == 0) {
            bft_q.nodes_queue[0] = nodes_iter;
            bft_q.writer = 1;
            bft_q.reader = 0;
            found = breadthFirstSearchStep(g, &bft_q, search_id);
        }
        nodes_iter = nodes_iter->next;
    }
    return found;
}

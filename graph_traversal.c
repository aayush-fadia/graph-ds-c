//
// Created by aayush on 5/29/20.
//

#include "graph_traversal.h"

TraversalResult *initResult(int num_nodes) {
    TraversalResult *retval = (TraversalResult *) malloc(sizeof(TraversalResult));
    retval->node_ids = (int *) malloc(num_nodes * sizeof(int));
    retval->writer = 0;
    retval->node_count = num_nodes;
    return retval;
}

void depthFirstStep(TraversalResult *result, Graph *g, Node *node) {
    if (node->visited == 0) {
        node->visited = 1;
        result->node_ids[result->writer] = node->id;
        result->writer++;
        Edge *edge_iter = node->edges;
        while (edge_iter != NULL) {
            Node *dest_node = edge_iter->destNode;
            if (dest_node->visited == 0) {
                depthFirstStep(result, g, dest_node);
            }
            edge_iter = edge_iter->next;
        }
    }
}

TraversalResult *traverseDepthFirst(Graph *g) {
    indexate(g);
    TraversalResult *retval = initResult(g->node_count);
    Node *nodes_iter = g->nodes;
    while (nodes_iter != NULL) {
        depthFirstStep(retval, g, nodes_iter);
        nodes_iter = nodes_iter->next;
    }
    return retval;
}


void breadthFirstStep(TraversalResult *result, Graph *g, BreadthFirstQueue *bft_q) {
    Node *node = bft_q->nodes_queue[bft_q->reader];
    node->visited = 1;
    bft_q->reader = bft_q->reader + 1;
    Edge *edge_iter = node->edges;
    result->node_ids[result->writer] = node->id;
    result->writer = result->writer + 1;
    while (edge_iter != NULL) {
        Node *dest_node = edge_iter->destNode;
        int dest = edge_iter->dest;
        if (dest_node->visited == 0) {
            bft_q->nodes_queue[bft_q->writer] = dest_node;
            bft_q->writer = bft_q->writer + 1;
            dest_node->visited = 1;
        }
        edge_iter = edge_iter->next;
    }
    if (bft_q->reader < bft_q->writer) {
        breadthFirstStep(result, g, bft_q);
    }
}


TraversalResult *traverseBreadthFirst(Graph *g) {
    indexate(g);
    BreadthFirstQueue bft_q;
    bft_q.nodes_queue = (Node **) malloc(g->node_count * sizeof(Node *));
    bft_q.reader = 0;
    bft_q.writer = 0;
    Node **nodePtrs = (Node **) malloc(g->node_count * sizeof(Node *));
    Node *nodes_iter = g->nodes;
    TraversalResult *result = initResult(g->node_count);
    while (nodes_iter != NULL) {
        if (nodes_iter->visited == 0) {
            bft_q.nodes_queue[0] = nodes_iter;
            bft_q.writer = 1;
            bft_q.reader = 0;
            breadthFirstStep(result, g, &bft_q);
        }
        nodes_iter = nodes_iter->next;
    }
    return result;
}

void topologicalStep(TopologicalStack *stack, Graph *g, Node *node) {
    if (node->visited == 0) {
        node->visited = 1;
        Edge *edge_iter = node->edges;
        while (edge_iter != NULL) {
            Node *dest_node = edge_iter->destNode;
            if (dest_node->visited == 0) {
                topologicalStep(stack, g, dest_node);
            }
            edge_iter = edge_iter->next;
        }
        stack->stack[stack->writer] = node;
        stack->writer++;
    }
}

TraversalResult *traverseTopological(Graph *g) {
    indexate(g);
    TopologicalStack stck;
    stck.stack = (Node **) malloc(g->node_count * sizeof(Node *));
    stck.writer = 0;
    Node *nodes_iter = g->nodes;
    while (nodes_iter != NULL) {
        topologicalStep(&stck, g, nodes_iter);
        nodes_iter = nodes_iter->next;
    }
    TraversalResult *retval = initResult(g->node_count);
    while (stck.writer > 0) {
        stck.writer--;
        retval->node_ids[retval->writer] = stck.stack[stck.writer]->id;
        retval->writer++;
    }
    return retval;
}


void printOrder(TraversalResult *order) {
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < order->node_count; i++) {
        printf("Node %d found!\n", order->node_ids[i]);
    }
    printf("------------------------------------------------------------\n");
}


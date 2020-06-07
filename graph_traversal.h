//
// Created by aayush on 5/29/20.
//

#ifndef DSPD3_GRAPH_TRAVERSAL_H
#define DSPD3_GRAPH_TRAVERSAL_H

#include "graph_basics.h"

typedef struct breadth_first_queue {
    //The queue required for the Breadth First Search.
    Node **nodes_queue;
    int *queue;//The queue of the node indices.
    int writer;//The position at which to write the next node index.
    int reader;//The position from which to read next node index.
} BreadthFirstQueue;

typedef struct topological_stack {
    //The stack required for topological traversal.
    Node **stack;//The stack to hold node IDs.
    int writer;//The position of the top of the stack.
} TopologicalStack;

typedef struct traversal_result {
    //This is the format in which traversal orders are returned when a graph is traversed.
    int *node_ids;//The array of node IDs that the traversal found.
    int node_count;//The number of nodes in this traversal
    int writer;//The pointer that indicates the position in the array in which to write next ID.
} TraversalResult;

TraversalResult *traverseDepthFirst(Graph *g);

TraversalResult *traverseBreadthFirst(Graph *g);

TraversalResult *traverseTopological(Graph *g);

void printOrder(TraversalResult *order);//This function prints out the nodes in order from a TraversalResult struct.

#endif //DSPD3_GRAPH_TRAVERSAL_H

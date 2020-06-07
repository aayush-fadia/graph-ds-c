//
// Created by aayush on 5/28/20.
//

#ifndef DSPD3_GRAPH_BASICS_H
#define DSPD3_GRAPH_BASICS_H

#include <stdio.h>
#include <malloc.h>

typedef enum status {
    OK, NOT_OK
} Status;

typedef struct ll_item_node {
    int id;
    int index;
    int visited;
    struct ll_item_edge *edges;
    struct ll_item_node *next;
} Node;

typedef struct ll_item_edge {
    int weight;
    int dest;
    Node *destNode;
    struct ll_item_edge *next;
} Edge;

typedef struct graph_data {
    Node *nodes;
    int node_count;
    int directed;
} Graph;

void addNode(Graph *g, int id);

Status addEdgeToGraph(Graph *g, int source_id, int dest_id, int weight);

Graph *createEmptyGraphDirected();

Graph *createEmptyGraphUndirected();

void printNode_(Node *node);

void printGraph(Graph *g);

Status deleteEdgeFromNode_(Node *node, int dest);

Status deleteEdgeFromGraph(Graph *g, int source, int dest);

void severIncoming(Graph *g, int dest);

void deleteAllEdgesFromNode_(Node *node);

void severOutgoing(Graph *g, int source);

void deleteNodeFromGraph(Graph *g, int id);

void indexate(Graph *g);

int indexOfNode(Graph *g, int node_id);

void freeGraph(Graph *g);

#endif //DSPD3_GRAPH_BASICS_H

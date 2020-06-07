//
// Created by aayush on 5/28/20.
//
#include <malloc.h>
#include "graph_basics.h"


void addNode(Graph *g, int id) {
    Node *lastNode = g->nodes;
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->id = id;
    if (lastNode == NULL) {
        g->nodes = newNode;
    } else {
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
    g->node_count = g->node_count + 1;
}

Status addEdgeToNode_(Node *node, Edge *edge) {
    Edge *edges_iter = node->edges;
    Status retval;
    if (edges_iter == NULL) {
        node->edges = edge;
        edge->next = NULL;
        retval = OK;
    } else {
        Edge *prevEdge = NULL;
        while (edges_iter->dest < edge->dest && edges_iter->next != NULL) {
            prevEdge = edges_iter;
            edges_iter = edges_iter->next;
        }
        if (edges_iter->dest == edge->dest) {
            retval = NOT_OK;
        } else {
            retval = OK;
            if (edges_iter->next == NULL) {
                if (prevEdge == NULL) {
                    if (edges_iter->dest < edge->dest) {
                        edges_iter->next = edge;
                        edge->next = NULL;
                    } else {
                        node->edges = edge;
                        edge->next = edges_iter;
                    }
                } else {
                    edges_iter->next = edge;
                    edge->next = NULL;
                }
            } else if (prevEdge == NULL) {
                node->edges = edge;
                edge->next = edges_iter;
            } else {
                prevEdge->next = edge;
                edge->next = edges_iter;
            }
        }
    }
    return retval;
}

Status addEdgeToGraph(Graph *g, int source_id, int dest_id, int weight) {
    Status retval = NOT_OK;
    Node *node_iter = g->nodes;
    Node *source_node = NULL;
    Node *dest_node = NULL;
    int sourcefound = 0, destfound = 0;
    while (node_iter != NULL && (!sourcefound || !destfound)) {
        if (node_iter->id == source_id) {
            source_node = node_iter;
            sourcefound = 1;
        }
        if (node_iter->id == dest_id) {
            dest_node = node_iter;
            destfound = 1;
        }
        node_iter = node_iter->next;
    }
    if (sourcefound && destfound) {
        Edge *newEdge = (Edge *) malloc(sizeof(Edge));
        newEdge->dest = dest_id;
        newEdge->destNode = dest_node;
        newEdge->weight = weight;
        retval = addEdgeToNode_(source_node, newEdge);
        if (!g->directed) {
            Edge *newEdgeReverse = (Edge *) malloc(sizeof(Edge));
            newEdgeReverse->dest = source_id;
            newEdgeReverse->destNode = source_node;
            newEdgeReverse->weight = weight;
            retval = addEdgeToNode_(dest_node, newEdgeReverse);
        }
    }
    return retval;
}


Graph *createEmptyGraphDirected() {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->nodes = NULL;
    g->directed = 1;
    return g;
}

Graph *createEmptyGraphUndirected() {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->nodes = NULL;
    g->directed = 0;
    return g;
}

void printNode_(Node *node) {
    printf("%d: ", node->id);
    Edge *edge_iter = node->edges;
    while (edge_iter != NULL) {
        printf("%dw%d ", edge_iter->dest, edge_iter->weight);
        edge_iter = edge_iter->next;
    }
    printf("\n");
}

void printGraph(Graph *g) {
    Node *nodes_iter = g->nodes;
    printf("-----------------------------\n");
    char *directionality = g->directed ? "Directed" : "Undirected";
    printf("%d nodes\n", g->node_count);
    while (nodes_iter != NULL) {
        printNode_(nodes_iter);
        nodes_iter = nodes_iter->next;
    }
    printf("-----------------------------\n");
}

Status deleteEdgeFromNode_(Node *node, int dest) {
    Status retval = NOT_OK;
    Edge *edges_iter = node->edges;
    if (edges_iter != NULL) {
        Edge *prevEdge = NULL;
        while (edges_iter->next != NULL && edges_iter->dest != dest) {
            prevEdge = edges_iter;
            edges_iter = edges_iter->next;
        }
        if (edges_iter->dest == dest) {
            retval = OK;
            if (prevEdge != NULL) {
                prevEdge->next = edges_iter->next;
            } else {
                node->edges = edges_iter->next;
            }
            free(edges_iter);
        }
    }

    if (edges_iter != NULL) {
        retval = OK;

    }
    return retval;
}

Status deleteEdgeFromGraph(Graph *g, int source, int dest) {
    Node *nodes_iter = g->nodes;
    Status retval = NOT_OK;
    while (nodes_iter->id != source && nodes_iter != NULL) {
        nodes_iter = nodes_iter->next;
    }
    if (nodes_iter != NULL) {
        retval = deleteEdgeFromNode_(nodes_iter, dest);
    }
    return retval;
}

void severIncoming(Graph *g, int dest) {

    Node *nodes_iter = g->nodes;
    while (nodes_iter != NULL) {
        deleteEdgeFromNode_(nodes_iter, dest);
        nodes_iter = nodes_iter->next;
    }

}

void deleteAllEdgesFromNode_(Node *node) {
    Edge *edges_iter = node->edges;
    Edge *prevEdge = NULL;
    if (edges_iter != NULL) {
        prevEdge = edges_iter;
        edges_iter = edges_iter->next;
        free(prevEdge);
        while (edges_iter != NULL) {
            prevEdge = edges_iter;
            edges_iter = edges_iter->next;
            free(prevEdge);
        }
        node->edges = NULL;
    }
}

void severOutgoing(Graph *g, int source) {
    Node *node_iter = g->nodes;
    while (node_iter != NULL && node_iter->id != source) {
        node_iter = node_iter->next;
    }
    if (node_iter != NULL) {
        deleteAllEdgesFromNode_(node_iter);
    }
}

void deleteNodeFromGraph(Graph *g, int id) {
    severOutgoing(g, id);
    severIncoming(g, id);
    Node *nodes_iter = g->nodes;
    Node *prevNode = NULL;
    if (nodes_iter != NULL) {
        while (nodes_iter->id != id && nodes_iter->next != NULL) {
            prevNode = nodes_iter;
            nodes_iter = nodes_iter->next;
        }
        if (prevNode == NULL) {
            if (nodes_iter->id == id) {
                g->nodes = nodes_iter->next;
                g->node_count = g->node_count - 1;
                free(nodes_iter);
            }
        } else {
            prevNode->next = nodes_iter->next;
            g->node_count = g->node_count - 1;
            free(nodes_iter);
        }

    }
}

void indexate(Graph *g) {
    int i = 0;
    Node *nodes_iter = g->nodes;
    while (nodes_iter != NULL) {
        nodes_iter->visited = 0;
        nodes_iter->index = i;
        nodes_iter = nodes_iter->next;
        i = i + 1;
    }
    g->node_count = i;
}


int indexOfNode(Graph *g, int node_id) {
    Node *nodes_iter = g->nodes;
    while (nodes_iter->id != node_id) {
        nodes_iter = nodes_iter->next;
    }
    return nodes_iter->index;
}

void freeNode(Node *n) {
    Edge *edges_iter = n->edges;
    Edge *temp;
    while (edges_iter != NULL) {
        temp = edges_iter;
        edges_iter = edges_iter->next;
        free(temp);
    }
    free(n);
}


void freeGraph(Graph *g) {
    Node *nodes_iter = g->nodes;
    Node *temp;
    while (nodes_iter != NULL) {
        temp = nodes_iter;
        nodes_iter = nodes_iter->next;
        freeNode(temp);
    }
    free(g);
}

//
// Created by aayush on 6/1/20.
//

#include "graph_path_finding.h"

int isNotInf(int a) {
    return a != -1;
}

int isLesser(int a, int b) {
    if (b == -1) {
        return 1;
    } else if (a == -1) {
        return 0;
    } else {
        return a < b;
    }
}

void printElement(DijkstraElement *elem) {
    printf("Node = %d, Distance = %d, Previous = %d\n", elem->index_node->id, elem->dist, elem->prev);
}


void printQueue(DijkstraQueue *q) {
    for (int i = 0; i < q->node_count; i++) {
        printElement(q->queue[i]);
    }
    printf("\n");
}

int posInQueue(DijkstraQueue *q, int index) {
    int found = 0;
    int i;
    for (i = 0; found == 0; i++) {
        if (q->queue[i]->index_node->index == index) {
            found = 1;
        }
    }
    return i - 1;
}

void sortQueue(DijkstraQueue *q, int check_index) {
    DijkstraElement *cur_elem = q->queue[check_index];
    DijkstraElement *prev_element = q->queue[check_index - 1];
    while (check_index > 0 && !isLesser(prev_element->dist, cur_elem->dist)) {
        q->queue[check_index] = prev_element;
        check_index = check_index - 1;
        q->queue[check_index] = cur_elem;
        if (check_index != 0) {
            cur_elem = q->queue[check_index];
            prev_element = q->queue[check_index - 1];
        }
    }
}

DijkstraQueue *initQueue(Graph *g, int start_index) {
    DijkstraQueue *queue = (DijkstraQueue *) malloc(sizeof(DijkstraQueue));
    queue->queue = (DijkstraElement **) malloc(g->node_count * sizeof(DijkstraElement *));
    queue->indexed = (DijkstraElement **) malloc(g->node_count * sizeof(DijkstraElement *));
    Node *nodes_iter = g->nodes;
    while (nodes_iter != NULL) {
        int i = nodes_iter->index;
        DijkstraElement *elem = (DijkstraElement *) malloc(sizeof(DijkstraElement));
        elem->index_node = nodes_iter;
        elem->prev = start_index;
        elem->dist = (start_index == i) ? 0 : -1;
        queue->queue[i] = elem;
        queue->indexed[i] = elem;
        nodes_iter = nodes_iter->next;
    }
    sortQueue(queue, start_index);
    queue->pos = 0;
    queue->node_count = g->node_count;
    return queue;
}

void dijkstraStep(Graph *g, DijkstraQueue *q) {
    DijkstraElement *elem = q->queue[q->pos];
    if (elem->dist != -1) {
        Node *curNode = elem->index_node;
        Edge *edges_iter = curNode->edges;
        while (edges_iter != NULL) {
            int dest_index = edges_iter->destNode->index;
            int new_dist = elem->dist + edges_iter->weight;
            DijkstraElement *elemOfDest = q->indexed[dest_index];
            if (isLesser(new_dist, elemOfDest->dist)) {
                elemOfDest->dist = new_dist;
                elemOfDest->prev = elem->index_node->index;
                int check_index = posInQueue(q, dest_index);
                sortQueue(q, check_index);
            }
            edges_iter = edges_iter->next;
        }
    }
}


DijkstraQueue *dijkstrasShortestPaths(Graph *g, int source_id) {
    indexate(g);
    int source_index = indexOfNode(g, source_id);
    DijkstraQueue *q = initQueue(g, source_index);
    for (int i = 0; i < g->node_count; i++) {
        dijkstraStep(g, q);
        q->pos = q->pos + 1;
    }
    return q;
}

void printPathTo(DijkstraQueue *q, int source_index, int dest_index) {
    DijkstraElement *cur_elem = q->indexed[dest_index];
    if (cur_elem->dist != -1) {
        int *stack = (int *) malloc(q->node_count * sizeof(int));
        int writer = 0;
        int total_weight = cur_elem->dist;
        while (cur_elem->index_node->index != source_index) {
            stack[writer] = cur_elem->index_node->id;
            writer++;
            cur_elem = q->indexed[cur_elem->prev];
        }
        while (writer > 0) {
            writer--;
            printf("->%d", stack[writer]);
        }
        printf(" Weight: %d\n", total_weight);
    }

}


void printAllPathsDijkstra(DijkstraQueue *q) {
    int source_index = q->queue[0]->index_node->index;
    int source_id = q->queue[0]->index_node->id;
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < q->node_count; i++) {
        if (q->indexed[i]->dist != -1) {
            printf("%d", source_id);
            printPathTo(q, source_index, i);
        } else {
            printf("No path from %d to %d\n", source_id, q->indexed[i]->index_node->id);
        }
    }
    printf("-----------------------------------------------------\n");
}


FMatrix *initFMatrix(Graph *g) {
    int n_nodes = g->node_count;
    FMatrix *retval = (FMatrix *) malloc(sizeof(FMatrix));
    retval->n = n_nodes;
    retval->matrix = (FElement **) malloc(n_nodes * sizeof(FElement *));
    Node *nodes_iter = g->nodes;
    while (nodes_iter != NULL) {
        retval->matrix[nodes_iter->index] = (FElement *) malloc(n_nodes * sizeof(FElement));
        Edge *edges_iter = nodes_iter->edges;
        for (int i = 0; i < g->node_count; i++) {
            retval->matrix[nodes_iter->index][i].dist = i == nodes_iter->index ? 0 : -1;
            retval->matrix[nodes_iter->index][i].prev = nodes_iter->index;
        }
        while (edges_iter != NULL) {
            FElement elem;
            elem.dist = edges_iter->weight;
            elem.prev = nodes_iter->index;
            retval->matrix[nodes_iter->index][edges_iter->destNode->index].dist = edges_iter->weight;
            edges_iter = edges_iter->next;
        }
        nodes_iter = nodes_iter->next;
    }
    return retval;
}


FMatrix *updateFMatrix(FMatrix *oldFMatrix, int permit) {
    int n_nodes = oldFMatrix->n;
    FMatrix *retval = (FMatrix *) malloc(sizeof(FMatrix));
    retval->n = n_nodes;
    retval->matrix = (FElement **) malloc(n_nodes * sizeof(FElement *));
    for (int i = 0; i < oldFMatrix->n; i++) {
        retval->matrix[i] = (FElement *) malloc(n_nodes * sizeof(FElement));
        for (int j = 0; j < oldFMatrix->n; j++) {
            if (i == permit || j == permit) {
                retval->matrix[i][j] = oldFMatrix->matrix[i][j];
            } else if (i == j) {
                retval->matrix[i][j].prev = i;
                retval->matrix[i][j].dist = 0;
            } else {
                int dist_a_to_p = oldFMatrix->matrix[i][permit].dist;
                int dist_p_to_b = oldFMatrix->matrix[permit][j].dist;
                if (isNotInf(dist_a_to_p) && isNotInf(dist_p_to_b)) {
                    int total_dist_via_p = dist_a_to_p + dist_p_to_b;
                    if (isLesser(total_dist_via_p, oldFMatrix->matrix[i][j].dist)) {
                        retval->matrix[i][j].dist = total_dist_via_p;
                        retval->matrix[i][j].prev = permit;
                    } else {
                        retval->matrix[i][j] = oldFMatrix->matrix[i][j];
                    }
                } else {
                    retval->matrix[i][j] = oldFMatrix->matrix[i][j];
                }
            }
        }
    }
    return retval;
}

void printFMatrix(FMatrix *matrix) {
    printf("---------------------------------------------------\n");
    for (int i = 0; i < matrix->n; i++) {
        for (int j = 0; j < matrix->n; j++) {
            printf("%d via %d ", matrix->matrix[i][j].dist, matrix->matrix[i][j].prev);
        }
        printf("\n");
    }
    printf("---------------------------------------------------\n");
}


void destroyFMatrix(FMatrix *toDestroy) {
    for (int i = 0; i < toDestroy->n; i++) {
        free(toDestroy->matrix[i]);
    }
    free(toDestroy->matrix);
    free(toDestroy);
}


FMatrix *APSP(Graph *g) {
    indexate(g);
    FMatrix *old = initFMatrix(g);
    for (int i = 0; i < g->node_count; i++) {
        FMatrix *new = updateFMatrix(old, i);
        destroyFMatrix(old);
        old = new;
    }
    return old;
}


void printShortestPath(Graph *g, int source_id, FMatrix *matrix, int dest_id) {
    int source_index = indexOfNode(g, source_id);
    int dest_index = indexOfNode(g, dest_id);
    int *stack = (int *) malloc(g->node_count * sizeof(int));
    int writer = 0;
    FElement elem = matrix->matrix[source_index][dest_index];
    int dist = elem.dist;
    if (dist == -1) {
        printf("No Path exists from %d to %d", source_id, dest_id);
    } else {
        while (elem.prev != source_index) {
            stack[writer] = elem.prev;
            elem = matrix->matrix[source_index][elem.prev];
            writer++;
        }
        printf("%d", source_id);
        while (writer > 0) {
            writer--;
            printf("->%d", indexOfNode(g, stack[writer]));
        }
        printf("->%d", dest_id);
    }
}

void allPathsStep(AllPathsState state, Node *node, int dest_id) {
    if (node->id == dest_id) {
        for (int i = 0; i < state.writer; i++) {
            printf("%d->", state.path[i]);
        }
        printf("%d\n", dest_id);
    } else {
        int destReached = 0;
        int visited = 0;
        for (int j = 0; j < state.writer && visited == 0; j++) {
            if (state.path[j] == node->id) {
                visited = 1;
            }
        }
        if (!visited) {
            Edge *edges_iter = node->edges;
            while (edges_iter != NULL) {
                AllPathsState state_new;
                state_new.path = (int *) malloc(state.n * sizeof(int));
                state_new.n = state.n;
                for (int i = 0; i < state.writer; i++) {
                    state_new.path[i] = state.path[i];
                }
                state_new.path[state.writer] = node->id;
                state_new.writer = state.writer + 1;
                state_new.total_weight = state.total_weight + edges_iter->weight;
                allPathsStep(state_new, edges_iter->destNode, dest_id);
                edges_iter = edges_iter->next;
            }
        }

    }

}


void printAllPaths(Graph *g, int source_id, int dest_id) {
    Node *nodes_iter = g->nodes;
    while (nodes_iter->id != source_id) {
        nodes_iter = nodes_iter->next;
    }
    Edge *edges_iter = nodes_iter->edges;
    printf("----------------------------------------------\n");
    while (edges_iter != NULL) {
        AllPathsState state;
        state.path = (int *) malloc(g->node_count * sizeof(int));
        state.path[0] = nodes_iter->id;
        state.writer = 1;
        state.n = g->node_count;
        state.total_weight = 0;
        allPathsStep(state, edges_iter->destNode, dest_id);
        edges_iter = edges_iter->next;
    }
    printf("----------------------------------------------\n");
}

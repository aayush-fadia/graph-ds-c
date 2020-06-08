//
// Created by aayush on 6/7/20.
//

#include "graph_interface.h"


void nodeInput(Graph *g) {
    int node_id = scanInt("Enter node id (Any Integer)");
    addNode(g, node_id);
    printLine("Added the node");
}

void edgeInput(Graph *g) {
    int source = scanInt("Enter the source node of the edge");
    int dest = scanInt("Enter the destination node of the edge");
    int weight = scanInt("Enter the weight of the edge");
    addEdgeToGraph(g, source, dest, weight);
    printLine("Added Edge");
}


Graph *graphEdit(Graph *g) {
    if (g == NULL) {
        printLine("1) Create Undirected Graph");
        printLine("2) Create Directed Graph");
        int directionality = scanInt("Enter Choice");
        while (directionality != 1 && directionality != 2) {
            printLine("Invalid Choice");
            directionality = scanInt("Enter Choice");
        }
        if (directionality == 1) {
            g = createEmptyGraphUndirected();
        } else {
            g = createEmptyGraphDirected();
        }
    }
    int choice = 0;
    while (choice != 3) {
        printGraph(g);
        printLine("1) Add a node to your graph");
        printLine("2) Add an edge to your graph");
        printLine("3) Done, finalize the graph");
        choice = scanInt("Enter Choice");
        switch (choice) {
            case 1:
                nodeInput(g);
                break;
            case 2:
                edgeInput(g);
                break;
            case 3:
                break;
            default:
                printLine("Invalid Choice");
                break;
        }
    }
    indexate(g);
    return g;
}

void traverseOptions(Graph *g) {
    printLine("1) Depth First");
    printLine("2) Breadth First");
    printLine("3) Topological");
    printLine("4) Exit");
    int choice = scanInt("Enter choice");
    switch (choice) {
        case 1:
            printOrder(traverseDepthFirst(g));
            break;
        case 2:
            printOrder(traverseBreadthFirst(g));
            break;
        case 3:
            printOrder(traverseTopological(g));
            break;
        case 4:
            break;
        default:
            printLine("Invalid Choice");
            break;
    }
}

void allPathsInterface(Graph *g) {
    int source = scanInt("Source");
    int destination = scanInt("Destination");
    printAllPaths(g, source, destination);
}

void dijkstraInterface(Graph *g) {
    int source = scanInt("Source");
    DijkstraQueue *dijkstraQueue = dijkstrasShortestPaths(g, source);
    printAllPathsDijkstra(dijkstraQueue);
}

void floydWarshallInterface(Graph *g) {
    FMatrix *matrix = APSP(g);
    printFMatrix(matrix);
}

void pathFindingOptions(Graph *g) {
    printLine("1) All Paths between two nodes");
    printLine("2) Dijkstra's Algorithm");
    printLine("3) Floyd Warshall Algorithm");
    printLine("4) Exit");
    int choice = scanInt("Enter Choice");
    switch (choice) {
        case 1:
            allPathsInterface(g);
            break;
        case 2:
            dijkstraInterface(g);
            break;
        case 3:
            floydWarshallInterface(g);
        default:
            printLine("Invalid Choice");
            break;
    }
}

void minSpanTreeInterface(Graph *g) {
    Graph *minTree = minimumSpanningTree(g);
    printGraph(minTree);
    freeGraph(minTree);
}

void graphInterface(Graph *g) {
    if (g == NULL) {
        g = graphEdit(g);
    } else {
        printGraph(g);
    }
    int choice = 0;
    while (choice != 5) {
        printLine("Enter Choice");
        printLine("1) Traverse Graph");
        printLine("2) Path Finding");
        printLine("3) Modify the Graph");
        printLine("4) Calculate Minimum Spanning Tree");
        printLine("5) Exit the program");
        choice = scanInt("Enter Choice");
        switch (choice) {
            case 1:
                traverseOptions(g);
                break;
            case 2:
                pathFindingOptions(g);
                break;
            case 3:
                g = graphEdit(g);
                break;
            case 4:
                minSpanTreeInterface(g);
                break;
            case 5:
                break;
            default:
                printLine("Invalid Choice");
        }
    }
}


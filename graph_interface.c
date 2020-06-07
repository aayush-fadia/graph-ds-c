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
    if (g == NULL) { g = createEmptyGraph(); }
    int choice = 0;
    while (choice != 3) {
        printGraph(g);
        printLine("1) Add a node to your graph");
        printLine("2) Add an edge to your graph");
        printLine("3) Done, finalize the graph");
        choice = scanInt("What do you want to do");
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
                printLine("Enter a valid option pls.");
                break;
        }
    }
    return g;
}

void depthFirstTraverse(Graph *g) {

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
            printLine("Enter a valid choice pls");
            break;
    }
}


void graphInterface(Graph *g) {
    if (g == NULL) {
        g = graphEdit(g);
    }
    int choice = 0;
    while (choice != 4) {
        printLine("What do you want to do?");
        printLine("1) Traverse Graph");
        printLine("2) Path Finding");
        printLine("3) Modify the Graph");
        printLine("4) Exit the program");
        choice = scanInt("What do you want to do");
        switch (choice) {
            case 1:
                traverseOptions(g);
                break;
            case 3:
                g = graphEdit(g);
            default:
                printLine("Enter a valid choice pls");
        }
    }
}


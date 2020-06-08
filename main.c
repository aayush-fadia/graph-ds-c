#include "graph_basics.h"
#include "graph_traversal.h"
#include "graph_advanced.h"
#include "graph_path_finding.h"
#include "graph_interface.h"

int main() {
    Graph* g = createEmptyGraphDirected();
    addNode(g, 10);
    addNode(g, 20);
    addNode(g, 30);
    addNode(g, 40);
    addEdgeToGraph(g, 10, 20, 1);
    addEdgeToGraph(g, 10, 30, 6);
    addEdgeToGraph(g, 10, 40, 5);
    addEdgeToGraph(g, 20, 30, 2);
    addEdgeToGraph(g, 20, 40, 3);
    addEdgeToGraph(g, 30, 40, 4);
    Graph *mst = minimumSpanningTree(g);
    printGraph(mst);
    graphInterface(g);
}

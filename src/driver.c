#include "driver.h"

int main(int argc, char **argv) {
    TSP *tsp = init_tsp(argv[1]);
    printf("TSP 0: %d %d\n", tsp->nodes[0].x, tsp->nodes[0].y);
    printf("TSP %d: %d %d\n", tsp->num_nodes-1, tsp->nodes[tsp->num_nodes-1].x, tsp->nodes[tsp->num_nodes-1].y);

    // get euclidean distances for graph
    generate_graph(tsp);

    // generate the MST (prim's)
    build_mst(tsp);

    // get the odd-degree vertices


    free_tsp(tsp);

    return 0;
}
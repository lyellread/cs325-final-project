#include "driver.h"

int main(int argc, char **argv) {
    int total_distance;
    TSP *tsp;
    array_t visited;

    // read in data
    tsp = init_tsp(argv[1]);
    
    // get euclidean distances for graph
    generate_graph(tsp);

    // do nearest neighbor
    total_distance = compute_nearest_neighbor(tsp, 18, &visited);

    result_output(total_distance, visited, argv[1]);

    free_tsp(tsp);
    array_free(visited);

    return 0;
}
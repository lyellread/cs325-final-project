#include "driver.h"

int main(int argc, char **argv) {
    TSP *tsp = init_tsp(argv[1]);
    
    // get euclidean distances for graph
    generate_graph(tsp);

    // generate the MST (prim's)
    build_mst(tsp);

    // get the odd-degree vertices
    array_t odd_vertices = get_odd_vertices(tsp);

    // build the perfect matching graph
    build_perfect_matching(tsp, odd_vertices);

    array_t euler_tour = generate_euler_tour(tsp);
    //dbg if needed

    array_t tour = tsp_from_euler(euler_tour);

    result_output(tsp, tour, argv[1]);

    free_tsp(tsp);
    array_free(odd_vertices);
    array_free(euler_tour);
    array_free(tour);

    return 0;
}
#include "tsp.h"

// get the Euclidean distance b/t two nodes
int get_euclidean_distance(Node n1, Node n2) {
	double dx = pow((double)(n1.x - n2.x), 2);
	double dy = pow((double)(n1.y - n2.y), 2);

	return round(sqrt(dx+dy));
}

// generate the distances for the whole graph
void generate_graph(TSP *tsp) {
	for (int i = 0; i < tsp->num_nodes; i++) {
		for (int j = 0; j < tsp->num_nodes; j++) {
			tsp->graph[i][j] = tsp->graph[j][i] = get_euclidean_distance(tsp->nodes[i], tsp->nodes[j]);
		}
	}
}

// use prim's algorithm to find MST
Graph get_mst(TSP *tsp) {

}

void free_tsp(TSP *tsp) {
	for (int i = 0; i < tsp->num_nodes; i++) {
		free(tsp->graph[i]);
		tsp->graph[i] = NULL;
	}
	free(tsp->graph);

	free(tsp->nodes);
	tsp->nodes = NULL;

	free(tsp);
	tsp = NULL;
}
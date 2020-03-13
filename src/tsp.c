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

void _print_mst(TSP *tsp, int parent[]) {
	int total = 0;
	puts("Edge\tWeight");
	for (int i = 1; i < tsp->num_nodes; i++) {
		printf("(%d,%d) - (%d, %d)\t%d\n", tsp->nodes[parent[i]].x, tsp->nodes[parent[i]].y, tsp->nodes[i].x, tsp->nodes[i].y, tsp->graph[i][parent[i]]);
		total += tsp->graph[i][parent[i]];
	}
	printf("Total: %d\n", total);
}

// use prim's algorithm to find MST
void build_mst(TSP *tsp) {
	int key[tsp->num_nodes];
	int parent[tsp->num_nodes];
	Edge *mst;
	bool in_mst[tsp->num_nodes];

	int min_node;

	// dynamic b/c easier to return
	mst = malloc(sizeof(Edge) * tsp->num_nodes);

	// init arrs
	for (int i = 0; i < tsp->num_nodes; i++) {
		key[i] = INT_MAX;
		in_mst[i] = false;
	}

	// pick first vertex
	key[0] = 0;
	parent[0] = -1;

	// loop through nodes
	for (int i = 0; i < tsp->num_nodes - 1; i++) {
		// get the mst node
		min_node = mst_min_key(tsp, key, in_mst);

		// save node
		in_mst[min_node] = true;

		// update adjacent vertices not yet in mst
		for (int j = 0; j < tsp->num_nodes; j++) {
			if (tsp->graph[min_node][j] && !(in_mst[j]) && tsp->graph[min_node][j] < key[j]) {
				// non zero value, not in mst, weight less than key value
				parent[j] = min_node;
				key[j] = tsp->graph[min_node][j];
			}
		}
	}

	// _print_mst(tsp, parent);
}

// find the lowest edge that's not in the MST
int mst_min_key(TSP *tsp, int key[], bool in_mst[]) {
	int min_idx, min_val = INT_MAX;
	for (int i = 0; i < tsp->num_nodes; i++) {
		if (!(in_mst[i]) && key[i] < min_val) {
			// found candidate node
			min_idx = i;
			min_val = key[i];
		}
	}

	return min_idx;
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
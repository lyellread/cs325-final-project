#include "tsp.h"

// get the Euclidean distance b/t two nodes
// O(c)
int get_euclidean_distance(Node n1, Node n2) {
	double dx = pow((double)(n1.x - n2.x), 2);
	double dy = pow((double)(n1.y - n2.y), 2);

	return round(sqrt(dx+dy));
}

// generate the distances for the whole graph
// O(V^2)
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

int compute_nearest_neighbor(TSP *tsp, int start_vertex, array_t *visited_out) {
	int current, lowest_vertex, lowest_distance, i, check_distance, total_distance;
	array_t visited;

	current = start_vertex;
	visited = array_new();
	total_distance = lowest_vertex = 0;

	while (visited->length < tsp->num_nodes) {
		puts("visited:");
		array_print(visited);
		lowest_distance = INT_MAX;

		// find the next node
		for (i = 0; i < tsp->num_nodes; i++) {
			printf("i=%d\tcurrent=%d\t", i, current); 

			// can't go to itself
			if (i == current) {
				printf("i == current, continue\n");
				continue;
			}

			// no duplicates
			if (array_in(visited, i)) {
				printf("i in visited, continue\n");
				continue;
			}

			// check if better than current
			check_distance = tsp->graph[current][i];
			printf("check_distance=%d\tlowest_distance=%d\t", check_distance, lowest_distance);
			if (check_distance < lowest_distance) {
				printf("found a better vertex");

				lowest_distance = check_distance;
				lowest_vertex = i;

				total_distance += lowest_distance;
			}
			printf("\n");
		}

		printf("saving %d to visited\n", lowest_vertex);
		array_append(visited, lowest_vertex);
		printf("current num visited: %d\tcurrent distance: %d\n",  visited->length, total_distance);
		current = lowest_vertex;

		printf("\n\n");
	}

	puts("done!");

	*visited_out = visited;
	return total_distance;
}

// free heap memory for tsp struct
void free_tsp(TSP *tsp) {
	for (int i = 0; i < tsp->num_nodes; i++) {
		free(tsp->graph[i]);
		tsp->graph[i] = NULL;
	}
	free(tsp->graph);
	tsp->graph = NULL;

	free(tsp->nodes);
	tsp->nodes = NULL;

	free(tsp);
	tsp = NULL;
}
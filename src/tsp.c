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

// use prim's algorithm to find MST
// O(V^2)
void build_mst(TSP *tsp) {
	int key[tsp->num_nodes];
	int parent[tsp->num_nodes];
	bool in_mst[tsp->num_nodes];

	int min_node;

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

	// save mst edges
	// this makes getting the odd degree vertices super easy
	for (int i = 1; i < tsp->num_nodes; i++) {
		int n2 = parent[i];
		if (in_mst[i] && n2 != -1) {
			// node is in mst
			array_append(tsp->multigraph[i], n2);
			array_append(tsp->multigraph[n2], i);
		}
	}

	// _print_mst(tsp, parent);
}

// find the lowest edge that's not in the MST
// O(V)
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

// get the odd vertices (after mst)
// O(V)
array_t get_odd_vertices(TSP *tsp) {
	array_t odd_vertices = array_new();
	for (int i = 0; i < tsp->num_nodes; i++) {
		if (tsp->multigraph[i]->length % 2 == 1) {
			array_append(odd_vertices, i);
		}
	}
	return odd_vertices;
}

// add the perfect matching graph to the multigraph
// O(V), where V is the number of vertices in the odd vertex subgraph
// minimum not required, this is O(V^2) vs O(V^3) if it was minimum
void build_perfect_matching(TSP *tsp, array_t odd_vertices) {
	unsigned int length;
	int saved_node, i;

	// keep going until no more left
	// can't use for b/c odd_vertices gets modified out of order
	while (odd_vertices->length != 0) {
		length = saved_node = INT_MAX;

		// find a vertex near the first in the array
		for (i = 1; i < odd_vertices->length; i++) {
			if (tsp->graph[odd_vertices->data[0]][odd_vertices->data[i]] < length) {
				// found a closer vertex
				length = tsp->graph[odd_vertices->data[0]][odd_vertices->data[i]];
				saved_node = odd_vertices->data[i];
			}
		}

		// save the edge
		array_append(tsp->multigraph[odd_vertices->data[0]], saved_node);
		array_append(tsp->multigraph[saved_node], odd_vertices->data[0]);

		// remove two nodes from odd_vertices
		array_remove_at(odd_vertices, 0);
		array_remove_elem(odd_vertices, saved_node);
	}
}

// generate the Euler tour for the multigraph
array_t generate_euler_tour(TSP *tsp) {
	stack_t stack = stack_new();
	array_t circuit = array_new();
	int current_vertex = 0;

	// iterate through all saved vertices and existing edges
	while (tsp->multigraph[current_vertex]->length > 0 || stack->length > 0) {
		if (tsp->multigraph[current_vertex]->length == 0) {
			// no more edges, add to circuit
			array_append(circuit, current_vertex);
			current_vertex = stack_pop(stack);
		} else {
			// still has edges, push to stack and keep going
			stack_push(stack, current_vertex);
			current_vertex = array_remove_at(tsp->multigraph[current_vertex], 0);
		}
	}

	return circuit;
}


array_t tsp_from_euler (array_t euler_tour){
	array_t tour = array_new();
	//array_t visited = array_new() -- tour == visited for these purposes
	for (int i = 0; i < euler_tour->length; i++){
		if (array_in(tour, euler_tour->data[i]) == -1){
			//not already visited
			array_append(tour, euler_tour->data[i]);
		}
	}
	array_free(euler_tour);
	return tour;
}

// free heap memory for tsp struct
void free_tsp(TSP *tsp) {
	for (int i = 0; i < tsp->num_nodes; i++) {
		free(tsp->graph[i]);
		tsp->graph[i] = NULL;
	
		array_free(tsp->multigraph[i]);
		tsp->multigraph[i] = NULL;
	}
	free(tsp->graph);
	tsp->graph = NULL;
	free(tsp->multigraph);
	tsp->multigraph = NULL;

	free(tsp->nodes);
	tsp->nodes = NULL;

	free(tsp);
	tsp = NULL;
}
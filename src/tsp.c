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
		//puts("visited:");
		//array_print(visited);
		lowest_distance = INT_MAX;

		// find the next node
		for (i = 0; i < tsp->num_nodes; i++) {
			//printf("i=%d\tcurrent=%d\t", i, current); 

			// can't go to itself
			if (i == current) {
				//printf("i == current, continue\n");
				continue;
			}

			// no duplicates
			if (array_in(visited, i)) {
				//printf("i in visited, continue\n");
				continue;
			}

			// check if better than current
			check_distance = tsp->graph[current][i];
			//printf("check_distance=%d\tlowest_distance=%d\t", check_distance, lowest_distance);
			if (check_distance < lowest_distance) {
				//printf("found a better vertex");

				lowest_distance = check_distance;
				lowest_vertex = i;

				total_distance += lowest_distance;
			}
			//printf("\n");
		}

		//printf("saving %d to visited\n", lowest_vertex);
		array_append(visited, lowest_vertex);
		//printf("current num visited: %d\tcurrent distance: %d\n",  visited->length, total_distance);
		current = lowest_vertex;

		//printf("\n\n");
	}

	//puts("done!");

	*visited_out = visited;
	return total_distance;
}


int get_total_distance(TSP *tsp, array_t tour) {
	int distance = 0, i;
	for (i = 0; i < tour->length-1; i++) {
		distance += tsp->graph[tour->data[i]][tour->data[i+1]];
	}
	distance += tsp->graph[tour->data[i]][tour->data[0]];

	return distance;
}


array_t two_opt(TSP *tsp, array_t visited_out, int initial_total_distance){

	int best_distance, new_distance;
	array_t new_route, best_route;

	start_again:

		best_distance = initial_total_distance;
		best_route = visited_out;

		for (int i = 1; i < visited_out->length-1; i++){
			for (int k = i + 1; k < visited_out->length; k++){
				new_route = two_opt_swap(visited_out, i, k);
				new_distance = get_total_distance(tsp, new_route);
				if (new_distance < best_distance){
					best_route = new_route;
					array_free(new_route);
					best_distance = new_distance;
					goto start_again;
				}
				else{
					array_free(new_route);
				}
			}
		}
	return best_route;
}


array_t two_opt_swap(array_t current_path, int one, int two){
	
	array_t out_array;

	for (int i = 0; i <= one; i++){
		array_append(out_array, current_path->data[i]);
	}

	for (int i = two; i > one; i--){
		array_append(out_array, current_path->data[i]);
	}

	for (int i = two; i < current_path->length; i++){
		array_append(out_array, current_path->data[i]);
	}

	return out_array;
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
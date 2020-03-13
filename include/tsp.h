#ifndef __TSP_H
#define __TSP_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"

#define MAX_NODES 15112

typedef int **Graph;

typedef struct {
    int x;
    int y;
} Node; // each city is a Node

typedef struct {
    int n1;
    int n2;
} Edge;

typedef struct {
    Node *nodes;
    int num_nodes;
    Graph graph; // 2D int array w/ Euclidean distances as values
    array_t *multigraph; // this is the mst and then the perfect matching graph
    // do it into the same graph b/c more efficient
} TSP;

int get_euclidean_distance(Node, Node);
void generate_graph(TSP *);
void build_mst(TSP *);
int mst_min_key(TSP *, int [], bool []);
array_t get_odd_vertices(TSP *);
void build_perfect_matching(TSP *, array_t);
void free_tsp(TSP *);

#endif
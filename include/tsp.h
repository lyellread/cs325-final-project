#ifndef __TSP_H
#define __TSP_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "stack.h"

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
} TSP;

int get_euclidean_distance(Node, Node);
void generate_graph(TSP *);
int compute_nearest_neighbor(TSP *, int, array_t *);
array_t two_opt(TSP *, array_t, int);
array_t two_opt_swap(array_t , int, int);
int get_total_distance(TSP *, array_t );
void free_tsp(TSP *);

#endif
#ifndef __TSP_H
#define __TSP_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 15112

typedef int **Graph;

typedef struct {
    int x;
    int y;
} Node; // each city is a Node

typedef struct {
    Node *nodes;
    int num_nodes;
    Graph graph; // 2D int array w/ Euclidean distances as values
} TSP;

int get_euclidean_distance(Node, Node);
Graph get_mst(TSP *);
void free_tsp(TSP *);

#endif
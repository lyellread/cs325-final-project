#include "io.h"

// Read in nodes from input file
TSP *init_tsp(const char *path) {
    FILE *fp;
    char *line = NULL;
    size_t line_len = 0;
    TSP *tsp;
    int c = 0;

    tsp = malloc(sizeof(TSP));

    fp = fopen(path, "r");
    if (!fp) {
        fputs("failed to open input file\n", stderr);
        exit(1);
    }

    tsp->nodes = malloc(sizeof(Node) * MAX_NODES);

    while ((getline(&line, &line_len, fp)) != -1) {
        // iterate through each line 
        sscanf(line, "%*d %d %d\n", &(tsp->nodes[c].x), &(tsp->nodes[c].y));
        c++;
    }

    tsp->num_nodes = c;

    tsp->graph = malloc(sizeof(int *) * tsp->num_nodes);
    for (int i = 0; i < tsp->num_nodes; i++) {
        tsp->graph[i] = malloc(sizeof(int) * tsp->num_nodes);
    }
    
    tsp->multigraph = malloc(sizeof(array_t *) * tsp->num_nodes);
    for (int i = 0; i < tsp->num_nodes; i++) {
        tsp->multigraph[i] = array_new();
    }

    fclose(fp);
    return tsp;
}

void result_output (array_t tour, const char * path){
    FILE * fp;

    char extension[6] = ".tour";
    char filename[100] = "\0";

    strcat(filename, path);
    strcat(filename, extension);

    fp = fopen(filename, "w");
    if (!fp) {
        fputs("failed to open output file\n", stderr);
        exit(1);
    }

    fprintf(fp, "%d\n", tour->length);

    for (int i = 0; i < tour->length; i++){
        fprintf(fp, "%d\n", tour->data[i]);
    }

    fclose(fp);
    array_free(tour);
}
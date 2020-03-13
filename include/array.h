#ifndef __ARRAY_H
#define __ARRAY_H

#include <limits.h>
#include <stdlib.h>

#define ARRAY_DEFAULT_SIZE 30

typedef struct {
    int *data; // data
    int length; // num elements in array
    size_t size; // max elements in array
} Array;

typedef Array *array_t;

array_t array_new();
void array_append(array_t, int);
void array_insert_at(array_t, int, unsigned int);
int array_at(array_t, unsigned int);
void array_remove_at(array_t, unsigned int);
void array_remove_elem(array_t, int);
void array_free(array_t);

#endif
#include "array.h"

// double available memory for array
void _array_resize(array_t arr) {
    arr->size *= 2;
    arr->data = realloc(arr->data, arr->size);
}

// make a new array with the specified width
array_t array_new() {
    array_t arr = malloc(sizeof(Array));

    arr->data = malloc(sizeof(int) * ARRAY_DEFAULT_SIZE);

    arr->length = 0;
    arr->size = ARRAY_DEFAULT_SIZE;

    return arr;
}

// append an element to the array
// O(c)
void array_append(array_t arr, int data) {
    if (arr->length == arr->size) {
        _array_resize(arr);
    }

    arr->data[arr->length++] = data;
}

// insert an element to a certain position
void array_insert_at(array_t arr, int data, unsigned int idx) {
    if (idx >= arr->length) abort();

    arr->data[idx] = data;
}

// get an element from the array
int array_at(array_t arr, unsigned int idx) {
    if (idx >= arr->length) abort();
    return arr->data[idx];
}

// free data
void array_free(array_t arr) {
    free(arr->data);
    arr->data = NULL;
}
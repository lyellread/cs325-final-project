#include "array.h"

// double available memory for array
void _array_resize(array_t arr) {
    int *new_arr = malloc(sizeof(int) * (arr->size*2));
    for (int i = 0; i < arr->length; i++) new_arr[i] = arr->data[i];
    free(arr->data);

    arr->data = new_arr;
    arr->size *= 2;
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

// get an element from the array
// O(c)
int array_at(array_t arr, unsigned int idx) {
    if (idx >= arr->length) abort();
    return arr->data[idx];
}

// remove an element at certain index
// returns the value that was removed
// (used when generating the euler circuit)
// O(n)
int array_remove_at(array_t arr, unsigned int idx) {
    if (idx >= arr->length) abort();

    int val = arr->data[idx];

    for (int i = idx; i < arr->length-1; i++) {
        arr->data[i] = arr->data[i+1];
    }

    arr->length--;

    return val;
}

// remove a certain value from the array
// if it occurs multiple times, only remove
// the first one
// O(n)
void array_remove_elem(array_t arr, int val) {
    unsigned int idx = INT_MAX;
    for (int i = 0; i < arr->length; i++) {
        if (arr->data[i] == val) {
            idx = i;
            break;
        }
    }

    // if it wasn't found, don't remove anything
    if (idx != INT_MAX) array_remove_at(arr, idx);
}

// free data
void array_free(array_t arr) {
    free(arr->data);
    arr->data = NULL;
    
    free(arr);
    arr = NULL;
}
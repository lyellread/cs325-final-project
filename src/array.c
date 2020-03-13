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

// remove an element at certain index
// O(n)
void array_remove_at(array_t arr, unsigned int idx) {
    if (idx >= arr->length) abort();

    for (int i = idx; i < arr->length-1; i++) {
        arr->data[i] = arr->data[i+1];
    }

    arr->length--;
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

// get index of first occurrence of item in array, if any
// else return -1
int array_in(array_t array, int val){
    for (i = 0; i < array->length; i++){
        if (array->data[i] == val){
            return i;
        }
    }
    
    return -1;
}

// free data
void array_free(array_t arr) {
    free(arr->data);
    arr->data = NULL;
    
    free(arr);
    arr = NULL;
}
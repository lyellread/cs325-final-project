#include "stack.h"

stack_t stack_new() {
    return (stack_t) array_new();
}

int pop(stack_t stack) {
    if (stack->length == 0) abort();

    return stack->data[--stack->length];
}

void push(stack_t stack, int val) {
    array_append((array_t)stack, val);
}
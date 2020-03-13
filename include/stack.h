#ifndef __STACK_H
#define __STACK_H

#include <stdlib.h>

#include "array.h"

typedef array_t stack_t;

stack_t stack_new();
int pop(stack_t);
void push(stack_t, int);

#endif
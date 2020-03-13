#ifndef __STACK_H
#define __STACK_H

#include <stdlib.h>

#include "array.h"

typedef array_t stack_t;

stack_t stack_new();
int stack_pop(stack_t);
void stack_push(stack_t, int);

#endif
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "tsp.h"

TSP *init_tsp(const char *);
void result_output (int, array_t, const char *);

#endif
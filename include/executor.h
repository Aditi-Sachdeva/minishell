#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "parser.h"

void run_external(char *args[], redirect_t *r, int background);
void run_pipeline(char *left[], char *right[]);

#endif
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_P
{
    char *name;
    unsigned long long line;
    struct Node_P *next;
} Node_P;

void add_procedure_line(char *name, unsigned long long line);
unsigned long long get_line_procedure(char *name);

#endif

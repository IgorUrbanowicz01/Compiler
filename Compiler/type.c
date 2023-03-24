#include <stdio.h>
#include <stdlib.h>
#include "type.h"

struct type *type_create(type_t kind, struct decl *params)
{
    struct type *t = malloc(sizeof(*t));
    if (!t)
    {
        puts("Failed to allocate space for type, exiting...");
        exit(EXIT_FAILURE);
    }

    t->kind = kind;
    t->params = params;

    return t;
}

void type_print(struct type *t)
{
    if (!t)
        return;

    // char *kind_to_str[] = {"void", "boolean", "char", "integer", "string", "array", "function"};
    // printf("%s", kind_to_str[t->kind - TYPE_VOID]);
    char *type_t_to_str[] = {"integer", "function"};
    printf("%s", type_t_to_str[t->kind]);
    switch (t->kind)
    {
    case TYPE_FUNCTION:
        fputs(" (", stdout);
        decl_print_list(t->params, 0, "", ", ");
        fputs(")", stdout);
        break;
    default:
        break;
    }
}
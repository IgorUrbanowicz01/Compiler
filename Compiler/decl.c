#include "decl.h"

#define MAX_SIZE 100
char *arr[MAX_SIZE];

struct decl *decl_create(char *ident, struct type *type, struct stmt *func_body, struct decl *next, struct decl *next_procedure)
{
    struct decl *d = malloc(sizeof(*d));
    if (!d)
    {
        puts("[ERROR|FATAL] Could not allocate decl memory, exiting...");
        exit(EXIT_FAILURE);
    }

    d->ident = ident;
    d->type = type;
    d->func_body = func_body;
    d->next_procedure = next_procedure;
    d->next = next;

    return d;
}

void decl_print(struct decl *d, int indents, char *term)
{
    if (!d)
        return;

    printf("%s", d->ident);

    if (d->func_body)
    {
        fputs(" = {\n", stdout);
        stmt_print_list(d->func_body, indents + 1, "\n");
        fputs("\n}", stdout);
    }
    else
        fputs(term, stdout);
}

void decl_print_list(struct decl *d, int indents, char *term, char *delim)
{
    if (!d)
        return;
    decl_print(d, indents, term);
    if (d->next)
        fputs(term, stdout);
    decl_print_list(d->next, indents, ", ", delim);
    if (d->next_procedure)
        fputs(delim, stdout);
    decl_print_list(d->next_procedure, indents, term, delim);
}

bool decl_find(struct decl *d, char *i_find)
{
    if (!d)
        return 0;
    if (strcmp(d->ident, i_find) == 0)
        return 1;
    return decl_find(d->next, i_find);
}

void resolveProcedures(struct decl *d)
{
    if (!d)
        return;
    add_verible(d->ident, d->next);
    addparameters(d->ident, d->type->params);
    stmt_change_name(d->ident, d->func_body);
    resolveProcedures(d->next_procedure);
}

void addparameters(char *name, struct decl *p)
{
    if (!p)
        return;
    strcat(p->ident, "_-_");
    strcat(p->ident, name);
    set_register_parameter(p->ident);
    addparameters(name, p->next);
    initialize_verible(p->ident);
}

void add_verible(char *name, struct decl *p)
{
    if (!p)
        return;
    strcat(p->ident, "_-_");
    strcat(p->ident, name);
    set_register_varible(p->ident);
    add_verible(name, p->next);
}

void change_name(char *name, struct decl *p)
{
    if (!p)
        return;
    strcat(p->ident, "_-_");
    strcat(p->ident, name);
    change_name(name, p->next);
}

/*int contains(char *str, int index)
{
    for (int i = 0; i < index; i++)
    {
        if (strcmp(arr[i], str) == 0)
        {
            return 1;
        }
    }
    return 0;
}*/

/*void add_string(char *str, int index)
{
    if (index < MAX_SIZE)
        arr[index++] = str;
    else
        printf("Array is full\n");
}*/

/*int march_on_decl(struct decl *d, int index){
    add_string(d->ident, index);
    if (d->next)
        return march_on_decl(d->next, index+1);
    else
        return index + 1;
}*/

/*void decl_resolve(struct decl *d, int index)
{
    if (d->type->params)
        index += march_on_decl(d->type->params, index);
    if (d->next)
        index += march_on_decl(d->next, index);
}*/

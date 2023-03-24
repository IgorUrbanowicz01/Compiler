#include "procedure.h"

Node_P *headP = NULL;

void add_procedure_line(char *name, unsigned long long line)
{
    struct Node_P *new_node = (struct Node_P *)malloc(sizeof(struct Node_P));
    new_node->name = strdup(name);
    new_node->next = NULL;
    new_node->line = line;
    if (headP == NULL)
    {
        headP = new_node;
    }
    else
    {
        struct Node_P *current = headP;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

unsigned long long get_line_procedure(char *name)
{
    Node_P *current = headP;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current->line;
        }
        current = current->next;
    }
    return 0;
}
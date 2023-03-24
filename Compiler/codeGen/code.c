#include "code.h"
#include "registerHandler.h"

// Initialize an empty code list
void init_code_list(struct CodeList *list, unsigned long long starting_line)
{
    list->starting_line = starting_line;
    list->head = NULL;
    list->tail = NULL;
}

// Add a line of code to the code list
void add_line(struct CodeList *list, char *command, char *arg1)
{
    struct Line *newLine = (struct Line *)malloc(sizeof(struct Line));
    newLine->command = strdup(command);
    if (arg1)
        newLine->arg1 = strdup(arg1);
    newLine->next = NULL;

    if (list->tail == NULL)
    {
        list->head = newLine;
        list->tail = newLine;
        newLine->line_number = list->starting_line;
    }
    else
    {
        newLine->line_number = get_last_line_index(list) + 1;
        list->tail->next = newLine;
        list->tail = newLine;
    }
}

long long get_last_line_index(struct CodeList *list)
{
    if (!list->tail)
        return list->starting_line - 1;
    return list->tail->line_number;
}

// Print the code list
void print_code_list(struct CodeList *list)
{
    struct Line *currentLine = list->head;
    while (currentLine != NULL)
    {
        if (!currentLine->arg1)
            printf("%s \n", currentLine->command);
        else
            printf("%s %s\n", currentLine->command, currentLine->arg1);
        currentLine = currentLine->next;
    }
}

void copy_code_list(struct CodeList *b, struct CodeList *a)
{
    struct Line *currentLine = a->head;
    while (currentLine != NULL)
    {
        add_line(b, currentLine->command, currentLine->arg1);
        currentLine = currentLine->next;
    }
}

void write_code_list_to_file(struct CodeList *list, FILE *fp)
{
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    struct Line *currentLine = list->head;
    while (currentLine != NULL)
    {
        if (!currentLine->arg1)
            fprintf(fp, "%s\n", currentLine->command);
        else
            fprintf(fp, "%s %s\n", currentLine->command, currentLine->arg1);
        currentLine = currentLine->next;
    }
    fclose(fp);
}

#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Line
{
    char *command;
    char *arg1;
    unsigned long long line_number;
    struct Line *next;
};

struct CodeList
{
    unsigned long long starting_line;
    struct Line *head;
    struct Line *tail;
};

void init_code_list(struct CodeList *list, unsigned long long starting_line);
void add_line(struct CodeList *list, char *command, char *arg1);
void print_code_list(struct CodeList *list);
void copy_code_list(struct CodeList *a, struct CodeList *b);
long long get_last_line_index(struct CodeList *list);
void write_code_list_to_file(struct CodeList *list, FILE *fp);

#endif

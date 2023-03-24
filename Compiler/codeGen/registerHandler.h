#ifndef REGISTER_HANDLER_H
#define REGISTER_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node
{
    unsigned long long reg;
    char *varible;
    bool param;
    bool initialized;
    struct Node *next;
};

// extern char *registers[NUM_REGISTERS];

char *get_register_varible(unsigned long long reg);
void set_register_varible(char *varible);
void set_register_parameter(char *varible);
char *get_register_index(char *varible);
char *get_empty_register();
void print_registers();
int check_if_initialized(char *varible);
bool is_parameter(char *varible);
bool is_initialized(char *varible);
void initialize_verible(char *varible);

#endif

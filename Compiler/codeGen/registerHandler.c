#include "registerHandler.h"

struct Node *head = NULL;

void set_register_varible(char *varible)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->varible = strdup(varible);
    new_node->next = NULL;
    new_node->param = false;
    new_node->initialized = false;
    if (head == NULL)
    {
        new_node->reg = 12;
        head = new_node;
    }
    else
    {
        struct Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        new_node->reg = current->reg + 1;
        current->next = new_node;
    }
}

void set_register_parameter(char *varible)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->varible = strdup(varible);
    new_node->next = NULL;
    new_node->param = true;
    new_node->initialized = false;
    if (head == NULL)
    {
        new_node->reg = 12;
        head = new_node;
    }
    else
    {
        struct Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        new_node->reg = current->reg + 1;
        current->next = new_node;
    }
}

char *get_register_index(char *varible)
{
    struct Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->varible, varible) == 0)
        {
            char reg_str[20];
            snprintf(reg_str, 20, "%lld", current->reg);
            return strdup(reg_str);
        }
        current = current->next;
    }
    printf("ERROR| cant find verible %s\n", varible);
    return strdup("-1");
}

void print_registers()
{
    struct Node *current = head;
    while (current != NULL)
    {
        printf("Register index: %llu, Variable: %s Parameter: %d\n", current->reg, current->varible, current->param);
        current = current->next;
    }
}

char *get_empty_register()
{
    if (head == NULL)
    {
        return strdup("11");
    }

    struct Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    char reg_str[20];
    snprintf(reg_str, 20, "%lld", current->reg + 1);
    return strdup(reg_str);
}

int check_if_initialized(char *varible)
{
    struct Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->varible, varible) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

bool is_parameter(char *varible)
{
    struct Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->varible, varible) == 0)
        {
            return current->param;
        }
        current = current->next;
    }
    printf("Veribe not found: %s\n", varible);
    return 0;
}

bool is_initialized(char *varible)
{
    struct Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->varible, varible) == 0)
        {
            return current->initialized;
        }
        current = current->next;
    }
    printf("Veribe not found: %s\n", varible);
    return 0;
}

void initialize_verible(char *varible)
{
    struct Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->varible, varible) == 0)
        {
            current->initialized = true;
            return;
        }
        current = current->next;
    }
    printf("Veribe not found: %s\n", varible);
    return;
}
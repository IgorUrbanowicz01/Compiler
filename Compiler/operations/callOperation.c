#include "callOperation.h"

/*
1 <--- line where divide starts
44 <--- line where mod starts
87 <--- line where mul starts
116 <--- line where mul ENDS
*/

char *get_reg(struct expr *expr)
{

    switch (expr->kind)
    {
    case EXPR_IDENT:
        return get_register_index(expr->data->ident_name);
        break;

    case EXPR_INT_LIT:
        return get_register_index(expr->data->ident_name);
        break;

    default:
        printf("[FATAL|ERROR]WRONG EXPRESION PASSED");
        exit(1);
        break;
    }
}

void mul_call(struct CodeList *list, struct expr *expr)
{
    if (!is_initialized(expr->data->operator_args->data->ident_name) && expr->data->operator_args->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    if (!is_initialized(expr->data->operator_args->next->data->ident_name) && expr->data->operator_args->next->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    char *name = get_empty_register();
    strcat(name, "temp");
    set_register_varible(name);
    char *A = get_reg(expr->data->operator_args);
    char *B = get_reg(expr->data->operator_args->next);
    char *WYNIK = get_register_index(name);
    bool is_A_param = is_parameter(expr->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(expr->data->operator_args->next->data->ident_name);
    char buffer[20];
    if (is_A_param)
    {
        add_line(list, "LOADI", A);
    }
    else
    {
        add_line(list, "LOAD", A);
    }
    add_line(list, "STORE", "1");
    if (is_B_param)
    {
        add_line(list, "LOADI", B);
    }
    else
    {
        add_line(list, "LOAD", B);
    }
    add_line(list, "STORE", "2");
    unsigned long long line = get_last_line_index(list) + 4;
    sprintf(buffer, "%llu", line);
    add_line(list, "SET", buffer);
    add_line(list, "STORE", "8");
    add_line(list, "JUMP", "87");
    add_line(list, "STORE", WYNIK);
    expr_free_oper(expr->data->operator_args);
    expr->kind = EXPR_IDENT;
    expr->data->ident_name = name;
}

void div_call(struct CodeList *list, struct expr *expr)
{
    if (!is_initialized(expr->data->operator_args->data->ident_name) && expr->data->operator_args->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    if (!is_initialized(expr->data->operator_args->next->data->ident_name) && expr->data->operator_args->next->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    char *name = get_empty_register();
    strcat(name, "temp");
    set_register_varible(name);
    char *A = get_reg(expr->data->operator_args);
    char *B = get_reg(expr->data->operator_args->next);
    char *WYNIK = get_register_index(name);
    bool is_A_param = is_parameter(expr->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(expr->data->operator_args->next->data->ident_name);
    char buffer[20];
    if (is_A_param)
    {
        add_line(list, "LOADI", A);
    }
    else
    {
        add_line(list, "LOAD", A);
    }
    add_line(list, "STORE", "1");
    if (is_B_param)
    {
        add_line(list, "LOADI", B);
    }
    else
    {
        add_line(list, "LOAD", B);
    }
    add_line(list, "STORE", "2");
    unsigned long long line = get_last_line_index(list) + 4;
    sprintf(buffer, "%llu", line);
    add_line(list, "SET", buffer);
    add_line(list, "STORE", "8");
    add_line(list, "JUMP", "1");
    add_line(list, "LOAD", "3");
    add_line(list, "STORE", WYNIK);
    expr_free_oper(expr->data->operator_args);
    expr->kind = EXPR_IDENT;
    expr->data->ident_name = name;
}

void mod_call(struct CodeList *list, struct expr *expr)
{

    if (!is_initialized(expr->data->operator_args->data->ident_name) && expr->data->operator_args->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    if (!is_initialized(expr->data->operator_args->next->data->ident_name) && expr->data->operator_args->next->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    char *name = get_empty_register();
    strcat(name, "temp");
    set_register_varible(name);
    char *A = get_reg(expr->data->operator_args);
    char *B = get_reg(expr->data->operator_args->next);
    char *WYNIK = get_register_index(name);
    bool is_A_param = is_parameter(expr->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(expr->data->operator_args->next->data->ident_name);
    char buffer[20];
    if (is_A_param)
    {
        add_line(list, "LOADI", A);
    }
    else
    {
        add_line(list, "LOAD", A);
    }
    add_line(list, "STORE", "1");
    if (is_B_param)
    {
        add_line(list, "LOADI", B);
    }
    else
    {
        add_line(list, "LOAD", B);
    }
    add_line(list, "STORE", "2");
    unsigned long long line = get_last_line_index(list) + 4;
    sprintf(buffer, "%llu", line);
    add_line(list, "SET", buffer);
    add_line(list, "STORE", "8");
    add_line(list, "JUMP", "44");
    add_line(list, "LOAD", "3");
    add_line(list, "STORE", WYNIK);
    expr_free_oper(expr->data->operator_args);
    expr->kind = EXPR_IDENT;
    expr->data->ident_name = name;
}

void add_call(struct CodeList *list, struct expr *expr)
{
    if (!is_initialized(expr->data->operator_args->data->ident_name) && expr->data->operator_args->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    if (!is_initialized(expr->data->operator_args->next->data->ident_name) && expr->data->operator_args->next->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }

    char *name = get_empty_register();
    strcat(name, "temp");
    set_register_varible(name);
    char *A = get_reg(expr->data->operator_args);
    char *B = get_reg(expr->data->operator_args->next);
    char *WYNIK = get_register_index(name);
    bool is_A_param = is_parameter(expr->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(expr->data->operator_args->next->data->ident_name);
    if (is_A_param)
    {
        add_line(list, "LOADI", A);
    }
    else
    {
        add_line(list, "LOAD", A);
    }
    if (is_B_param)
    {
        add_line(list, "ADDI", B);
    }
    else
    {
        add_line(list, "ADD", B);
    }
    add_line(list, "STORE", WYNIK);
    expr_free_oper(expr->data->operator_args);
    expr->kind = EXPR_IDENT;
    expr->data->ident_name = name;
}

void sub_call(struct CodeList *list, struct expr *expr)
{
    if (!is_initialized(expr->data->operator_args->data->ident_name) && expr->data->operator_args->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    if (!is_initialized(expr->data->operator_args->next->data->ident_name) && expr->data->operator_args->next->kind == EXPR_IDENT)
    {
        printf("ERROR|INITIALIZATION varible %s\n", expr->data->operator_args->data->ident_name);
        exit(1);
    }
    char *name = get_empty_register();
    strcat(name, "temp");
    set_register_varible(name);
    char *A = get_reg(expr->data->operator_args);
    char *B = get_reg(expr->data->operator_args->next);
    char *WYNIK = get_register_index(name);
    bool is_A_param = is_parameter(expr->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(expr->data->operator_args->next->data->ident_name);
    if (is_A_param)
    {
        add_line(list, "LOADI", A);
    }
    else
    {
        add_line(list, "LOAD", A);
    }
    if (is_B_param)
    {
        add_line(list, "SUBI", B);
    }
    else
    {
        add_line(list, "SUB", B);
    }
    add_line(list, "STORE", WYNIK);
    expr_free_oper(expr->data->func_and_args);
    expr->kind = EXPR_IDENT;
    expr->data->ident_name = name;
}

void asg_call(struct CodeList *list, struct expr *expr)
{
    char *A = get_reg(expr->data->operator_args);
    char *B = get_reg(expr->data->operator_args->next);
    bool is_A_param = is_parameter(expr->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(expr->data->operator_args->next->data->ident_name);
    if (is_B_param)
    {
        add_line(list, "LOADI", B);
    }
    else
    {
        add_line(list, "LOAD", B);
    }
    if (is_A_param)
    {
        add_line(list, "STOREI", A);
    }
    else
    {
        add_line(list, "STORE", A);
    }
    expr_free_oper(expr);
}
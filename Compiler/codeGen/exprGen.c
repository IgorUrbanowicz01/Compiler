#include "exprGen.h"

void generate_while_loop_code_from_expr(struct CodeList *list, struct stmt *s)
{
    long long line_index = get_last_line_index(list) + 1;
    long long line_index_post_oper;
    char buffer[20];
    sprintf(buffer, "%llu", line_index);
    generate_from_expr(list, s->expr_list->data->operator_args);
    generate_from_expr(list, s->expr_list->data->operator_args->next);
    char *A = get_reg(s->expr_list->data->operator_args);
    char *B = get_reg(s->expr_list->data->operator_args->next);
    bool is_A_param = is_parameter(s->expr_list->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(s->expr_list->data->operator_args->next->data->ident_name);
    struct CodeList *while_list = (struct CodeList *)malloc(sizeof(struct CodeList));

    switch (s->expr_list->kind)
    {
    case EXPR_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "ADD", "9");
        init_code_list(while_list, get_last_line_index(list) + 2);
        stmt_generator(while_list, s->body);
        add_line(while_list, "JUMP", buffer);
        line_index_post_oper = get_last_line_index(while_list) + 1;
        // printf("this is last index in while %llu<--\n", line_index_post_oper);
        sprintf(buffer, "%llu", line_index_post_oper);
        add_line(list, "JPOS", buffer);
        copy_code_list(list, while_list);
        break;
    case EXPR_NOT_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "ADD", "9");
        init_code_list(while_list, get_last_line_index(list) + 2);
        stmt_generator(while_list, s->body);
        add_line(while_list, "JUMP", buffer);
        line_index_post_oper = get_last_line_index(while_list) + 1;
        // printf("this is last index in while %llu<--\n", line_index_post_oper);
        sprintf(buffer, "%llu", line_index_post_oper);
        add_line(list, "JZERO", buffer);
        copy_code_list(list, while_list);
        break;
    case EXPR_LT:
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        init_code_list(while_list, get_last_line_index(list) + 2);
        stmt_generator(while_list, s->body);
        add_line(while_list, "JUMP", buffer);
        line_index_post_oper = get_last_line_index(while_list) + 1;
        // printf("this is last index in while %llu<--\n", line_index_post_oper);
        sprintf(buffer, "%llu", line_index_post_oper);
        add_line(list, "JZERO", buffer);
        copy_code_list(list, while_list);
        break;
    case EXPR_LT_EQ:
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "STORE", "9");
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
        add_line(list, "SUB", "9");
        init_code_list(while_list, get_last_line_index(list) + 2);
        stmt_generator(while_list, s->body);
        add_line(while_list, "JUMP", buffer);
        line_index_post_oper = get_last_line_index(while_list) + 1;
        // printf("this is last index in while %llu<--\n", line_index_post_oper);
        sprintf(buffer, "%llu", line_index_post_oper);
        add_line(list, "JPOS", buffer);
        copy_code_list(list, while_list);
        break;
    case EXPR_GT:
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
        init_code_list(while_list, get_last_line_index(list) + 2);
        stmt_generator(while_list, s->body);
        add_line(while_list, "JUMP", buffer);
        line_index_post_oper = get_last_line_index(while_list) + 1;
        // printf("this is last index in while %llu<--\n", line_index_post_oper);
        sprintf(buffer, "%llu", line_index_post_oper);
        add_line(list, "JZERO", buffer);
        copy_code_list(list, while_list);
        break;
    case EXPR_GT_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "SUB", "9");
        init_code_list(while_list, get_last_line_index(list) + 2);
        stmt_generator(while_list, s->body);
        add_line(while_list, "JUMP", buffer);
        line_index_post_oper = get_last_line_index(while_list) + 1;
        // printf("this is last index in while %llu<--\n", line_index_post_oper);
        sprintf(buffer, "%llu", line_index_post_oper);
        add_line(list, "JPOS", buffer);
        copy_code_list(list, while_list);
        break;
    default:
        printf("ERROR|Wrong while expresion\n");
        return;
        break;
    }

    // add_line(list, "JUMP ", line_index);
}

void generate_repeat_loop_code_from_expr(struct CodeList *list, struct stmt *s)
{
    long long line_index = get_last_line_index(list) + 1;
    // printf("this is the start of reapet %llu<--\n", line_index);
    char buffer[20];
    sprintf(buffer, "%llu", line_index);
    stmt_generator(list, s->body);
    generate_from_expr(list, s->expr_list->data->operator_args);
    generate_from_expr(list, s->expr_list->data->operator_args->next);
    char *A = get_reg(s->expr_list->data->operator_args);
    char *B = get_reg(s->expr_list->data->operator_args->next);
    bool is_A_param = is_parameter(s->expr_list->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(s->expr_list->data->operator_args->next->data->ident_name);

    switch (s->expr_list->kind)
    {
    case EXPR_EQ:

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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "ADD", "9");
        add_line(list, "JZERO", buffer);
        break;
    case EXPR_NOT_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "ADD", "9");
        add_line(list, "JPOS", buffer);
        break;
    case EXPR_LT:
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "JPOS", buffer);
        break;
    case EXPR_LT_EQ:
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "STORE", "9");
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
        add_line(list, "SUB", "9");
        add_line(list, "JZERO", buffer);
        break;
    case EXPR_GT:
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
        add_line(list, "JPOS", buffer);
        break;
    case EXPR_GT_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "SUB", "9");
        add_line(list, "JZERO", buffer);
        break;
    default:
        printf("ERROR|Wrong while expresion\n");
        return;
        break;
    }
}

void generate_if_code_from_expr(struct CodeList *list, struct stmt *s)
{
    long long line_index_post_if;
    long long line_index_post_else;
    char buffer[20];
    generate_from_expr(list, s->expr_list->data->operator_args);
    generate_from_expr(list, s->expr_list->data->operator_args->next);
    char *A = get_reg(s->expr_list->data->operator_args);
    char *B = get_reg(s->expr_list->data->operator_args->next);
    bool is_A_param = is_parameter(s->expr_list->data->operator_args->data->ident_name);
    bool is_B_param = is_parameter(s->expr_list->data->operator_args->next->data->ident_name);
    struct CodeList *if_list = (struct CodeList *)malloc(sizeof(struct CodeList));
    struct CodeList *else_list = (struct CodeList *)malloc(sizeof(struct CodeList));

    switch (s->expr_list->kind)
    {
    case EXPR_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "ADD", "9");
        init_code_list(if_list, get_last_line_index(list) + 2);
        stmt_generator(if_list, s->body);
        line_index_post_if = get_last_line_index(if_list) + 2;
        sprintf(buffer, "%llu", line_index_post_if);
        add_line(list, "JPOS", buffer);
        init_code_list(else_list, get_last_line_index(if_list) + 2);
        stmt_generator(else_list, s->else_body);
        line_index_post_else = get_last_line_index(else_list) + 1;
        sprintf(buffer, "%llu", line_index_post_else);
        add_line(if_list, "JUMP", buffer);
        // printf("this is last line of if %llu<--\n", line_index_post_if);
        copy_code_list(list, if_list);
        copy_code_list(list, else_list);
        break;
    case EXPR_NOT_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "ADD", "9");
        init_code_list(if_list, get_last_line_index(list) + 2);
        stmt_generator(if_list, s->body);
        line_index_post_if = get_last_line_index(if_list) + 2;
        sprintf(buffer, "%llu", line_index_post_if);
        add_line(list, "JZERO", buffer);
        init_code_list(else_list, get_last_line_index(if_list) + 2);
        stmt_generator(else_list, s->else_body);
        line_index_post_else = get_last_line_index(else_list) + 1;
        sprintf(buffer, "%llu", line_index_post_else);
        add_line(if_list, "JUMP", buffer);
        // printf("this is last line of if %llu<--\n", line_index_post_if);
        copy_code_list(list, if_list);
        copy_code_list(list, else_list);
        break;
    case EXPR_LT:
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        init_code_list(if_list, get_last_line_index(list) + 2);
        stmt_generator(if_list, s->body);
        line_index_post_if = get_last_line_index(if_list) + 2;
        sprintf(buffer, "%llu", line_index_post_if);
        add_line(list, "JZERO", buffer);
        init_code_list(else_list, get_last_line_index(if_list) + 2);
        stmt_generator(else_list, s->else_body);
        line_index_post_else = get_last_line_index(else_list) + 1;
        sprintf(buffer, "%llu", line_index_post_else);
        add_line(if_list, "JUMP", buffer);
        // printf("this is last line of if %llu<--\n", line_index_post_if);
        copy_code_list(list, if_list);
        copy_code_list(list, else_list);
        break;
    case EXPR_LT_EQ:
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "STORE", "9");
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
        add_line(list, "SUB", "9");
        init_code_list(if_list, get_last_line_index(list) + 2);
        stmt_generator(if_list, s->body);
        line_index_post_if = get_last_line_index(if_list) + 2;
        sprintf(buffer, "%llu", line_index_post_if);
        add_line(list, "JPOS", buffer);
        init_code_list(else_list, get_last_line_index(if_list) + 2);
        stmt_generator(else_list, s->else_body);
        line_index_post_else = get_last_line_index(else_list) + 1;
        sprintf(buffer, "%llu", line_index_post_else);
        add_line(if_list, "JUMP", buffer);
        // printf("this is last line of if %llu<--\n", line_index_post_if);
        copy_code_list(list, if_list);
        copy_code_list(list, else_list);
        break;
    case EXPR_GT:
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
        init_code_list(if_list, get_last_line_index(list) + 2);
        stmt_generator(if_list, s->body);
        line_index_post_if = get_last_line_index(if_list) + 2;
        sprintf(buffer, "%llu", line_index_post_if);
        add_line(list, "JZERO", buffer);
        init_code_list(else_list, get_last_line_index(if_list) + 2);
        stmt_generator(else_list, s->else_body);
        line_index_post_else = get_last_line_index(else_list) + 1;
        sprintf(buffer, "%llu", line_index_post_else);
        add_line(if_list, "JUMP", buffer);
        // printf("this is last line of if %llu<--\n", line_index_post_if);
        copy_code_list(list, if_list);
        copy_code_list(list, else_list);
        break;
    case EXPR_GT_EQ:
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
        add_line(list, "STORE", "9");
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
            add_line(list, "SUBI", A);
        }
        else
        {
            add_line(list, "SUB", A);
        }
        add_line(list, "SUB", "9");
        init_code_list(if_list, get_last_line_index(list) + 2);
        stmt_generator(if_list, s->body);
        line_index_post_if = get_last_line_index(if_list) + 2;
        sprintf(buffer, "%llu", line_index_post_if);
        add_line(list, "JPOS", buffer);
        init_code_list(else_list, get_last_line_index(if_list) + 2);
        stmt_generator(else_list, s->else_body);
        line_index_post_else = get_last_line_index(else_list) + 1;
        sprintf(buffer, "%llu", line_index_post_else);
        add_line(if_list, "JUMP", buffer);
        // printf("this is last line of if %llu<--\n", line_index_post_if);
        copy_code_list(list, if_list);
        copy_code_list(list, else_list);
        break;
    default:
        printf("ERROR|Wrong while expresion\n");
        return;
        break;
    }
}

void generate_from_expr(struct CodeList *list, struct expr *e)
{
    if (!e)
        return;
    switch (e->kind)
    {
    case EXPR_IDENT:
        return;
        break;
    case EXPR_INT_LIT:
        return;
        break;
    case EXPR_ADD:
        generate_from_expr(list, e->data->func_and_args);
        generate_from_expr(list, e->data->func_and_args->next);
        add_call(list, e);
        break;
    case EXPR_SUB:
        generate_from_expr(list, e->data->func_and_args);
        generate_from_expr(list, e->data->func_and_args->next);
        sub_call(list, e);
        break;
    case EXPR_MUL:
        generate_from_expr(list, e->data->func_and_args);
        generate_from_expr(list, e->data->func_and_args->next);
        mul_call(list, e);
        break;
    case EXPR_DIV:
        generate_from_expr(list, e->data->func_and_args);
        generate_from_expr(list, e->data->func_and_args->next);
        div_call(list, e);
        break;
    case EXPR_MOD:
        generate_from_expr(list, e->data->func_and_args);
        generate_from_expr(list, e->data->func_and_args->next);
        mod_call(list, e);
        break;
    case EXPR_ASGN:
        initialize_verible(e->data->operator_args->data->ident_name);
        generate_from_expr(list, e->data->func_and_args->next);
        asg_call(list, e);
        break;
    default:
        printf("ERROR|Wrong operation expresion\n");
        return;
        break;
    }
}

void resolve_expr_int(struct expr *e)
{
    if (!e)
        return;
    if (e->kind == EXPR_IDENT)
    {
        return;
    }
    if (e->kind == EXPR_INT_LIT)
    {
        return;
    }
    resolve_expr_int(e->data->operator_args);
    resolve_expr_int(e->data->operator_args->next);
    unsigned long long A;
    unsigned long long B;
    unsigned long long WYNIK;
    char buffer[20];
    if (e->data->operator_args->kind == EXPR_INT_LIT && e->data->operator_args->next->kind == EXPR_INT_LIT)
    {
        A = strtoull(e->data->operator_args->data->ident_name, NULL, 10);
        B = strtoull(e->data->operator_args->next->data->ident_name, NULL, 10);
        switch (e->kind)
        {
        case EXPR_ADD:
            WYNIK = A + B;
            break;
        case EXPR_SUB:
            if (B > A)
            {
                WYNIK = 0;
            }
            else
            {
                WYNIK = A - B;
            }
            break;
        case EXPR_MUL:
            WYNIK = A * B;
            break;
        case EXPR_DIV:
            if (B == 0)
            {
                WYNIK = 0;
            }
            else
            {
                WYNIK = A / (unsigned long long)B;
            }
            break;
        case EXPR_MOD:
            WYNIK = A % B;
            break;
        default:
            printf("ERROR|Wrong operation expresion\n");
            return;
            break;
        }
        expr_free_oper(e->data->operator_args);
        sprintf(buffer, "%llu", WYNIK);
        e->kind = EXPR_INT_LIT;
        e->data->ident_name = strdup(buffer);
        // free(buffer);
    }
}

void expr_change_name(char *name, struct expr *e)
{
    if (!e)
        return;
    if (e->kind == EXPR_IDENT)
    {
        strcat(e->data->ident_name, "_-_");
        strcat(e->data->ident_name, name);
        return;
    }
    if (e->kind == EXPR_INT_LIT)
    {
        return;
    }
    expr_change_name(name, e->data->operator_args);
    expr_change_name(name, e->data->operator_args->next);
    switch (e->kind)
    {
    case EXPR_ADD:
        return;
        break;
    case EXPR_SUB:
        return;
        break;
    case EXPR_MUL:
        return;
        break;
    case EXPR_DIV:
        return;
        break;
    case EXPR_MOD:
        return;
        break;
    default:
        return;
        break;
    }
}

void expr_add_int(struct CodeList *list, struct expr *e)
{
    if (!e)
        return;
    if (e->kind == EXPR_IDENT)
    {
        return;
    }
    if (e->kind == EXPR_INT_LIT)
    {
        if (check_if_initialized(e->data->ident_name) == 0)
        {
            char *buffer = strdup(e->data->ident_name);
            set_register_varible(buffer);
            add_line(list, "SET", buffer);
            add_line(list, "STORE", get_register_index(buffer));
        }
        return;
    }
    expr_add_int(list, e->data->operator_args);
    expr_add_int(list, e->data->operator_args->next);

    switch (e->kind)
    {
    case EXPR_ADD:
        break;
    case EXPR_SUB:
        break;
    case EXPR_MUL:
        break;
    case EXPR_DIV:
        break;
    case EXPR_MOD:
        break;
    case EXPR_ASGN:
        break;
    default:
        return;
        break;
    }
}
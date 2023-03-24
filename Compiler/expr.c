#include "expr.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/* internal helpers */
int oper_precedence(expr_t);
void expr_print_subexpr(struct expr *e, expr_t parent_oper, bool right_oper);
void descape_and_print_str_lit(const char *s);
void descape_and_print_char_lit(char c);
char *descape_char(char c, char delim);

struct expr *expr_create(expr_t expr_type, union expr_data *data)
{

    struct expr *e = malloc(sizeof(*e));
    e->kind = expr_type;
    // this seemed to me a good union applic.ation since the data values are mutually exclusive
    e->data = data;
    e->next = NULL;
    return e;
}

struct expr *expr_create_oper(expr_t expr_type, struct expr *left_arg, struct expr *right_arg)
{
    /* */
    union expr_data *d = malloc(sizeof(*d));
    if (!d)
        return NULL;
    // uniform interface for unary operators: pass as NULL whichever operand is not used
    // fill in with empty placeholders on either side so that we have two operands no matter the operator
    if (!left_arg)
        left_arg = expr_create_empty();
    if (!right_arg)
        right_arg = expr_create_empty();
    left_arg->next = right_arg;
    d->operator_args = left_arg;
    return expr_create(expr_type, d);
}

struct expr *expr_create_identifier(char *ident)
{
    union expr_data *d = malloc(sizeof(*d));
    d->ident_name = ident;
    return expr_create(EXPR_IDENT, d);
}

struct expr *expr_create_integer_literal(char *int_lit)
{
    // unsigned long long num;
    // num = strtoull(int_lit, NULL, 10);
    union expr_data *d = malloc(sizeof(*d));
    d->ident_name = strdup(int_lit);
    // d->int_data = num;

    return expr_create(EXPR_INT_LIT, d);
}

struct expr *expr_create_empty()
{
    return expr_create(EXPR_EMPTY, NULL);
}

char *oper_to_str(expr_t t)
{
    char *strs[] = {" = ", " < ", " <= ", " > ", " >= ", " == ", " != ", " + ", " - ", " * ", " / ", " % "};
    return (t < EXPR_ASGN) ? "" : strs[t - EXPR_ASGN];
}

void expr_print(struct expr *e)
{
    if (!e)
        return;

    switch (e->kind)
    {
    case EXPR_EMPTY:
        break;
    case EXPR_FUNC_CALL:
        expr_print(e->data->func_and_args);
        fputs("(", stdout);
        expr_print_list(e->data->func_and_args->next, ", ");
        fputs(")", stdout);
        break;
    case EXPR_IDENT:
        fputs(e->data->ident_name, stdout);
        break;
    case EXPR_INT_LIT:
        printf("%llu", e->data->int_data);
        break;
    default:
        // operators
        /* this printing code is made elegant by allowing the AST to have empty nodes */
        expr_print_subexpr(e->data->operator_args, e->kind, false);
        fputs(oper_to_str(e->kind), stdout);
        expr_print_subexpr(e->data->operator_args->next, e->kind, true);
        break;
    }
}

void expr_print_subexpr(struct expr *e, expr_t parent_oper, bool right_oper)
{
    if (!e || e->kind == EXPR_EMPTY)
        return;

    // if parent operator is non-commutative and we are the operand opposite the associativy of the operator, wrap in parens ( a - (b - c) | (a = b) = c or (a = &b) = c )
    bool commutativities[] = {false, true, true, true, true, true, true, true, true, true, false, true, false, false, false};
    // false = 0, hence left (0 to left of 1 on number line)
    bool associativities[] = {true, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

    // to see relevance, consider the cases | (3+4)*5 | a - -b | - -(a - - b) |
    bool wrap_in_parens = oper_precedence(parent_oper) > oper_precedence(e->kind) || (parent_oper == e->kind && (parent_oper == EXPR_ADD_INV || parent_oper == EXPR_ADD_ID))
                          // now that I include spaces in my expressions, parentheses are not strictly necessary in this case
                          //|| (parent_oper == EXPR_ADD && e->kind == EXPR_ADD_ID)
                          //|| (parent_oper == EXPR_SUB && e->kind == EXPR_ADD_INV)
                          || (parent_oper == e->kind && parent_oper - EXPR_ASGN < sizeof(commutativities) / sizeof(*commutativities) && !commutativities[parent_oper - EXPR_ASGN] && associativities[parent_oper - EXPR_ASGN] != right_oper);
    if (wrap_in_parens)
        fputs("(", stdout);
    expr_print(e);
    if (wrap_in_parens)
        fputs(")", stdout);
}

void expr_print_list(struct expr *e, char *delim)
{
    if (!e)
        return;

    expr_print(e);
    if (e->next)
        fputs(delim, stdout);
    expr_print_list(e->next, delim);
}

char *descape_char(char c, char delim)
{
    char *clean = malloc(3);
    if (!clean)
    {
        puts("[ERROR|internal] Failed to allocate clean char memory, exiting...");
        exit(EXIT_FAILURE);
    }
    char *writer = clean;
    switch (c)
    {
    case '\n':
        *(writer) = '\\';
        *(++writer) = 'n';
        break;
    case '\\':
        *(writer) = '\\';
        *(++writer) = '\\';
        break;
    default:
        if (c == delim)
        {
            *(writer) = '\\';
            *(++writer) = delim;
        }
        else
            *(writer) = c;
        break;
    }
    *(++writer) = '\0';
    return clean;
}

void descape_and_print_char_lit(char c)
{
    char clean[5] = "'";
    char *clean_c = descape_char(c, '\'');
    strcat(clean, clean_c);
    strcat(clean, "'");
    fputs(clean, stdout);
    free(clean_c);
}

void descape_and_print_str_lit(const char *s)
{
    // we'll need at most twice the characters, plus delimeters, plus nul
    char *clean = malloc(2 * strlen(s) + 3);
    if (!clean)
    {
        puts("Failed to allocate clean char memory, exiting...");
        exit(EXIT_FAILURE);
    }
    clean[0] = '"';
    clean[1] = '\0';
    for (const char *reader = s; *reader; reader++)
    {
        char *next = descape_char(*reader, '"');
        strcat(clean, next);
        free(next);
    }
    strcat(clean, "\"");
    fputs(clean, stdout);
    free(clean);
}

int oper_precedence(expr_t t)
{
    // handle against unlikely empty expr here
    if (t == EXPR_EMPTY)
        return INT_MAX;
    int oper_precs[] = {1, 2, 3, 4, 4, 4, 4, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10};
    return oper_precs[t - EXPR_ASGN];
}

void expr_free_oper(struct expr *e)
{
    if (!e)
    {
        return;
    }

    // recursively free next element in linked list
    expr_free_oper(e->next);
    // check the type of expression and free the corresponding data
    switch (e->kind)
    {
    case EXPR_TEMP:
        break;
    case EXPR_IDENT:
        free(e->data);
        break;
    case EXPR_INT_LIT:
        free(e->data);
        break;
    default:
        expr_free_oper(e->data->operator_args);
        free(e->data);
        break;
    }
    free(e);
}

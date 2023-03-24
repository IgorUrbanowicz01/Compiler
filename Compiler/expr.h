#ifndef EXPR_H
#define EXPR_H

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef enum
{
    /* EXPR_NAME       @ precedence @   commutative? @  associativity @   string  @ */
    EXPR_EMPTY,     // @    11      @                @                @           @
    EXPR_ASGN,      // @    1       @   no           @   right        @   " = "   @
    EXPR_LT,        // @    4       @   yes          @   left         @   " < "   @
    EXPR_LT_EQ,     // @    4       @   yes          @   left         @   " <= "  @
    EXPR_GT,        // @    4       @   yes          @   left         @   " > "   @
    EXPR_GT_EQ,     // @    4       @   yes          @   left         @   " >= "  @
    EXPR_EQ,        // @    4       @   yes          @   left         @   " == "  @
    EXPR_NOT_EQ,    // @    4       @   yes          @   left         @   " != "  @
    EXPR_ADD,       // @    5       @   yes          @   left         @   " + "   @
    EXPR_SUB,       // @    5       @   no           @   left         @   " - "   @
    EXPR_MUL,       // @    6       @   yes          @   left         @   " * "   @
    EXPR_DIV,       // @    6       @   no           @   left         @   " / "   @
    EXPR_MOD,       // @    6       @   no           @   left         @   " % "   @
    EXPR_ADD_ID,    // @    8       @                @                @   "+"     @
    EXPR_ADD_INV,   // @    8       @                @                @   "-"     @
    EXPR_FUNC_CALL, // @    10      @                @                @           @
    EXPR_IDENT,     // @    10      @                @                @           @
    EXPR_INT_LIT,   // @    10      @                @                @           @
    EXPR_TEMP
} expr_t;

union expr_data
{
    char *ident_name;
    const char *str_data;
    unsigned long long int_data;
    struct expr *func_and_args;
    struct expr *operator_args;
};

struct expr
{
    /* used by all kinds of exprs */
    expr_t kind;
    union expr_data *data;
    struct expr *next;
};

struct expr *expr_create(expr_t kind, union expr_data *data);

struct expr *expr_create_oper(expr_t kind, struct expr *left, struct expr *right);
struct expr *expr_create_identifier(char *ident);
struct expr *expr_create_integer_literal(char *int_lit);
struct expr *expr_create_function_call(struct expr *function, struct expr *arg_list);
struct expr *expr_create_empty();
void expr_free_oper(struct expr *e);
void expr_print(struct expr *e);
void expr_print_list(struct expr *e, char *delim);

#endif

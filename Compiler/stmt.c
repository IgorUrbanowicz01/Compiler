#include "stmt.h"
#include <stdlib.h>
#include <stdio.h>

struct stmt *stmt_create(stmt_t kind, struct decl *decl, struct expr *expr_list, struct stmt *body, struct stmt *else_body)
{
    struct stmt *s = malloc(sizeof(*s));
    if (!s)
    {
        puts("Failed to allocate space for stmt, exiting...");
        exit(EXIT_FAILURE);
    }

    s->kind = kind;
    s->decl = decl;
    s->expr_list = expr_list;
    s->body = body;
    s->else_body = else_body;
    s->next = NULL;

    return s;
}

void stmt_print(struct stmt *s, int indents, bool indent_first)
{
    if (!s)
        return;

    // bool indent_next = true;

    for (int i = 0; i < indents; i++)
    {
        printf("  ");
    }

    switch (s->kind)
    {
    case STMT_EXPR:
        expr_print(s->expr_list);
        fputs(";", stdout);
        fputs("\n", stdout);
        break;
    case STMT_IF_ELSE:
        fputs("if( ", stdout);
        expr_print(s->expr_list);
        fputs(" )", stdout);
        bool body_is_not_block = !(s->body->kind == STMT_BLOCK);
        fputs(body_is_not_block ? "\n" : " ", stdout);
        stmt_print(s->body, indents + body_is_not_block, body_is_not_block);
        if (s->body->next)
        {
            fputs("\n", stdout);

            for (int i = 0; i < indents; i++)
            {
                printf("  ");
            }
            fputs("else:", stdout);
            bool body_is_not_block_or_if = !(s->body->next->kind == STMT_BLOCK || s->body->next->kind == STMT_IF_ELSE);
            fputs(body_is_not_block_or_if ? "\n" : " ", stdout);
            stmt_print(s->body->next, indents + body_is_not_block_or_if, body_is_not_block_or_if);
        }
        break;
    case STMT_WRITE:
        fputs("print ", stdout);
        expr_print_list(s->expr_list, ", ");
        fputs(";", stdout);
        fputs("\n", stdout);
        break;
    case STMT_READ:
        fputs("read ", stdout);
        expr_print_list(s->expr_list, ", ");
        fputs(";", stdout);
        fputs("\n", stdout);
        break;
    case STMT_REPEAT:
        fputs("repeat: ", stdout);
        fputs("\n", stdout);
        stmt_print_list(s->body, indents + 1, ", ");
        fputs("until ", stdout);
        expr_print(s->expr_list);
        break;
    case STMT_WHILE:
        fputs("while ", stdout);
        expr_print(s->expr_list);
        fputs("\n", stdout);
        stmt_print_list(s->body, indents + 1, ", ");
        fputs("end while: ", stdout);
        break;
    case STMT_HEAD:
        fputs(s->decl->ident, stdout);
        fputs("(", stdout);
        decl_print_list(s->decl->type->params, indents, "", ", ");
        fputs(")", stdout);
        fputs("\n", stdout);
        stmt_print_list(s->body, indents + 1, ", ");
        break;
    default:
        break;
    }
}

void stmt_print_list(struct stmt *s, int indents, char *delim)
{
    if (!s)
        return;

    stmt_print(s, indents, true);
    stmt_print_list(s->next, indents, delim);
}

int stmt_resolve(struct stmt *s, struct scope *sc, bool verbose)
{
    if (!s)
        return 0;
    int err_count = 0;
    // printf("stmt: received scope with %d params\n", sc->params);
    // err_count += decl_resolve(s->decl, sc, false, verbose);
    // resolve if cond, print par#include "scope.h"ams, for params, general expression
    // err_count += expr_resolve(s->expr_list, sc, verbose);
    // resolve inner scope if block
    // static int i = 0;
    // i++;
    // struct scope *p = sc;
    // if( i == 3 ) printf("scope being nested contains argv? %d\n", (bool) scope_lookup(sc, "argv", true));    // if( i == 3 ) printf("nested scope contains argv? %d\n", (bool) scope_lookup(sc, "argv", false));
    // printf("inner scope next is og scope? %d\n", p == sc->next);
    // if( i == 3 ) printf("nested scope next contains argv? %d\n", (bool) scope_lookup(sc->next, "argv", true));
    // struct scope *inner_sc = scope_enter(sc);
    // printf("stmt: resolving body %d\n", i);
    // err_count += stmt_resolve(s->body, inner_sc, verbose);    // printf("stmt: body resolved %d\n", i);
    // printf("stmt %d has %d errors\n", s->kind, err_count);
    return err_count;
}

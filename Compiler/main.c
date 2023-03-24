#include <stdio.h>
#include "parser.h"
#include "decl.h"
#include "./codeGen/registerHandler.h"
#include "./codeGen/declGen.h"
#include "./codeGen/code.h"
#include "./operations/addOperation.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

typedef enum yytokentype token_t;

extern FILE *yyin;
extern int yylex();
extern char *yytext;
extern int last_int_literal;
extern struct decl *ast;
extern struct decl *procedure;

extern int yyparse();

char *indent_space(int indents);
struct decl *scan_file(char *filename);
int parse_file(char *filename);
void print_ast(struct decl *ast);
int resolve_ast(struct decl *ast, bool verbose);
void process_cl_args(int argc, char **argv, bool *stages, char **to_compile);

/* stages */
int SCAN = 0,
    PARSE = 1,
    PPRINT = 2,
    RESOLVE = 3;

void usage(int return_code, char *called_as)
{
    printf(
        "usage: %s [options]\n"
        "\n"
        "Options:\n"
        "   -scan <file>    Scans <file> and outputs tokens encountered\n"
        "   -parse <file>   Scans <file> quietly and reports whether parse was successful\n"
        "   -print <file>   Scans and parses <file> quietly and outputs a nicely formatted version of the bminor program <file>\n"
        "   -resolve <file> Scans, parses, and builds AST for program <file> quietly, then resolves all variable references\n",
        called_as);
    exit(return_code);
}

int main(int argc, char *argv[])
{
    FILE *fin = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    /* scan */
    if (!fin)
    {
        printf("can't open file");
        exit(1);
    }

    yyin = fin;
    char buffer[20];
    struct CodeList *list = (struct CodeList *)malloc(sizeof(struct CodeList));
    struct CodeList *parameter = (struct CodeList *)malloc(sizeof(struct CodeList));
    struct CodeList *varibles = (struct CodeList *)malloc(sizeof(struct CodeList));
    init_code_list(varibles, 0);
    init_code_list(list, 0);
    init_code_list(parameter, 1);
    add_Operation_to_list(parameter, "./operations/div");
    add_Operation_to_list(parameter, "./operations/mod");
    add_Operation_to_list(parameter, "./operations/mul");
    // print_code_list(parameter);
    yyparse();
    decl_resolve_int(varibles, procedure);
    decl_resolve_int(varibles, ast);
    resolveProcedures(procedure);
    // print_registers();
    long long firstline = decl_generator_procedure(parameter, procedure) + 1;
    sprintf(buffer, "%llu", firstline);
    add_line(list, "JUMP", buffer);
    copy_code_list(list, parameter);
    copy_code_list(list, varibles);
    add_line(list, "SET", "1");
    add_line(list, "STORE", "10");
    decl_generator(list, ast);
    add_line(list, "HALT", NULL);
    // print_code_list(list);
    // print_procedure(procedure);
    // printf("\n");
    // print_ast(ast);
    write_code_list_to_file(list, out);

    return EXIT_SUCCESS;
}
void print_procedure(struct decl *procedure) { decl_print_list(procedure, 0, ";", "\n"); }
void print_ast(struct decl *ast) { decl_print_list(ast, 0, ";", "\n"); }

#ifndef DECL_H
#define DECL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "type.h"
#include "stmt.h"
#include "expr.h"
#include "./codeGen/registerHandler.h"
#include "./codeGen/stmtGen.h"

struct decl
{
	char *ident;
	struct type *type;
	struct stmt *func_body;
	struct decl *next_procedure;
	struct decl *next;
};

struct decl *decl_create(char *name, struct type *type, struct stmt *func_body, struct decl *next, struct decl *next_procedure);
void decl_print(struct decl *d, int indents, char *term);
void decl_print_list(struct decl *d, int indents, char *term, char *delim);
bool decl_find(struct decl *d, char *i_find);
void resolveProcedures(struct decl *d);
void addparameters(char *name, struct decl *p);
void add_verible(char *name, struct decl *p);
void change_name(char *name, struct decl *p);

struct scope;

#endif

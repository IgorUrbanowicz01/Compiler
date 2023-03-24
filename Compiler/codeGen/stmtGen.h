#ifndef STMT_GENERATOR_H
#define STMT_GENERATOR_H

#include <stdlib.h>
#include "../stmt.h"
#include "registerHandler.h"
#include "code.h"
#include "exprGen.h"
#include "procedure.h"
#include "../decl.h"

void stmt_generator(struct CodeList *list, struct stmt *s);
void stmt_resolve_int(struct CodeList *list, struct stmt *s);
void generate_stmt_head(struct CodeList *list, struct stmt *s);
void generate_parameters_code_stmt(struct CodeList *list, struct decl *d, struct decl *current_procedure);
void stmt_change_name(char *name, struct stmt *s);

#endif

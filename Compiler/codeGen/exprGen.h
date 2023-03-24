#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "../expr.h"
#include "registerHandler.h"
#include "code.h"
#include "stmtGen.h"
#include "../stmt.h"
#include "../operations/callOperation.h"
#include <stdbool.h>

void generate_while_loop_code_from_expr(struct CodeList *list, struct stmt *s);
void generate_if_code_from_expr(struct CodeList *list, struct stmt *s);
void generate_repeat_loop_code_from_expr(struct CodeList *list, struct stmt *s);
void generate_from_expr(struct CodeList *list, struct expr *e);
void resolve_expr_int(struct expr *e);
void expr_add_int(struct CodeList *list, struct expr *e);
void expr_change_name(char *name, struct expr *e);

#endif

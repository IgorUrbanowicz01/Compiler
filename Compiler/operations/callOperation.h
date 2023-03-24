#ifndef CALLOPERATION_H
#define CALLOPERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../codeGen/registerHandler.h"
#include "../codeGen/code.h"
#include "../expr.h"

char *get_reg(struct expr *expr);
void mul_call(struct CodeList *list, struct expr *expr);
void div_call(struct CodeList *list, struct expr *expr);
void mod_call(struct CodeList *list, struct expr *expr);
void add_call(struct CodeList *list, struct expr *expr);
void sub_call(struct CodeList *list, struct expr *expr);
void asg_call(struct CodeList *list, struct expr *expr);

#endif

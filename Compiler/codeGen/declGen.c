#include "declGen.h"

void decl_generator(struct CodeList *list, struct decl *d)
{
    stmt_generator(list, d->func_body);
}

void decl_resolve_int(struct CodeList *list, struct decl *d)
{
    if (!d)
        return;
    stmt_resolve_int(list, d->func_body);
    decl_resolve_int(list, d->next_procedure);
}

long long decl_generator_procedure(struct CodeList *list, struct decl *d)
{
    if (!d)
        return get_last_line_index(list);
    decl_generator_procedure(list, d->next_procedure);
    set_register_varible(d->ident);
    add_procedure_line(d->ident, get_last_line_index(list) + 1);
    stmt_generator(list, d->func_body);
    char *jump_reg = get_register_index(d->ident);
    add_line(list, "JUMPI", jump_reg);
    return get_last_line_index(list);
}
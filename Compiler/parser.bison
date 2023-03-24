
%{
#include <stdio.h>
#include "decl.h"
#include "stmt.h"
#include "expr.h"
//#include "param_list.h"
#include "type.h"
#include <stdlib.h>
#include <string.h>
#include "codeGen/registerHandler.h"

//#define YYSTYPE struct decl *

extern char *yytext;
extern char *last_int_literal;
extern int yylex();
extern int yyerror( char *str );
extern int yylineno;
//extern char *clean_string(char *string, char delim);
struct decl *ast;
struct decl *procedure;
struct decl *declere = NULL;
struct decl *parameters = NULL;

%}

%token PROCEDURE
%token IS
%token VAR
%token X_BEGIN
%token END
%token PROGRAM
%token IF
%token THEN
%token ELSE
%token ENDIF
%token WHILE
%token DO
%token ENDWHILE
%token REPEAT
%token UNTIL
%token READ
%token WRITE
%token LPR
%token RPR
%token ASSIGN
%token COMMA
%token SEMICOLON
%token EQ
%token NEQ
%token GT
%token LT
%token LEQ
%token GEQ
%token ADD
%token SUB
%token MUL
%token DIV
%token MOD
%token <ident> IDENT
%token INT_LIT
%token SCAN_ERR
%token TOKEN_EOF


%union {
    struct decl *decl;
    struct stmt *stmt;
    struct expr *expr;
    //struct param_list *param_list;
    struct type *type;
    char *ident;
}

%type <decl>        program decl procedures_decl main declH declSTMT
%type <stmt>        function_head_stmt stmt maybe_stmts  if_stmt write_stmt while_stmt repeat_stmt
%type <expr>        read_stmt expr expr1 expr3 expr4 expr5 expr6  atom 
%type <ident>       ident identE
%type <type>        proc_head proc_headSTMT

%%

program : procedures_decl main
        {procedure = $1; ast = $2; return 1; }
        ;
/* END PROGRAM ================================= BEGIN PROCEDURE */

procedures_decl : procedures_decl PROCEDURE ident proc_head IS VAR decl X_BEGIN maybe_stmts END
            {  $$ = decl_create($3, $4, $9, $7, NULL); $$->next_procedure = $1;}
            | procedures_decl PROCEDURE ident proc_head IS X_BEGIN maybe_stmts END
            { $$ = decl_create($3, $4, $7, NULL, NULL); $$->next_procedure = $1;}
            |
            { $$ = NULL; }
            ;

proc_head: LPR declH RPR
            { $$ = type_create(TYPE_FUNCTION, $2); }
            ;

proc_headSTMT: LPR declSTMT RPR
            { $$ = type_create(TYPE_FUNCTION, $2); }
            ;

/* END PROCEDURE ================================= BEGIN DECLARATIONS */

declSTMT:identE COMMA declSTMT
      { $$  = decl_create($1, type_create(TYPE_INTEGER, NULL), NULL, NULL, NULL); $$->next = $3;}
      | identE 
      { $$  = decl_create($1, type_create(TYPE_INTEGER, NULL), NULL, NULL, NULL);}

declH : ident COMMA declH
      { $$  = decl_create($1, type_create(TYPE_INTEGER, NULL), NULL, NULL, NULL); $$->next = $3; parameters = $$; }
      | ident 
      { $$  = decl_create($1, type_create(TYPE_INTEGER, NULL), NULL, NULL, NULL); parameters = $$;}
      ;

decl : ident COMMA decl
      { $$  = decl_create($1, type_create(TYPE_INTEGER, NULL), NULL, NULL, NULL); $$->next = $3; declere = $$; 
            set_register_varible($1);   
      }
      | ident 
      { $$  = decl_create($1, type_create(TYPE_INTEGER, NULL), NULL, NULL, NULL); declere = $$;
            set_register_varible($1);
      }
      ;



/* END DECLARATIONS ============================ BEGIN MAIN */

main : PROGRAM IS VAR decl X_BEGIN maybe_stmts END
      {$$ = decl_create("MAIN", type_create(TYPE_FUNCTION, NULL), $6, $4, NULL);}
      |PROGRAM IS X_BEGIN maybe_stmts END
      {$$ = decl_create("MAIN", type_create(TYPE_FUNCTION, NULL), $4, NULL, NULL);}
      ;
 
/* END MAIN ============================ BEGIN STATEMENTS */

stmt : expr
      { $$ = stmt_create(STMT_EXPR, NULL, $1, NULL, NULL); }
      | if_stmt
      { $$ = $1; }
      | read_stmt
      { $$ = $1; }
      | write_stmt
      { $$ = $1; }
      | while_stmt
      { $$ = $1; }
      | repeat_stmt
      { $$ = $1; }
      | function_head_stmt
      { $$ = $1; }
     ;


if_stmt : IF expr THEN maybe_stmts ELSE maybe_stmts ENDIF
        { $$ = stmt_create(STMT_IF_ELSE, NULL, $2, $4, $6); }
        | IF expr THEN maybe_stmts ENDIF
        { $$ = stmt_create(STMT_IF_ELSE, NULL, $2, $4, NULL); }
        ;

read_stmt : READ atom SEMICOLON
      { $$ = stmt_create(STMT_READ, NULL, $2, NULL, NULL);}
      ;

write_stmt: WRITE atom SEMICOLON
      { $$ = stmt_create(STMT_WRITE, NULL, $2, NULL, NULL);}
      ;

while_stmt: WHILE expr DO maybe_stmts ENDWHILE
      { $$ = stmt_create(STMT_WHILE, NULL, $2, $4, NULL);}
      ;

repeat_stmt: REPEAT maybe_stmts UNTIL expr SEMICOLON 
      { $$ = stmt_create(STMT_REPEAT, NULL, $4, $2, NULL);}
      ;
function_head_stmt:ident proc_headSTMT SEMICOLON
      { $$ = stmt_create(STMT_HEAD, decl_create($1, $2, NULL, NULL, NULL), NULL, NULL, NULL);}


maybe_stmts : /* empty */
            { $$ = NULL; }
            | stmt maybe_stmts
            { $1->next = $2; $$ = $1; }
            ;

/* END STATEMENTS ============================ BEGIN EXPRESSIONS */

/* expression: can be treated as a single value */
expr : expr6
     { $$ = $1; }
     ;

expr6: atom ASSIGN expr5 SEMICOLON
      { $$ = expr_create_oper(EXPR_ASGN, $1, $3);}
      | expr5
      { $$ = $1; }
      ;

/* comparisons: < <= > >= == != */
expr5 : expr5 LT expr4
      { $$ = expr_create_oper(EXPR_LT, $1, $3); }
      | expr5 LEQ expr4
      { $$ = expr_create_oper(EXPR_LT_EQ, $1, $3); }
      | expr5 GT expr4
      { $$ = expr_create_oper(EXPR_GT, $1, $3); }
      | expr5 GEQ expr4
      { $$ = expr_create_oper(EXPR_GT_EQ, $1, $3); }
      | expr5 EQ expr4
      { $$ = expr_create_oper(EXPR_EQ, $1, $3);}
      | expr5 NEQ expr4
      { $$ = expr_create_oper(EXPR_NOT_EQ, $1, $3); }
      | expr4
      { $$ = $1; }
      ;

/* binary add/sub: + - */
expr4 : expr4 ADD expr3
      { $$ = expr_create_oper(EXPR_ADD, $1, $3); }
      | expr4 SUB expr3
      { $$ = expr_create_oper(EXPR_SUB, $1, $3); }
      | expr3
      { $$ = $1; }
      ;

/* mult/div/mod: * / % */
expr3 : expr3 MUL expr1
      { $$ = expr_create_oper(EXPR_MUL, $1, $3); }
      | expr3 DIV expr1
      { $$ = expr_create_oper(EXPR_DIV, $1, $3); }
      | expr3 MOD expr1
      { $$ = expr_create_oper(EXPR_MOD, $1, $3); }
      | expr1
      { $$ = $1; }
      ;

/* grouping: () [] f() */
expr1 : atom
      { $$ = $1; }
      ;

/* atom: lowest form of expression */
atom : identE
     { $$ = expr_create_identifier($1); /*printf("%s <-- \n", $1);*/ }
     | INT_LIT
     { $$ = expr_create_integer_literal(last_int_literal); /*printf("%d <-- \n", last_int_literal);*/}
     ;

ident: IDENT
     { char *s = strdup($1);
       if (!s){
           fprintf(stdout, "[ERROR|internal] Failed to allocate space for duping identifier.\n");
           exit(EXIT_FAILURE);
       }
       $$ = s;
     }
     ;
identE: IDENT
     { char *s = strdup($1);
       if (!s){
           fprintf(stdout, "[ERROR|internal] Failed to allocate space for duping identifier.\n");
           exit(EXIT_FAILURE);
       }
       if(decl_find(declere, s) || decl_find(parameters, s))
            $$ = s;
       else{
            fprintf(stdout, "[ERROR|identifire] Failed to find decleared varible %s at line: %d \n", s, yylineno);
            exit(EXIT_FAILURE);
      }

     }
     ;


%%

int yyerror( char *str )
{
      fprintf(stderr, "Error at line: %d\n%s\n", yylineno, str);
    return 0;
}

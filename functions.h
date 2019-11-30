#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "symtab.h"
extern int yylineno;
extern void yyerror (char const *);

void declarations(int type, struct val_node *identifier_list);
void assignment_statement(symbol *variable, symbol *expression);
void print_statement(symbol *exprssion);
void procedure_statement(int arg_num, ...);	//... : procedure parameters
void compound_statement(int arg_num, ...);	//...: parameters
void if_statement(int arg_num, symbol *if_expression, symbol *if_statement, ...);	//...:elif_expressions/statements, else_expression
void while_statement(int arg_num, symbol *while_expression, symbol *while_statement);
void for_statement(int arg_num, symbol *for_expression, symbol *in_expression, symbol *statement);
symbol return_statement(symbol *expression);

#endif

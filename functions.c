#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void declarations(int type, struct val_node *identifier_list){
	struct val_node *temp_node;
	symbol sym;
	int arr_size = type / 2, loop;

	for (temp_node = identifier_list; temp_node; temp_node = temp_node->next){
		if(sym_stack_is_full()){
			yyerror("Variable stack is full");
			break;
		}
		if(search(temp_node->name)){
			yyerror(strcat(temp_node->name, " is already declared."));
			continue;
		}
		if (arr_size > 0){
			if(type % 2 == 0){
				sym.value.iptr = (int *)malloc(sizeof(int) * arr_size);
				for(loop = 0; loop < arr_size; loop++){
					sym.value.iptr[loop] = 0;
				}
			}else{
				sym.value.fptr = (float *)malloc(sizeof(float) * arr_size);
				for(loop = 0; loop < arr_size; loop++){
					sym.value.fptr[loop] = 0;
				}
			}
		}else{
			sym.value = (union_val)0;
		}
		sym.name = temp_node->name;
		sym.type = type;
		sym.sym = var;
		push(&sym);
		free(temp_node);
	}
}
void assignment_statement(symbol *variable, symbol *expression){
}

void print_statement(symbol *expression){
	if(!expression)
		return;

	print_sym(expression);
	printf("\n");

	if(!expression->name)
		free(expression);
}

void procedure_statement(int arg_num, ...){	//... : procedure parameters
}

void compound_statement(int arg_num, ...){	//...: parameters
}

void if_statement(int arg_num, symbol *if_expression, symbol *if_statement, ...){	//...:elif_expressions/statements, else_expression
}

void while_statement(int arg_num, symbol *while_expression, symbol *while_statement){
}

void for_statement(int arg_num, symbol *for_expression, symbol *in_expression, symbol *statement){
}

symbol return_statement(symbol *expression){
}


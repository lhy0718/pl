#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "functions.h"

void yyerror_args(int num, ...){
	va_list v;
	int loop=0;
	char msg[50];
	va_start(v, num);
	for(; loop<num; loop++){
		strcat(msg, va_arg(v, char *));
	}
	va_end(v);
	yyerror(msg);
}

void declarations(int type, struct val_node *identifier_list){
	struct val_node *temp_node;
	symbol *sym;
	int arr_size = type / 2, loop, index = 0;

	for (temp_node = identifier_list; temp_node; temp_node = temp_node->next){
		if(sym_stack_is_full()){
			yyerror("Variable stack is full");
			break;
		}
		if(search(temp_node->name)){
			yyerror(strcat(temp_node->name, " is already declared."));
			continue;
		}
		sym = malloc(sizeof(symbol));
		if (arr_size > 0){
			if(type % 2 == 0){
				sym->value.iptr = (int *)malloc(sizeof(int) * arr_size);
				for(loop = 0; loop < arr_size; loop++){
					sym->value.iptr[loop] = 0;
				}
			}else{
				sym->value.fptr = (float *)malloc(sizeof(float) * arr_size);
				for(loop = 0; loop < arr_size; loop++){
					sym->value.fptr[loop] = 0;
				}
			}
		}else{
			sym->value = (union_val)0;
		}
		sym->name = temp_node->name;
		sym->type = type;
		sym->sym = var;
		index++;
		push(sym);
		free(temp_node);
	}
	index_push(index);
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

int getival(symbol *s, int *num){
	_type t = _typeof(s);
	switch(t){
		case _int:
			*num = s->value.ival;
			return 1;
		case _int_elem:
			*num = *s->value.iptr;
			return 1;
		default:
			return 0;
	}
}

int getfval(symbol *s, float *num){
	_type t = _typeof(s);
	switch(t){
		case _float:
			*num = s->value.fval;
			return 1;
		case _float_elem:
			*num = *s->value.fptr;
			return 1;
		default:
			return 0;
	}
}

symbol *sym_add(symbol *s1, symbol *s2){
	_type _t1 = _typeof(s1), _t2 = _typeof(s2);
	int i1, i2;
	float f1, f2;
	char *msg;
	symbol *ret = malloc(sizeof(symbol));
	ret->name = NULL;
	ret->sym = var;
	if(getival(s1, &i1) && getival(s2, &i2)){
		ret->value.ival = i1 + i2;
		ret->type = 0;
		return ret;
	}
	else if(getfval(s1, &f1) && getfval(s2, &f2)){
		ret->type = 1;
		ret->value.fval = f1 + f2;
		return ret;
	}
	yyerror_args(5, "Can't add value type '", _typeof_str(s1), "' and '", _typeof_str(s2), "'.");
	free(ret);
	return NULL;
}

symbol *sym_sub(symbol *s1, symbol *s2){
	_type _t1 = _typeof(s1), _t2 = _typeof(s2);
	int i1, i2;
	float f1, f2;
	char *msg;
	symbol *ret = malloc(sizeof(symbol));
	ret->name = NULL;
	ret->sym = var;
	if(getival(s1, &i1) && getival(s2, &i2)){
		ret->type = 0;
		ret->value.ival = i1 - i2;
		return ret;
	}
	else if(getfval(s1, &f1) && getfval(s2, &f2)){
		ret->type = 1;
		ret->value.fval = f1 - f2;
		return ret;
	}
	yyerror_args(5, "Can't subtract value type '", _typeof_str(s1), "' and '", _typeof_str(s2), "'.");
	free(ret);
	return NULL;
}

symbol *sym_mul(symbol *s1, symbol *s2){
	_type _t1 = _typeof(s1), _t2 = _typeof(s2);
	int i1, i2;
	float f1, f2;
	char *msg;
	symbol *ret = malloc(sizeof(symbol));
	ret->name = NULL;
	ret->sym = var;
	if(getival(s1, &i1) && getival(s2, &i2)){
		ret->type = 0;
		ret->value.ival = i1 * i2;
		return ret;
	}
	else if(getfval(s1, &f1) && getfval(s2, &f2)){
		ret->type = 1;
		ret->value.fval = f1 * f2;
		return ret;
	}
	yyerror_args(5, "Can't multiply value type '", _typeof_str(s1), "' and '", _typeof_str(s2), "'.");
	free(ret);
	return NULL;
}

symbol *sym_div(symbol *s1, symbol *s2){
	_type _t1 = _typeof(s1), _t2 = _typeof(s2);
	int i1, i2;
	float f1, f2;
	char *msg;
	symbol *ret = malloc(sizeof(symbol));
	ret->name = NULL;
	ret->sym = var;
	if(getival(s1, &i1) && getival(s2, &i2)){
		ret->type = 0;
		ret->value.ival = i1 / i2;
		return ret;
	}
	else if(getfval(s1, &f1) && getfval(s2, &f2)){
		ret->type = 1;
		ret->value.fval = f1 / f2;
		return ret;
	yyerror_args(5, "Can't divide value type '", _typeof_str(s1), "' and '", _typeof_str(s2), "'.");
	}
	free(ret);
	return NULL;
}

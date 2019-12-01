#include <string.h>
#include "symtab.h"
#define TRUE 1
#define FALSE 0

void init_stack(void){
	top = -1;
	index_top = -1;
}

int sym_stack_is_full(void){
	return top < STACK_MAX - 1 ? FALSE : TRUE;
}

int push(symbol *sym){
	if(!sym_stack_is_full()){
		sym_stack[++top] = sym;
		return TRUE;
	}
	return FALSE;
}

symbol *pop(void){
	if(top<0)
		return NULL;
	else return sym_stack[top--];
}

int index_stack_is_full(){
	return index_top < INDEX_STACK_MAX - 1 ? FALSE : TRUE;
}

int index_push(int num){
	if(!index_stack_is_full()){
		index_stack[++index_top] = num;
		return TRUE;
	}
	return FALSE;	
}

int index_pop(void){
	if(index_top<0)
		return 0;
	else return index_stack[index_top--];
}

symbol *search(char *_name){
	int loop=top;

	if(top<0)
		return NULL;

	for(; loop>=0; loop--){
		if(strcmp(sym_stack[loop]->name, _name) == 0)
			return sym_stack[loop];
	}
	return NULL;
}

void print_stack(void){
	int loop=top;
	if (top<0){
		printf("stack is empty\n");
		return;
	}
	for(; loop>=0; loop--){
		symbol *sym = sym_stack[loop];
		printf("stack %d -> %s : ", loop, sym->name);
		print_sym(sym);
		printf("\n");
	}
	//for(loop=index_top;loop>=0;loop--){
	//	printf("%d\n", index_stack[loop]);
	//}
}

int8_t _typeof(symbol *_sym){
	symbol sym;
	if(!_sym)
		return _NULL;

	sym = *_sym;
	switch(sym.sym){
		case var:
			if(sym.type % 2 == 0)
				if(sym.type > 1)
					if(!sym.name)
						return _int_elem;		//int array element
					else
						return _int_arr;		//int array
				else
					return _int;				//int
			else
				if(sym.type > 1)
					if(!sym.name)
						return _float_elem;		//float array element
					else
						return _float_arr;		//float array
				else
					return _float;				//float
		case boolean:
			return sym.type ? _false : _true;	//? false : true
		case proc:
			return _proc;						//procedure
		case func:
			return _func;						//function
		default:
			return _unknown;					//unknown
	}
}
void print_sym(symbol *sym){
	int loop, arr_size;
	switch(_typeof(sym)){
		case _NULL:
			printf("undefined");
			return;
		case _false:
			printf("false");
			return;
		case _true:
			printf("true");
			return;
		case _int:
			printf("%d", sym->value.ival);
			return;
		case _float:
			printf("%f", sym->value.fval);
			return;
		case _int_elem:
			printf("%d", *sym->value.iptr);
			return;
		case _float_elem:
			printf("%f", *sym->value.fptr);
			return;
		case _int_arr:
			arr_size = sym->type / 2;

			printf("[ ");
			for(loop = 0; loop < arr_size-1; loop++)
				printf("%d, ", sym->value.iptr[loop]);
			printf("%d ]", sym->value.iptr[arr_size-1]);
			return;
		case _float_arr:
			arr_size = sym->type / 2;

			printf("[ ");
			for(loop = 0; loop < arr_size-1; loop++)
				printf("%f, ", sym->value.fptr[loop]);
			printf("%f ]", sym->value.fptr[arr_size-1]);
			return;
		case _proc:
			printf("procedure");
			return;
		case _func:
			printf("function");
			return;
		default:
			printf("unknown type value");
			return;
	}
}

char *_typeof_str(symbol *sym){
	switch(_typeof(sym)){
		case _int:
		case _int_elem:
			return "int";
		case _float:
		case _float_elem:
			return "float";
		case _int_arr:
		case _float_arr:
			return "array";
		case _proc:
		case _func:
			return "function";
		case _true:
		case _false:
			return "boolean";
		default:
			return "unknown";
	}
}

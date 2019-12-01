#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include <stdint.h>
#define STACK_MAX 1000
#define INDEX_STACK_MAX 1000
typedef void (*funcptr)(void);
typedef union{
	int ival;
	int *iptr;
	float fval;
	float *fptr;
	char *sval;
	funcptr funcptr;
}union_val;

typedef enum{
	boolean,
	var,
	func,
	proc
}sym_type;

typedef struct{
	char* name;	//if name == null then array element or boolean
	int type;		//true: not 0, false/int: 0, float: 1, int[n]: 2n, float[n]: 1+2n
	union_val value;
	sym_type sym;
}symbol;

struct val_node{
	char *name;
	struct val_node *next;
};

struct sym_node{
	symbol sym;
	struct sym_node *next;
};

typedef enum{
	_true = -100,
	_false,
	_NULL = 0,
	_int,
	_float,
	_int_elem,
	_float_elem,
	_int_arr,
	_float_arr,
	_proc,
	_func,
	_unknown
}_type;


static symbol *sym_stack[STACK_MAX];
static int index_stack[INDEX_STACK_MAX];
int top;
int index_top;

void init_stack(void);

int sym_stack_is_full(void);

int push (symbol *);

symbol *pop(void);

int index_stack_is_full(void);

int index_push(int);

int index_pop(void);

symbol *search(char *);

int8_t _typeof(symbol *);

char *_typeof_str(symbol *);

void print_sym(symbol*);

void print_stack(void);

#endif

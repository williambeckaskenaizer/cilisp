#ifndef __cilisp_h_
#define __cilisp_h_
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "cilisp.tab.h"
int yyparse(void);
int yylex(void);
void yyerror(char *);

typedef enum { NUM_TYPE, FUNC_TYPE, SYMFUNC_TYPE , VAR_TYPE} AST_NODE_TYPE;
typedef struct
{
    double value;
} NUMBER_AST_NODE;


typedef struct
{
    char *name;
    struct ast_node *op1;
    struct ast_node *op2;
    struct ast_node *table_node;
} FUNCTION_AST_NODE;

typedef struct
{
    AST_NODE_TYPE type;
    char* name;
    double val;
    struct ast_node *next;
} VAR_AST_NODE;

typedef struct ast_node
{
    AST_NODE_TYPE type;
    union
    {
        NUMBER_AST_NODE number;
        FUNCTION_AST_NODE function;
        VAR_AST_NODE variable;
    } data;
} AST_NODE;


//for holding a vaue Node
AST_NODE *number(double value);
//creating a functional node
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2);
//creating a symbol node
AST_NODE *symbol(char* symName);
//creating the first LET LIST
AST_NODE *LET(AST_NODE *list, );
// a Let statement makes a list of nodes
AST_NODE *let_state(AST_NODE *nlist, AST_NODE *element);
//this one will be when a symbol has a function and we need to get something out of it
AST_NODE *symbol_and_function(AST_NODE *table, AST_NODE *s_expr);
//self explan
void freeNode(AST_NODE *p);
//actually taking the node and evaluating a value from it
double eval(AST_NODE *p);
//the general evaluate fro LET litsts
double calculate(AST_NODE *p, double, double);

double sym_calc(AST_NODE *p)
AST_NODE *elem(char * symbol, AST_NODE* value);

//looking up the symbol in the table and returning its value
double sym_lookup (char* symbol, AST_NODE *table);



#endif

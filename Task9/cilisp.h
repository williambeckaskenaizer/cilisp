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

typedef enum { NUM_TYPE, FUNC_TYPE, SYMFUNC_TYPE , VAR_TYPE, COND_TYPE} AST_NODE_TYPE;

typedef struct
{
    double val;
} NUMBER_AST_NODE;

typedef struct
{
    struct ast_node *cond;
    struct ast_node *res1;
    struct ast_node *res2;
} COND_AST_NODE;


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
        COND_AST_NODE condition;
    } data;
} AST_NODE;


//for holding a vaue Node
AST_NODE *number(double value);
//creating a functional node
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2);
//creating a symbol node
AST_NODE *symbol(char* symName);
//creating the first LET LIST
AST_NODE *letting(AST_NODE *nlist, AST_NODE* element );
// a Let statement makes a list of nodes

//take the condition, if it's 1, point to r1, false, point to r2
AST_NODE *condition(AST_NODE* cond, AST_NODE *r1, AST_NODE *r2);

//this one will be when a symbol has a function and we need to get something out of it
AST_NODE *symbol_and_function(AST_NODE *table, AST_NODE *s_expr);
//self explan
void freeNode(AST_NODE *p);
//actually taking the node and evaluating a value from it
double eval(AST_NODE *p);
//the general evaluate fro LET litsts
double calculate(AST_NODE *p,double,double);

double getInput();

double symbol_calc(AST_NODE *p);

AST_NODE *elem(char * symbol, AST_NODE* value);

//looking up the symbol in the table and returning its value
double sym_find (char* symbol, AST_NODE *table);



#endif

#ifndef __l8t3_h_
#define __l8t3_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "cilisp.tab.h"

int yyparse(void);
int yylex(void);
void yyerror(char *);

// function to calculate expressions
double calc(char *, double, double);

#endif

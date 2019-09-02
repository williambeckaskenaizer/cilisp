#include "cilisp.h"

int main(void)
{
  yyparse();
  return 0;
}

void yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}

// find out which function it is
int resolveFunc(char *func)
{
char *funcs[] = { "neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min", "cbrt", "exp2", "hypot", ""};
  int i = 0;
  while (funcs[i][0] != '\0')
  {
    if (!strcmp(funcs[i], func))
      return i;

    i++;
  }
  yyerror("invalid function"); // paranoic -- should never happen
  return -1;
}

// create a node for a number
AST_NODE *number(double value)
{
  AST_NODE *p;
  size_t nodeSize;

  // allocate space for the fixed sie and the variable part (union)
  nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE);
  if ((p = malloc(nodeSize)) == NULL)
    yyerror("out of memory");

  p->type = NUM_TYPE;
  p->data.number.value = value;

  return p;
}

// create a node for a function
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2)
{
  AST_NODE *p;
  size_t nodeSize;

  // allocate space for the fixed sie and the variable part (union)
  nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
  if ((p = malloc(nodeSize)) == NULL)
    yyerror("out of memory");

  p->type = FUNC_TYPE;
  p->data.function.name = funcName;
  p->data.function.op1 = op1;
  p->data.function.op2 = op2;

  return p;
}

// free a node
void freeNode(AST_NODE *p)
{
  if (!p)
    return;

  if (p->type == FUNC_TYPE)
  {
    free(p->data.function.name);
    freeNode(p->data.function.op1);
    freeNode(p->data.function.op2);
  }

  free (p);
}

double calc(char *func, double op1, double op2) {
    int compares=resolveFunc(func);
  switch(compares){

    case 0:{ return (-op1);         } 
        
    case 1:{ return fabs(op1);      } 
    
    case 2:{ return exp(op1);       }

    case 3:{ return sqrt(op1);      }
            
    case 4:{ return (op1 + op2);    }
        
    case 5:{ return (op1 - op2);    }
        
    case 6:{ return (op1 * op2);    }
       
    case 7:{ return (op1 / op2);    }

    case 8:{ return fmod(op1, op2); }
        
    case 9:{ if (op2 == 2.0)
            { return log(op1);      }
             else 
            { return log10(op1);    }
                                    }
    case 10:{ return pow(op1, op2); }

    case 11:{ return ceil(op1);     }

    case 12:{ return floor(op1);    }

    case 13:{ return exp2(op1);     }

    case 14:{ return cbrt(op1);     }

    case 15:{ return hypot(op1,op2);}
    
    default:
    return 0.0;
    
}
}

void translate(AST_NODE *p)
{
  if (!p)
    return;
  if (p->type == NUM_TYPE) {
    printf("%f",p->data.number.value);
  }
  if (p->type == FUNC_TYPE) {
    switch (resolveFunc(p->data.function.name)) {
    case 4:
      printf(" ( ");
      translate(p->data.function.op1);
      printf(" + ");
      translate(p->data.function.op2);
      printf(" ) ");
      break;
    case 5:
      printf(" ( ");
      translate(p->data.function.op1);
      printf(" - ");
      translate(p->data.function.op2);
      printf(" ) ");
      break;
    case 6:
      printf(" ( ");
      translate(p->data.function.op1);
      printf(" * ");
      translate(p->data.function.op2);
      printf(" ) ");
      break;
    case 7:
      printf(" ( ");
      translate(p->data.function.op1);
      printf(" / ");
      translate(p->data.function.op2);
      printf(" ) ");
      break;
    default:
      printf("%s", p->data.function.name);
      printf(" ( ");
      translate(p->data.function.op1);
      translate(p->data.function.op2);
      printf(" ) ");
    }
  }
}

// TBD: implement


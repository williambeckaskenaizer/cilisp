//henlo

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

double eval(AST_NODE *p) //double
{
  if (!p)
    return 0;
  if (p->type == NUM_TYPE) {
    return p->data.number.value;
  }
  int funcRes = resolveFunc(p->data.function.name);
  if (p->type == FUNC_TYPE) {
    switch (funcRes) {
    case 0:
      printf("neg ");
      return -1 * (eval(p->data.function.op1));
    case 1:
      printf("abs ");
      return fabs(eval(p->data.function.op1));
    case 2:
      printf("exp ");
      return exp(eval(p->data.function.op1));
    case 3:
      printf("sqrt ");
      return sqrt(eval(p->data.function.op1));
    case 4:
      printf("add ");
      
      return eval(p->data.function.op1) + eval(p->data.function.op2);
    case 5:
      printf("sub ");
      return eval(p->data.function.op1) - eval(p->data.function.op2);
    case 6:
      printf("mult ");
      return eval(p->data.function.op1) * eval(p->data.function.op2);
    case 7: //div
      printf("div ");
      return eval(p->data.function.op1) / eval(p->data.function.op2);
    case 8: //remainder
      printf("rem ");
      return fmod(eval(p->data.function.op1), eval(p->data.function.op2));
    case 9: //log
      printf("log ");
      if ((int)p->data.function.op1 == 2) {
        //base 2
        return log2(eval(p->data.function.op1));
      }
      else if ((int)p->data.function.op1 == 10) {
        //base 10
        return log10(eval(p->data.function.op1));
      } else {
        return log(eval(p->data.function.op1));
      }
    case 10: //pow
      printf("pow ");
      return pow(eval(p->data.function.op1), eval(p->data.function.op2));
    case 11:
      printf("max ");
      return fmax(eval(p->data.function.op1), eval(p->data.function.op2));
    case 12:
      printf("min ");
      return fmin(eval(p->data.function.op1), eval(p->data.function.op2));
    default:
    break;
    }
  }
  return 0.0;
}





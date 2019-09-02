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
  char *funcs[] = { "neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min", ""};

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

double translate(AST_NODE *p)
{
  if (!p)
    return 0;
  if (p->type == NUM_TYPE) {
    printf(" %f ",p->data.number.value);
  }
  if (p->type == FUNC_TYPE) {
    switch (resolveFunc(p->data.function.name)) {
    case 4:
      printf(" ( ");
      translate(p->data.function.op1);
        //    printf("lolz %s",p->data.function.name);
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
      printf("%s ", p->data.function.name);
      printf(" ( ");
      translate(p->data.function.op1);
      translate(p->data.function.op2);
      printf(" ) ");
    }
  }
  
    printf("Hit the last thing");
    return 0;
}


// TBD: implement


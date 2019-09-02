#include "cilisp.h"

#define RANDMAX 100;

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
  char *funcs[] = { "neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min", "exp2","cbrt","hypot","print","equal","smaller","larger","rand","read"};

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

void printOut(double result){
  printf("%.2f", result);
}
//still need to convert these to switch and case statements.
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

    case 16:{             }

    case 17: {if(op1 == op2)
      {return 1.0;}
      else
      {return 0.0;}
      }
    case 18: {if(op1 < op2)
      {return 1.0;}
      else
      {return 0.0;}
      }
    case 19:{if (op1 > op2)
      { return 1.0; }
      else
      { return 0.0; }
      }
    case 20: return rand();

    case 21: return getInput();
    default:
    return 0.0;
}
}


double getInput(){
double input = scanf("%g", input);
return input;
}

AST_NODE *condition(AST_NODE* condition, AST_NODE *r1, AST_NODE *r2){
  AST_NODE *N;
  size_t nodeSize;
  nodeSize=sizeof(AST_NODE)+sizeof(VAR_AST_NODE);
  if(( N= malloc(nodeSize))==NULL){
  yyerror("NOT ENOUGH MINERALS, MINE MORE MINERALS ! ");
  }
  //if cond = 0, N.
  N->type = COND_TYPE;
  N->data.condition.cond = condition;
  N->data.condition.res1 = r1;
  N->data.condition.res2 = r2;
  return N;
}



AST_NODE *symbol(char *name){
  AST_NODE *N;
  size_t nodeSize;
  nodeSize=sizeof(AST_NODE)+sizeof(VAR_AST_NODE);
  if(( N= malloc(nodeSize))==NULL){
    yyerror("NOT ENOUGH MINERALS, MINE MORE MINERALS ! ");
  }
  N->type= VAR_TYPE;
  N->data.variable.name= name;
  return N;
}

// create a node for a number
AST_NODE *number(double val)
{
  AST_NODE *N;
  size_t nodeSize;
  // allocate space for fixed size and variable union
  nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE);
  if ((N = malloc(nodeSize)) == NULL)
    yyerror("NOT ENOUGH MINERALS, MINE MORE MINERALS !");
  N->type = NUM_TYPE;
  N->data.number.val = val;
  return N;
}

// create a node for a function
AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2)
{
  AST_NODE *N;
  size_t nodeSize;
  // allocate space for fixed size and variable union
  nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
  if ((N = malloc(nodeSize)) == NULL)
    yyerror("out of memory");
  N->type = FUNC_TYPE;
  N->data.function.name = funcName;
  N->data.function.op1 = op1;
  N->data.function.op2 = op2;
  return N;
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


AST_NODE *elem(char *symbol, AST_NODE *elem1){
AST_NODE *N;
  size_t nodeSize;
  // allocate space for fixed size and variable union
  nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
  if ((N = malloc(nodeSize)) == NULL)
    yyerror("NOT ENOUGH MINERALS, MINE MORE MINERALS ! ");
  N->type = VAR_TYPE;
  N->data.variable.name = symbol;
  N->data.variable.next = NULL;
  N->data.variable.val = eval(elem1);
  return N;

}
//building a basic table node field, labeling and assiging
AST_NODE *symbol_and_function(AST_NODE *table, AST_NODE *s_expr){

  s_expr->data.function.table_node = malloc(sizeof(table));
   s_expr->type = SYMFUNC_TYPE;
  s_expr->data.function.table_node = table;
  return s_expr;

}
//the actuall method for assigning the list from the passed element.
AST_NODE *letting(AST_NODE *list, AST_NODE *elem) {
    AST_NODE *N;
    size_t nodeSize;
    nodeSize = sizeof(AST_NODE) + sizeof(VAR_AST_NODE);
    if ((N = malloc(nodeSize)) == NULL)
        yyerror("NOT ENOUGH MINERALS, MINE MORE MINERALS !");
    N = elem;
    if (list != 0) {
        if ((N->data.variable.next = malloc(nodeSize)) == NULL) {
            yyerror("NOT ENOUGH MINERALS, MINE MORE MINERALS !");
        }
        N->data.variable.next = list;
    } else {
        N->data.variable.next = NULL;
    }
    N->type = VAR_TYPE;
    return N;
}
//sorting out what type of nodes are incoming and routing them effectively
double eval(AST_NODE *N){
if (N ==0){
  return 0.0;
}
//time to actually find the symbol and process it
if(N->type==SYMFUNC_TYPE){
  return(symbol_calc(N));
}//if we have a number pointer then we can return the value contained within the pointed union
if(N->type==NUM_TYPE){
  return N->data.number.val;
}//if we have a joined type of NUM_TYPE then we can go digging for the proper info
if(N->data.function.op1->type==NUM_TYPE){
  N->data.number.val=calc(N->data.function.name, N->data.function.op1->data.number.val, eval(N->data.function.op2));
  N->type=NUM_TYPE;
} else {
  N->data.number.val=calc(N->data.function.name, eval(N->data.function.op1), eval(N->data.function.op2));
}
return N->data.number.val;

if(N->type == COND_TYPE){
  if (eval(N->data.condition.cond)){
    eval(N->data.condition.res1);
    }else{
    eval(N->data.condition.res2);
    } 
}
}

//actually fince the symbol within a given table reference, return error and 0 if not found
double  symbol_find(char* symbol, AST_NODE *table){
while( table != NULL){
  if(strcmp(table->data.variable.name, symbol)==0){
    return ( table->data.variable.val);
  } else {
    table = table->data.variable.next;
  }
}
printf("symbol not found /sad ");
return 0.0;
}


double symbol_calc(AST_NODE *N){
//switch on incoming nodes, find their symbols and evaluate their symbols and attached values for op1 and op2
  while(!(N->data.function.op1->type == NUM_TYPE)){
    switch(N->data.function.op1->type) {
      case NUM_TYPE:
            break;
            //strict enforcement of NUM_TYPE
      case FUNC_TYPE:{
        N->data.function.op1->type=SYMFUNC_TYPE;
        N->data.function.op1->data.function.table_node=malloc(sizeof(N->data.function.table_node));
         N->data.function.op1->data.function.table_node= N->data.function.table_node;
          N->data.function.op1->data.number.val=eval(N->data.function.op1);
           N->data.function.op1->type=NUM_TYPE;
           break;
           //FUNC_TYPE getting evaluated as it should and finding the proper values of op1
      }
      case VAR_TYPE: {
        N->data.function.op1->data.number.val=symbol_find(N->data.function.op1->data.variable.name,N->data.function.table_node);
        N->data.function.op1->type= NUM_TYPE;
        break;
        //VAR_TYPE holds an assignment for a variable/name combo so find the reference and return a double value
      }
      default :
      //otherwise symbol and node combo was not found
      printf("Symbol not assigned ! ");
      break;
    }
  }
  //now for op2 if it exists
  if(N->data.function.op2){
while(!(N->data.function.op2->type == NUM_TYPE)){
    switch(N->data.function.op2->type) {
      case NUM_TYPE:
            break;
            //strict enforcement of NUM_TYPE
      case FUNC_TYPE:{
        N->data.function.op2->type=SYMFUNC_TYPE;
        N->data.function.op2->data.function.table_node=malloc(sizeof(N->data.function.table_node));
         N->data.function.op2->data.function.table_node= N->data.function.table_node;
          N->data.function.op2->data.number.val=eval(N->data.function.op2);
           N->data.function.op2->type=NUM_TYPE;
           break;
           //FUNC_TYPE getting evaluated as it should and finding the proper values of op2
      }
      case VAR_TYPE: {
        N->data.function.op2->data.number.val=symbol_find(N->data.function.op2->data.variable.name,N->data.function.table_node);
        N->data.function.op2->type= NUM_TYPE;
        break;
        //VAR_TYPE holds an assignment for a variable/name combo so find the reference and return a double value
      }
      default :
      //otherwise symbol and node combo was not found
      printf("Symbol not assigned ! ");
      break;

    }
  }
}
//if op2 does not contain anything then we must return a valid amount of information in
// the for of op1 and 0
if(!(N->data.function.op2)){
  return(calc(N->data.function.name, N->data.function.op1->data.number.val,0));
}
return (calc(N->data.function.name, N->data.function.op1->data.number.val, 
          N->data.function.op2->data.number.val));


}



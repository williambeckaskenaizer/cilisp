#include "cilisp.h"
#include <math.h>
#include <ctype.h>

int main(void)
{
  yyparse();
  return 0;
}

void yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}

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




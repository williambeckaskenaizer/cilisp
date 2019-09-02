/*

s-expressions calculator

program ::= program s-expr

s-expr ::= number | ( func s-expr ) | ( func s-expr s-expr )

number ::= [ + | - ] digit+ [ . digit+ ] 

digit ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

*/

%{
#include "cilisp.h"
%}

%union
{
   double dval;
   char *sval;
   struct ast_node *astNode;
};

%token <sval> FUNC
%token <dval> NUMBER
%token LPAREN RPAREN EOL QUIT

%type <astNode> s_expr

%%

program:/* empty */ { 
                       printf("> ");
                    }
        | program s_expr EOL {
                              // printf("yacc: program expr\n"); 
                              printf("%lf", eval($2));
                              freeNode($2);
                              printf("\n> "); 
                           }
        ;

s_expr:
        NUMBER {  
                  $$ = number($1); 
               }
        | LPAREN FUNC s_expr RPAREN { 
                                     $$ = function($2, $3, 0);  
                                  }
        | LPAREN FUNC s_expr s_expr RPAREN {
                                          $$ = function($2, $3, $4);
                                       }
        | QUIT { 
                  exit(0);
               }
        
        | error { 
                        printf("error\n"); 
                    }

        ;
%%


/*

s-expressions calculator

program ::= program s-expr

s-expr ::= number | ( func s-expr ) | ( func s-expr s-expr )

number ::= [ + | - ] digit+ [ . digit+ ] 

digit ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

symbol ::= letter+
letter ::= [a-zA-Z]
*/

%{
#include "cilisp.h"
%}

%union
{
   double dval;
   char *sval;
   char *symbol_val;
   struct ast_node *astNode;
};

%token <sval> FUNC
%token <dval> NUMBER
%token LPAREN RPAREN EOL QUIT
%token SYMBOL
%token LET

%type <astNode> s_expr
%type <astNode> let_list
%type <astNode> let_elem

%%

program:/* empty */ { 
                       printf("> ");
                    }
        | program s_expr EOL { 
                              // printf("yacc: program expr\n"); 
                              //translate($2);
                              //freeNode($2);
                              printf( "%lf", eval($2));
                              printf("\n> "); 
                           }
        ;

s_expr:
        NUMBER { 
                  //printf("yacc: NUMBER%lf", $1); 
                  $$ = number($1); 
               }
        | SYMBOL {
                // we found a symbol to make nodes from
                  $$=symbol($1);
                 }        


        | LPAREN FUNC s_expr RPAREN { 
                 // printf("yacc: LPAREN FUNC expr RPAREN\n"); 
                $$ = function($2, $3, 0);  
                //printf("%s(%lf)", $2, $3);
                                  }
        | LPAREN FUNC s_expr s_expr RPAREN {
                                          // printf("LPAREN FUNC expr expr RPAREN\n"); 
                                          // $$ = calc($2, $3, $4); 
                                          $$ = function($2, $3, $4);
                                       }

        
        | LPAREN LPAREN LET let_list RPAREN s_expr RPAREN  {
        //
            $$= symbol_and_function($4,$6);
            
         }

        |  QUIT { 
              
                 // printf("Compilation Error at ", $1)
                  exit(0);
               }


        | error { 
                        printf("error\n"); 
                        //printf("> ");
                    }

        ;

let_list:  let_elem 
            //Dont do somehting here!

        | let_list let_elem 
          {
          //do something here!
            $$ = let_state($1, $2);
          }

        ;       

let_elem: 
          LPAREN SYMBOL s_expr RPAREN
          {// This is triggered when a symbol token is joined with an s_expr
            
           // printf ("Because im a happy element! " );
          $$= elem($2,$3);

          };

%%


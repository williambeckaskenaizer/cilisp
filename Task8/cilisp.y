/*

s-expressions calculator

program ::= program s-expr

s-expr ::= number | ( func s-expr ) | ( func s-expr s-expr ) | ( cond s-expr s-expr s-expr )

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
   char *type;
   struct ast_node *astNode;
};

%token <sval> TYPE
%token <sval> LET
%token <sval> FUNCTION
%token <dval> NUMBER
%token LPAREN 
%token RPAREN 
%token EOL
%token QUIT


%token <symbol_val> ASYMBOL
%token <sval> COND

%type <astNode> s_expr
%type <astNode> let_list
%type <astNode> let_elem

%%

program:/* empty */ { 
                       printf("> ");
                    }
        | program s_expr EOL { 
                  eval($2);
                  printf( "%lf", eval($2));
                  printf("\n> "); 
                     }
        ;

s_expr:
        NUMBER { 
                  //printf("yacc: NUMBER%lf", $1); 
                  $$ = number($1); 
               }
        | ASYMBOL {
                // we found a symbol to make nodes from
                  $$=symbol($1);
                 }
        | LPAREN FUNCTION s-expr_list RPAREN{

        }

        | LPAREN ASYMBOL s-expr_list RPAREN{
        
        }

        | LPAREN FUNCTION s_expr RPAREN { 
                $$ = function($2, $3, 0);  
               
                                  }
        | LPAREN FUNCTION s_expr s_expr RPAREN {
                          // printf("LPAREN FUNC expr expr RPAREN\n"); 
                         
                          $$ = function($2, $3, $4);
                          }
        
        | LPAREN LPAREN LET let_list RPAREN s_expr RPAREN  {
        
            $$= symbol_and_function($6,$4);
            
         }
        | LPAREN COND s_expr s_expr s_expr RPAREN {

        $$ = condition($3, $4, $5);

        }

        | LPAREN FUNCTION RPAREN
        {
        printf("henlo there stinky yacc");
        $$ = function($2, 0, 0);
        }

        |  QUIT { 
              
                 // printf("Compilation Error at ", $1)
                  exit(0);
               }


        | error { 
                        printf("Mooo, yacc does not like this!\n"); 
                        //printf("> ");
                    }

        ;

s-expr_list: s-expr_list s-expr{
  
}

arg_list: ASYMBOL arg_list

let_list:  let_elem {
            $$ = $1
            //Dont do somehting here!
            }
        | let_list let_elem 
          {
          //do something here!
            $$ = letting($1, $2);
          }
        ;       

let_elem: 
          LPAREN TYPE ASYMBOL s_expr RPAREN
          {    $$= elem($3,$4);
           // This is triggered when a symbol token is joined with an s_expr
           // printf ("Because im a happy element! " );
          }
          LPAREN ASYMBOL LPAREN arg_list RPAREN s-expr RPAREN {

          }
          ;
%%


%option noyywrap

%{
    #include "cilisp.h"
%}

digit [0-9]
number {digit}+(\.{digit}+)?
let "let"
type "integer"|"real"|""
func "neg"|"abs"|"exp"|"sqrt"|"add"|"sub"|"mult"|"div"|"remainder"|"log"|"pow"|"max"|"min"|"equal"|"smaller"|"larger"|"rand"


symbol [a-zA-Z]+


%%

{number} {

                yylval.dval = strtod(yytext, NULL);
                //printf("lex: NUMBER dval = %lf\n", yylval.dval);
                return NUMBER;
            }

"quit"      { return QUIT;
             }

"cond"      {
            return COND;
            }


{let}      {
                yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char));
                strcpy(yylval.sval, yytext);
                //we have to return a value  that we care about so that bison can take care of the sequence of tokens using LET
                return LET;
            }
{func}      {   //im getting a function
                yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char));
                strcpy(yylval.sval, yytext);
                
                return FUNCTION;
            }
{type}      {
            yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char));
            strcpy(yylval.sval, yytext);
            return TYPE;
        }

{symbol} {              //hurray I have a symbol
                        yylval.symbol_val = (char *) malloc(strlen(yytext)*sizeof(char));
                        strcpy(yylval.symbol_val, yytext);
                        return ASYMBOL;
            }

"("         {
                //printf("lex: LPAREN\n"); 
                return LPAREN;
            }
")"         {
                //printf("lex: RPAREN\n"); 
                return RPAREN;
            }
"\n"        {
                //printf("lex: RPAREN\n"); 
                return EOL;
            }

[ \t]       ; /* skip whitespace */

.           // yyerror("lex: invalid character");

%%

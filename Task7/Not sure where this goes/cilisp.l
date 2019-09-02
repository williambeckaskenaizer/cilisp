%option noyywrap

%{
    #include "cilisp.h"
%}
letter [a-zA-Z]
symbol letter+
digit [0-9]
number {digit}+(\.{digit}+)?
func "neg"|"abs"|"exp"|"sqrt"|"add"|"sub"|"mult"|"div"|"remainder"|"log"|"pow"|"max"|"min"

%%

\-  { return NEGATIVE;}

{number} {
                yylval.dval = strtod(yytext, NULL);
                //printf("lex: NUMBER dval = %lf\n", yylval.dval);
                return NUMBER;
            }

"quit"      { return QUIT; }


{symbol}    { // If I have an actual symbol 
    yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char));
                strcpy(yylval.sval, yytext);
               
                return SYMBOL;

            }
"let"       {
                //might need the next two lines if flex doesnt cooperate
                //yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char));
               // strcpy(yylval.sval, yytext);
                    return LET;}


{func}      {
                yylval.sval = (char *) malloc(strlen(yytext)*sizeof(char));
                strcpy(yylval.sval, yytext);
                //printf("lex: FUNC sval = %s\n", yylval.sval);
                return FUNC;
            }

\(       { 
                //printf("lex: LPAREN\n"); 
                return LPAREN;
            }
 \)           { 
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

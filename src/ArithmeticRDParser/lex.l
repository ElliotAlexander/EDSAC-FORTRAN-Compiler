%{
#include <cstdio>
#include "parse.tab.h"  // to get the token types from Bison
#include "TOC.h"
%}
%%
[ \t]           ; // consume line by line TODO
[0-9]+\.[0-9]+    { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+            { yylval.ival = atoi(yytext); return INT; }
[A-Z]([A-Z0-9]+)? {
    yylval.vval = strdup(yytext);
    return VARIABLE;
}
\+                { return PLUS; }
\-                { return MINUS; }
\*                { return MUL; }
\/                { return DIV; }
\(                { return LPAREN; }
\)                { return RPAREN; }
\n                { return ENDL; }

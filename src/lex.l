%{
#include <cstdio>
#include "parse.tab.hh"  // to get the token types from Bison
#include "RDParseTreeNode.h"
#include <iostream>

// io.h serves as a Win32 available alternative to unistd.h
// If building for windows, disable the flex import and include it. 
#if defined(_WIN32)
#define YY_NO_UNISTD_H
#include <io.h>
#endif

// This class forms the tokenizer of the arithmetic parser referenced in ArithmeticRDParser.cpp

%}
%option noyywrap
%%
[ \t\n]           ; // consume line by line TODO
[0-9]+\.[0-9]+    { yylval.u.fval = atof(yytext); return FLOAT; }   
[0-9]+            { yylval.u.ival = atoi(yytext); return INT; }
[A-Z]([A-Z0-9]+)? {
    yylval.u.vval = yytext;
    return VARIABLE;
}
\+                { return PLUS; }
\-                { return MINUS; }
\*                { return MUL; }
\/                { return DIV; }
\^                { return EXPONENT; }
\(                { return LPAREN; }
\)                { return RPAREN; }
\,                { return COMMA; }

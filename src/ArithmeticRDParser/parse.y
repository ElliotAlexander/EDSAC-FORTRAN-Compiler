%{
  #include <cstdio>
  #include <iostream>
  #include "TOC/Operation.h"
  #include "TOC/Value.h"
  #include "TOC/Variable.h"
  #include "TOC.h"

  using namespace std;

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
 
  void yyerror(const char *s);
%}

%code requires {
    // This is required to force bison to include TOC before the preprocessing of union types and YYTYPE.
    #include "TOC.h"
}

%union {
  int ival;
  float fval;
  char *vval;
  TOC * toc_T;
}

%token <ival> INT
%token <fval> FLOAT
%token <vval> VARIABLE

%token ENDL PLUS MINUS MUL DIV LPAREN RPAREN

%type <toc_T> expression1
%type <toc_T> expression


%right PLUS MINUS
%right MUL DIV

%start start
%%
start:
    expressions;
expressions:
    expressions expression1 ENDL
    | expression1 ENDL;
expression1:
    expression { 
        TOC* x = $1;
        cout<<x->toTOCStr()<<endl; 
    }; 
expression:
    expression PLUS expression { 
        TOC *a1 = $1;
        TOC *a2 = $3;
        $$ = new Operation(a1, a2, OPS::ADD);
    }
    |expression MINUS expression { 
        TOC *a1 = $1;
        TOC *a2 = $3;
        $$ = new Operation(a1, a2, OPS::SUBTRACT);  
    }
    |expression MUL expression {
        TOC *a1 = $1;
        TOC *a2 = $3;
        $$ = new Operation(a1, a2, OPS::MULTIPLY);
    }
    |expression DIV expression { 
        TOC *a1 = $1;
        TOC *a2 = $3;
        $$ = new Operation(a1, a2, OPS::DIVIDE);
    }
    |LPAREN expression RPAREN { 
        TOC *t = $2; 
        $$ =  t;
    } 
    |INT { 
        $$ =  new Value<int>($1);
    }
    | FLOAT { 
        $$ = new Value<float>($1);
    }
    | VARIABLE {
        char* name = $1;
        $$ = new Variable(name);
    };
%%

void yyerror(const char *s) {
  cout << "Parser Error:  Message: " << s << endl;
  exit(-1);
}

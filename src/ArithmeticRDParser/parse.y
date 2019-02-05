%{
  #include <cstdio>
  #include <iostream>
  #include "TOC/Operation.h"
  #include "TOC/Value.h"
  #include "TOC/Variable.h"
  #include "TOC.h"

  using namespace std;

  extern int yylex();
  extern int yyparse(TOC*);
  extern FILE *yyin;
 
  void yyerror(std::vector<std::string> *result, const char *s);
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

%parse-param {std::vector<std::string> *result} 

%token <ival> INT
%token <fval> FLOAT
%token <vval> VARIABLE

%token ENDL PLUS MINUS MUL DIV LPAREN RPAREN

%type <toc_T> expression1
%type <toc_T> expression
%type <toc_T> start


%left PLUS MINUS
%left MUL DIV

%start start
%%
start:
    expressions;
expressions:
    expressions expression1 ENDL
    | expression1 ENDL;
expression1:
    expression {
        // careful - this will be lost at the end of control flow.
        int variable_index = 0;
        TOC* x = $$;
        std::vector<std::string> y = x->toTOCStr(variable_index);
        result->insert(result->end(), y.begin(), y.end());
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

void yyerror(std::vector<std::string> *result, const char *s) {
  cout << "Parser Error:  Message: " << s << endl;
  exit(-1);
}

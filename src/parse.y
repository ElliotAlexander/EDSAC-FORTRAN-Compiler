%{
    #include <cstdio>
    #include <iostream>
    #include "ArithmeticParser/Operation.h"
    #include "ArithmeticParser/Value.h"
    #include "ArithmeticParser/Variable.h"
    #include "ArithmeticParser/Function.h"
    #include "ArithmeticParser/Wrapper.h"

    #include "ArithmeticRDParser.h"
    #include "TOC.h"
    #include <vector>  

    using namespace std;   

    extern TOC* result_toc_extern;

    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;

    void yyerror(const char *s);

%}

%code requires {

    // This is required to force bison to include TOC before the preprocessing of union types and YYTYPE.
    #include "TOC.h"
    #include <vector>

    struct type_vals {
        union {
            int ival;
            float fval;
            char *vval;
            TOC *toc_T;
        } u;
        std::vector<TOC*> toc_args;
    };
}

%define api.value.type {struct type_vals}

%token <u.ival> INT
%token <u.fval> FLOAT
%token <u.vval> VARIABLE

%token ENDL PLUS MINUS MUL DIV LPAREN RPAREN COMMA

%type <u.toc_T> expression1
%type <u.toc_T> expression
%type <u.toc_T> start
%type <toc_args> arguments
%type <toc_args> single_argument


%left PLUS MINUS
%left MUL DIV

%start start
%%
start:
    expressions;
expressions:
    expressions expression1
    | expression1;
expression1:
    expression {
        TOC* x = $1;
        TOC* result = new Wrapper(x);
        result_toc_extern = result;
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
    | VARIABLE LPAREN arguments RPAREN {
        char* function_name = $1;
        std::vector<TOC*> args = $3;
        $$ = new Function(args, function_name);
    }
    | VARIABLE LPAREN RPAREN {
        char* function_name = $1;
        std::vector<TOC*> args = {};
        $$ = new Function(args, function_name);
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
arguments: 
    single_argument
    | expression COMMA arguments {
        TOC* arg1 = $1;
        std::vector<TOC*> return_arr;
        std::vector<TOC*> stacked_return_arr = $3;
        return_arr.insert(return_arr.end(), stacked_return_arr.begin(), stacked_return_arr.end());
        return_arr.push_back(arg1);
        $$ = return_arr;
    };
single_argument: 
    expression {
        TOC* arg1 = $1;
        std::vector<TOC*> return_arr;
        return_arr.push_back(arg1);
        $$ = return_arr;
    };
%%

void yyerror(const char *s) {
    cout << "Parser Error:  Message: " << s << endl;
    exit(-1);
}

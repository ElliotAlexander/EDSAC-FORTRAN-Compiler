%{
    #include <cstdio>
    #include <iostream>
    #include "ArithmeticParser/Operation.h"
    #include "ArithmeticParser/Value.h"
    #include "ArithmeticParser/Variable.h"
    #include "ArithmeticParser/Function.h"
    #include "TOC.h"
    #include <vector>  

    using namespace std;   

    extern int yylex();
    extern int yyparse(TOC*);
    extern FILE *yyin;

    void yyerror(std::vector<std::string> *result, const char *s);

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


%parse-param {std::vector<std::string> *result} 

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

void yyerror(std::vector<std::string> *result, const char *s) {
    cout << "Parser Error:  Message: " << s << endl;
    exit(-1);
}

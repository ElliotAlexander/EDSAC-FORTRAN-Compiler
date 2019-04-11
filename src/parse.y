%{
    #include <cstdio>
    #include <iostream>
    #include "ArithmeticParser/Operation.h"
    #include "ArithmeticParser/Value.h"
    #include "ArithmeticParser/Variable.h"
    #include "ArithmeticParser/Function.h"

    #include "ArithmeticRDParser.h"
    #include "RDParseTreeNode.h"
    #include <vector>  

    using namespace std;   


    extern int yylex(void);
    extern int yyparse(RDParseTreeNode *&result);
    extern FILE *yyin;

    void yyerror(RDParseTreeNode *&result, const char *s);

%}
%code requires {

    // This is required to force bison to include the parse node structure before the preprocessing of union types and YYTYPE.
    #include "RDParseTreeNode.h"
    #include <vector>

    struct type_vals {
        union {
            int ival;
            float fval;
            char *vval;
            RDParseTreeNode *toc_T;
        } u;
        std::vector<RDParseTreeNode*> toc_args;
    };
}

%define api.value.type {struct type_vals}
%parse-param {RDParseTreeNode *&result}

%token <u.ival> INT
%token <u.fval> FLOAT
%token <u.vval> VARIABLE

%token ENDL PLUS MINUS MUL DIV LPAREN RPAREN COMMA EXPONENT


%type <u.toc_T> top_level_expression
%type <u.toc_T> expression
%type <u.toc_T> start
%type <toc_args> arguments
%type <toc_args> single_argument


%left PLUS MINUS
%left MUL DIV
%right EXPONENT

%start start
%%
start:
    expressions;
expressions:
    expressions top_level_expression
    | top_level_expression;
top_level_expression:
    expression {
        RDParseTreeNode* x = $1;
        result = x;
    };
expression:
    expression PLUS expression { 
        RDParseTreeNode *a1 = $1;
        RDParseTreeNode *a2 = $3;
        $$ = new Operation(a1, a2, OPS::ADD_OPERATION);
    }
    |expression MINUS expression { 
        RDParseTreeNode *a1 = $1;
        RDParseTreeNode *a2 = $3;
        $$ = new Operation(a1, a2, OPS::SUBTRACT_OPERATION);  
    }
    |expression MUL expression {
        RDParseTreeNode *a1 = $1;
        RDParseTreeNode *a2 = $3;
        $$ = new Operation(a1, a2, OPS::MULTIPLY_OPERATION);
    }
    |expression DIV expression { 
        RDParseTreeNode *a1 = $1;
        RDParseTreeNode *a2 = $3;
        $$ = new Operation(a1, a2, OPS::DIVIDE_OPERATION);
    }
    | expression EXPONENT expression {
        RDParseTreeNode *a1 = $1;
        RDParseTreeNode *a2 = $3;
        $$ = new Operation(a1, a2, OPS::EXPONENT_OPERATION);
    }
    | VARIABLE LPAREN arguments RPAREN {
        char* function_name  = $1;
        std::vector<RDParseTreeNode*> args = $3;
        $$ = new Function(args, string(function_name));
    }
    | VARIABLE LPAREN RPAREN {
        char* function_name = $1;
        std::vector<RDParseTreeNode*> args = {};
        $$ = new Function(args, function_name);
    }
    |LPAREN expression RPAREN { 
        RDParseTreeNode *t = $2; 
        $$ =  t;
    } 
    | MINUS INT {
        int x = $2;
        $$ = new Value<int>(0-x);
    }
    | MINUS FLOAT {
        float x = $2;
        $$ = new Value<float>(0-x);
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
        RDParseTreeNode* arg1 = $1;
        std::vector<RDParseTreeNode*> return_arr;
        std::vector<RDParseTreeNode*> stacked_return_arr = $3;
        return_arr.insert(return_arr.end(), stacked_return_arr.begin(), stacked_return_arr.end());
        return_arr.push_back(arg1);
        $$ = return_arr;
    };
single_argument: 
    expression {
        RDParseTreeNode* arg1 = $1;
        std::vector<RDParseTreeNode*> return_arr;
        return_arr.push_back(arg1);
        $$ = return_arr;
    };
%%

void yyerror(RDParseTreeNode *&result, const char *s) {
    cout << "Parser Error:  Message: " << s << endl;
    exit(-1);
}

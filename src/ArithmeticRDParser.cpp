#include "ArithmeticRDParser.h"

#include <iostream>
#include <cstdio>
#include <iostream>
extern int yylex();
extern int yyparse();
extern FILE *yyin;

int parseADString(std::string input)
{
    // open a file handle to a particular file:
    FILE *myfile = fopen("in.snazzle", "r");
    // make sure it's valid:
    if (!myfile) {
        std::cout << "I can't open a.snazzle.file!" << std::endl;
        return -1;
    }
    // Set flex to read from it instead of defaulting to STDIN:
    yyin = myfile;  
    // Parse through the input:
    yyparse();
}
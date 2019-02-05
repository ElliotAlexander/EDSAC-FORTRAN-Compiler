#include "ArithmeticRDParser.h"



#include "TOC/Operation.h"
#include "TOC/Value.h"
#include "TOC/Variable.h"

#include <iostream>
#include <cstdio>
#include <iostream>
extern int yylex();
extern int yyparse(std::vector<std::string> *result);
extern TOC* yylval;
extern FILE *yyin;


int parseADString();

int main(int argc, char* argv[]){
    parseADString();
}

int parseADString()
{
    // open a file handle to a particular file:
    FILE *myfile = fopen("in.txt", "r");
    // make sure it's valid:
    if (!myfile) {
        std::cout << "Failed to open file" << std::endl;
        return -1;
    }
    // Set flex to read from it instead of defaulting to STDIN:
    yyin = myfile;  
    // Parse through the input:
    std::vector<std::string> result;
    yyparse(&result);
    for (int i = 0; i < result.size(); i++) {
		std::cout << result.at(i) << ' ' << std::endl;
	}
}


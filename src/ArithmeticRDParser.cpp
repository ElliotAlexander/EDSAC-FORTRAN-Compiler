#include "ArithmeticParser/ArithmeticRDParser.h"

extern int yylex();
extern int yyparse(std::vector<std::string> *result);
extern TOC* yylval;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);


int parseADString(std::string input_string)
{
    // open a file handle to a particular file:
    // make sure it's valid:


	char cstr[input_string.size() + 1];
	strcpy(cstr, input_string.c_str());	// or pass &s[0]

    std::vector<std::string> result;
    YY_BUFFER_STATE buffer = yy_scan_string(cstr);
    yyparse(&result);
    yy_delete_buffer(buffer);
    for (int i = 0; i < result.size(); i++) {
		std::cout << result.at(i) << ' ' << std::endl;
	}
}


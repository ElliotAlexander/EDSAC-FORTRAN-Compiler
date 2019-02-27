#include "ArithmeticRDParser.h"

extern int yylex();
extern int yyparse(TOC *&result);
extern TOC* yylval;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

std::unique_ptr<TOC> parseADString(std::string input_string)
{
	char cstr[input_string.size() + 1];
	strcpy(cstr, input_string.c_str());
    YY_BUFFER_STATE buffer = yy_scan_string(cstr);
    TOC* x;
    int res = yyparse(x);
    std::unique_ptr<TOC> ptr(x);
    yy_delete_buffer(buffer);
    return ptr;
}


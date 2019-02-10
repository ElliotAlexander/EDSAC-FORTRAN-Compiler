#include "ArithmeticRDParser.h"

extern int yylex();
extern int yyparse();
extern TOC* yylval;

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

TOC* result_toc_extern;


TOC* parseADString(std::string input_string)
{
	char cstr[input_string.size() + 1];
	strcpy(cstr, input_string.c_str());	// or pass &s[0]

    YY_BUFFER_STATE buffer = yy_scan_string(cstr);

    yyparse();
    yy_delete_buffer(buffer);

    return result_toc_extern;
}


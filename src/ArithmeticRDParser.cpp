#include "ArithmeticRDParser.h"


extern int yylex();                             // Needed for flex.lex.cc
extern int yyparse(RDParseTreeNode *&result);   // Needed for flex.lex.cc
extern RDParseTreeNode* yylval;                 // Needed for flex.lex.cc

typedef struct yy_buffer_state * YY_BUFFER_STATE;               // Needed for tab.yy.h
extern YY_BUFFER_STATE yy_scan_string(const char * str);        // needed for tab.yy/h
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);           // Needed for tab.yy.c


//  ParseADString is a hook into the flex + bison arithmetic parser contained within lex.flex.cc and parse.tab.cc
//  yy_scan_str takes an input arithmetic statement, and tokenises the statement into an interpretable stream of tokens.
//  yy_parse then takes this stream, and builds a parse tree node constructed of RDParseTreeNodes from it. 
//  The head of this parse tree (and subsequently all further references) is returned through x, w
std::unique_ptr<RDParseTreeNode> parseADString(std::string input_string)
{
	// MSVC support - no dynamic arrays. 
	char* cstr = (char*)input_string.c_str();       // convert to a raw char*.
    // Note - extern YY_BUFFER_STATE yy_scan_string(const char * str)
    YY_BUFFER_STATE buffer = yy_scan_string(cstr);  // Tokenise the input string
    RDParseTreeNode* x;     
    // Note - extern int yyparse(RDParseTreeNode *&result);
    int res = yyparse(x);   // x is passed by reference and modified in yyparse. This serves as the main 'return' output of the parser.
    if(res != 0){
        Logging::logErrorMessage("Error - arithmetic value " + input_string + " failed to parse correctly.");
        Logging::logErrorMessage("Arithmeric errors are unrecoverable, the compiler will exit.");
        exit(-1);
    }
    std::unique_ptr<RDParseTreeNode> ptr(x);   // x is then converted to a unique ptr,
    yy_delete_buffer(buffer);                  // the token buffer is cleared
    return ptr;                                // responsibility for x is then passed to the calling class, which is responsible for it's management.
}


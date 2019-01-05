#ifndef __STATEMENT_H_INCLUDED
#define __STATEMENT_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "Globals.h"
#include "Token_Headers.h"
#include "Token.h"

class Statement {
    public:
        Statement(std::string statement_body, std::string label, int line_no);
        Token* identifyStatement();
        bool tokenizeStatement(Token* token_type);
    private:
        Token* tokentype;
        std::string statement_body;
        std::string statement_body_nows;
        std::string label;
        int line_no;
};

#endif
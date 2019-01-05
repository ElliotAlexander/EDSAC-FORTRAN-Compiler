#ifndef __CALL_H_INCLUDED
#define __CALL_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class CALL : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "CALL_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
    private:
        std::string TO_MATCH = "CALL"
        + RegexConstants::SUBROUTINE_NAME 
        + "\\("
        + RegexConstants::ANY_ARG_LIST
        + "\\)$";
};


#endif
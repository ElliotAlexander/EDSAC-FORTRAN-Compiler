#ifndef __ARITH_FUNCTION_H_INCLUDED
#define __ARITH_FUNCTION_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class ARITH_FUNCTION : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName();
    private:
        std::string TO_MATCH = RegexConstants::SUBROUTINE_NAME + "\\(" + RegexConstants::MULTI_VARIABLE_LIST + "\\)[=]" + RegexConstants::ANY_ARG_LIST;
    };


#endif
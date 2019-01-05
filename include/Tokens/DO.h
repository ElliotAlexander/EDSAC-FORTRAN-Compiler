#ifndef __DO_H_INCLUDED
#define __DO_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class DO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName();
    private:
        std::string TO_MATCH = "DO([0-9]+)("
            + RegexConstants::VARIABLE_NAME + "|"
            + RegexConstants::INTEGER + 
            + ")=( "
            + RegexConstants::VARIABLE_NAME + "|"
            + RegexConstants::INTEGER + 
            + "),("
            + RegexConstants::VARIABLE_NAME + "|"
            + RegexConstants::INTEGER + 
            + ")(,("
            + RegexConstants::VARIABLE_NAME + "|"
            + RegexConstants::INTEGER + 
            + "))?";
};


#endif
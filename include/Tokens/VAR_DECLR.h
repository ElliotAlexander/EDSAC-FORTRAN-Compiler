#ifndef __VAR_DECLR_H_INCLUDED
#define __VAR_DECLR_H_INCLUDED

#include <vector>
#include "TOC.h"
#include <string>
#include <regex>
#include <iostream>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class VAR_DECLR : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "VAR_DECL_TOKEN"; };
        std::string getRegex(){return TO_MATCH;}
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = RegexConstants::VARIABLE_NAME + "[=]" 
        + "(" 
        + RegexConstants::FUNCTION_CALL
        + "|"
        + RegexConstants::FLOATING_POINT
        + "|"
        + RegexConstants::VARIABLE_NAME 
        + "|"
        + RegexConstants::DIRECT_VAL
        + ")((" 
        + RegexConstants::INLINE_OPERATION 
        + "("
        + RegexConstants::VARIABLE_NAME 
        + "|"
        + RegexConstants::FLOATING_POINT
        + "|"
        + RegexConstants::FUNCTION_CALL
        + "|"
        + RegexConstants::DIRECT_VAL
        + "))+)?";
    };


#endif
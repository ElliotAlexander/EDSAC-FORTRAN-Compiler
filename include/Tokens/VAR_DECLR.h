#ifndef __VAR_DECLR_H_INCLUDED
#define __VAR_DECLR_H_INCLUDED

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
        std::string getRegex(){return TO_MATCH; }
        bool tokenize(std::string input);
    private:
        std::string TO_MATCH = RegexConstants::VARIABLE_NAME + "=" + RegexConstants::ANY_ARG;
    };


#endif
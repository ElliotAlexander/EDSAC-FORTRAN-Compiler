#ifndef __DO_H_INCLUDED
#define __DO_H_INCLUDED

#include <string>
#include "Token.h"
#include "ArithmeticRDParser.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include <vector>
#include "TOC.h"
#include <stdlib.h>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <iostream>

class DO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DO_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
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
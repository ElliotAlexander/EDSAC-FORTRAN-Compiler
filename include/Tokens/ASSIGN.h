#ifndef __ASSIGN_H_INCLUDED
#define __ASSIGN_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class ASSIGN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName();
    private:
        std::string TO_MATCH = "ASSIGN"
            + RegexConstants::ANY_ARG 
            + "TO"
            + "([0-9]+)(.[0-9]+)?";
};


#endif
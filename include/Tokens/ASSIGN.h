#ifndef __ASSIGN_H_INCLUDED
#define __ASSIGN_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include <vector>
#include "TOC.h"
#include "Constants.h"

class ASSIGN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "ASSIGN_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }    
        bool tokenize(std::string input);
        std::vector<TOC> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "ASSIGN"
            + RegexConstants::ANY_ARG 
            + "TO"
            + "([0-9]+)(.[0-9]+)?";
};


#endif
#ifndef __END_H_INCLUDED
#define __END_H_INCLUDED

#include <string>
#include "Token.h"
#include <vector>
#include "TOC.h"
#include "Utils.h"
#include "Constants.h"

class END : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "END_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "END((\\" + RegexConstants::MULTI_VARIABLE_LIST + "\\))?" 
        + "|"
        + "(END)(FILE)"
        + RegexConstants::ANY_ARG;
};


#endif
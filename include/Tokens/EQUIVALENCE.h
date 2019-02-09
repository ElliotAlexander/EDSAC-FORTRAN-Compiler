#ifndef __EQUIVALENCE_H_INCLUDED
#define __EQUIVALENCE_H_INCLUDED

#include <string>
#include <vector>
#include "TOC.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class EQUIVALENCE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "EQUIVALENCE_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "EQUIVALENCE (\\(" + RegexConstants::MULTI_VARIABLE_LIST + "\\))+";
};


#endif
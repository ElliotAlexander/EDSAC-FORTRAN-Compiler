#ifndef __EQUIVALENCE_H_INCLUDED
#define __EQUIVALENCE_H_INCLUDED

#include <vector>
#include <string>
#include <numeric>
#include <iostream>
#include "TOC.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"

class EQUIVALENCE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "EQUIVALENCE_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
        std::vector<std::map<TOC*,TOC*>> equivalence_arguments;
    private:
        std::string TO_MATCH = "EQUIVALENCE(\\(" + RegexConstants::ANY_ARG_LIST + "\\))+";
};


#endif
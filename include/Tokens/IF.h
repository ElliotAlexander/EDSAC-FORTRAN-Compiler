#ifndef __IF_H_INCLUDED
#define __IF_H_INCLUDED

#include <string>
#include <vector>
#include "TOC.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class IF : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "IF_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "IF(\\(" + RegexConstants::ANY_ARG_LIST + "\\)|ACCUMULATOROVERFLOW|QUOTIENTOVERFLOW|DIVIDECHECK)([0-9]+)((,[0-9]+)+)?";

};

#endif
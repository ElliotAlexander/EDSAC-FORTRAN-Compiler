#ifndef __IF_H_INCLUDED
#define __IF_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class IF : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "IF_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
    private:
        std::string TO_MATCH = "IF(\\([A-Z0-9\\.]+\\)|ACCUMULATOROVERFLOW|QUOTIENTOVERFLOW|DIVIDECHECK)([0-9]+)((,[0-9]+)+)?";

};

#endif
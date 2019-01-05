#ifndef __DIMENSION_H_INCLUDED
#define __DIMENSION_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class DIMENSION : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DIMENSION_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
    private:
        std::string TO_MATCH = "COMMON" + RegexConstants::MULTI_VARIABLE_LIST;
};


#endif
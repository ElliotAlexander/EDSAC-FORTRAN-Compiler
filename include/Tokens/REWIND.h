#ifndef __REWIND_H_INCLUDED
#define __REWIND_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class REWIND : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "REWIND_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
    private:
        std::string TO_MATCH = "REWIND" + RegexConstants::VARIABLE_NAME;
};


#endif
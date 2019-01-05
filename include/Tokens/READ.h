#ifndef __READ_H_INCLUDED
#define __READ_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include <boost/algorithm/string.hpp>

class READ : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "READ_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool tokenize(std::string input);
    private:
        std::string TO_MATCH = "READ (T" + RegexConstants::VARIABLE_NAME;
};


#endif
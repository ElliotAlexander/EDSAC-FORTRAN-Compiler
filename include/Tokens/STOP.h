#ifndef __STOP_H_INCLUDED
#define __STOP_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class STOP : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "STOP_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool tokenize(std::string input);
    private:
        std::string TO_MATCH = "STOP([0-9]+)?";
};


#endif
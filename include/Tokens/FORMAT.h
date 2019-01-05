#ifndef __FORMAT_H_INCLUDED
#define __FORMAT_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class FORMAT : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "FORMAT_FUNCTION"; };
        std::string getRegex(){return TO_MATCH; }
        bool tokenize(std::string input);
    private:
        std::string TO_MATCH = "FORMAT\\((((I[0-9]+)|((E|F)[0-9]+.[0-9]+)),?)+\\)";

};

#endif
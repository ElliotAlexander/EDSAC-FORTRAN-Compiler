#ifndef __GOTO_H_INCLUDED
#define __GOTO_H_INCLUDED

#include <string>
#include <vector>
#include "TOC.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "ArithmeticRDParser.h"
#include "Globals.h"

class GOTO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "GOTO_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
        TOC* goto_result;
    private:
        std::string TO_MATCH = "GOTO"
        + RegexConstants::ANY_ARG_LIST;

};

#endif
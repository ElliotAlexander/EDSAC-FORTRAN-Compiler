#ifndef __PAUSE_H_INCLUDED
#define __PAUSE_H_INCLUDED

#include <vector>
#include "TOC.h"
#include "Token.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"

class PAUSE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "PAUSE_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
        TOC* pause_input_variable;
        bool pause_input_variable_set;
    private:
        std::string TO_MATCH = "PAUSE|PAUSE"+RegexConstants::ANY_ARG_LIST;

};

#endif
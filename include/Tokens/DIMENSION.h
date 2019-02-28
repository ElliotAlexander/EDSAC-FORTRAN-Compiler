#ifndef __DIMENSION_H_INCLUDED
#define __DIMENSION_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include <vector>
#include "RDParseTreeNode.h"
#include "Constants.h"

class DIMENSION : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DIMENSION_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<RDParseTreeNode*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "DIMENSION(("
        + RegexConstants::VARIABLE_NAME
        + "\\([0-9]+\\),?)+)";
};


#endif
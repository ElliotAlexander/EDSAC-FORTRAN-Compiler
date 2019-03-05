#ifndef __COMMON_H_INCLUDED
#define __COMMON_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include <vector>
#include "RDParseTreeNode.h"
#include "Constants.h"

class COMMON : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DIMENSION_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::string> generatetoc(int &variable_index);
    private:
        std::string TO_MATCH = "COMMON" + RegexConstants::MULTI_VARIABLE_LIST;
};


#endif
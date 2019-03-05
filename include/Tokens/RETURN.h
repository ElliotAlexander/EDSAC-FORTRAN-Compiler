#ifndef __RETURN_H_INCLUDED
#define __RETURN_H_INCLUDED

#include <vector>
#include "RDParseTreeNode.h"
#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class RETURN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "RETURN_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::string> generatetoc(int &variable_index);
    private:
        std::string TO_MATCH = "RETURN";
};


#endif
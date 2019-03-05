#ifndef __EQUIVALENCE_H_INCLUDED
#define __EQUIVALENCE_H_INCLUDED

#include <vector>
#include <string>
#include <numeric>
#include <iostream>
#include <memory>

#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "Logging.h"

class EQUIVALENCE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "EQUIVALENCE_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::string> generatetoc(int &variable_index);
        std::vector<std::vector<std::unique_ptr<RDParseTreeNode>>> equivalence_arguments;
    private:
        std::string TO_MATCH = "EQUIVALENCE(\\(" + RegexConstants::ANY_ARG_LIST + "\\))+";
};


#endif
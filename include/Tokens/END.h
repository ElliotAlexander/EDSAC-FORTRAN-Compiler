#ifndef __END_H_INCLUDED
#define __END_H_INCLUDED

#include <string>
#include "Token.h"
#include <vector>
#include "RDParseTreeNode.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 

class END : public Token {
    public:
        std::vector<std::unique_ptr<RDParseTreeNode>> argument_list;
        bool isValid(std::string input);
        std::string getTokenName(){return "END_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<RDParseTreeNode*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "END(\\([0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+\\))?|(END)(FILE)"
        + RegexConstants::ANY_ARG;
        bool argument_list_set = false;
};


#endif
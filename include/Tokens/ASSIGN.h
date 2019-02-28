#ifndef __ASSIGN_H_INCLUDED
#define __ASSIGN_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include <vector>
#include "RDParseTreeNode.h"
#include "Constants.h"
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include "Globals.h"
#include "Logging.h"
#include <memory>
#include "ArithmeticRDParser.h"

class ASSIGN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "ASSIGN_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }    
        bool initaliseToken(std::string input);
        std::vector<RDParseTreeNode*> generatetoc(std::string input);
        std::string variable_name;
        std::unique_ptr<RDParseTreeNode> assignment_value;
    private:
        std::string TO_MATCH = "ASSIGN"
            + RegexConstants::ANY_ARG 
            + "TO"
            + "([0-9]+)(.[0-9]+)?";
};


#endif
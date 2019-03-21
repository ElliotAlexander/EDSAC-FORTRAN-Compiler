#ifndef __ASSIGN_H_INCLUDED
#define __ASSIGN_H_INCLUDED

#include "Token.h"
#include "Utils.h"
#include "RDParseTreeNode.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "Globals.h"
#include "Logging.h"
#include "ArithmeticRDParser.h"
#include "SymbolTable/STController.h"


#include <memory>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <string>
#include <vector>


class ASSIGN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "ASSIGN_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }    
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "ASSIGN"
            + RegexConstants::ANY_ARG 
            + "TO([0-9]+)(.[0-9]+)?";
        std::string variable_name;
        std::unique_ptr<RDParseTreeNode> assignment_value;
};


#endif
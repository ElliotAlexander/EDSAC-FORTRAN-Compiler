#ifndef __VAR_DECLR_H_INCLUDED
#define __VAR_DECLR_H_INCLUDED

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <memory>
#include <boost/algorithm/string.hpp>

#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "Logging.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "ThreeOpCode/ThreeOpCode.h"

class VAR_DECLR : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "VAR_DECL_TOKEN"; };
        std::string getRegex(){return TO_MATCH;}
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
        std::string variable_name;
        std::unique_ptr<RDParseTreeNode> right_hand_side_parsed;
    private:
        std::string TO_MATCH = RegexConstants::VARIABLE_NAME + "=(" 
        + RegexConstants::ANY_ARG 
        + "|("
        + RegexConstants::SUBROUTINE_NAME 
        + "\\(" + RegexConstants::ANY_ARG + "((," + RegexConstants::ANY_ARG + ")?)+\\)))+";
    };


#endif
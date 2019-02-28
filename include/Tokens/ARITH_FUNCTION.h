#ifndef __ARITH_FUNCTION_H_INCLUDED
#define __ARITH_FUNCTION_H_INCLUDED

#include <string>
#include "Token.h"
#include "RDParseTreeNode.h"
#include <vector>
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include <boost/algorithm/string.hpp>
#include <memory>
#include "Logging.h"


class ARITH_FUNCTION : public Token {

    public:
        std::string function_name;
        std::unique_ptr<RDParseTreeNode> function_resolution;
        std::vector<std::unique_ptr<RDParseTreeNode>> function_arguments; 
        ARITH_FUNCTION();
        bool isValid(std::string input);
        std::string getTokenName(){return "ARITH_FUNCTION"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<RDParseTreeNode*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = RegexConstants::SUBROUTINE_NAME + "(\\" + RegexConstants::MULTI_VARIABLE_LIST + "\\)[=]" + RegexConstants::ANY_ARG_LIST;
    };


#endif
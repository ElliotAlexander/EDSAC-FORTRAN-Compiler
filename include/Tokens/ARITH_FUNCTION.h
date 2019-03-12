#ifndef __ARITH_FUNCTION_H_INCLUDED
#define __ARITH_FUNCTION_H_INCLUDED

#include "Token.h"
#include "RDParseTreeNode.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "Logging.h"
#include "ThreeOpCode/ThreeOpCode.h"

#include <boost/algorithm/string.hpp>
#include <memory>
#include <string>
#include <vector>

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
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc();
    private:
        std::string TO_MATCH = RegexConstants::SUBROUTINE_NAME + "(\\" + RegexConstants::MULTI_VARIABLE_LIST + "\\)[=]" + RegexConstants::ANY_ARG_LIST;
    };


#endif
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
#include "ProgramStructure/FunctionMapping.h"

#include <boost/algorithm/string.hpp>
#include <memory>
#include <string>
#include <vector>

class ARITH_FUNCTION : public Token {

    public:
        bool initaliseToken(std::string input);
        bool isValid(std::string input);
        std::string getTokenName(){return "ARITH_FUNCTION"; };
        std::string getRegex(){return TO_MATCH; }
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = RegexConstants::SUBROUTINE_NAME + "(\\" + RegexConstants::MULTI_VARIABLE_LIST + "\\)[=]" + RegexConstants::ANY_ARG_LIST;
        std::string function_name;
        std::string function_resolution;
        std::vector<std::string> function_arguments; 
    };


#endif
#ifndef __CALL_H_INCLUDED
#define __CALL_H_INCLUDED

#include "Token.h"
#include "Utils.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "RDParseTreeNode.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "Logging.h"
#include "ProgramStructure/FunctionMapping.h"

#include <vector>
#include <string>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <memory>

class CALL : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "CALL_TOKEN"; };
        std::string getRegex(){return TO_MATCH; } 
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "CALL" + RegexConstants::SUBROUTINE_NAME + "\\(("
        + RegexConstants::ANY_ARG_LIST
        + ")?\\)";
        std::vector<std::unique_ptr<RDParseTreeNode>> subroutine_arguments;
        std::string subroutine_name;
};


#endif
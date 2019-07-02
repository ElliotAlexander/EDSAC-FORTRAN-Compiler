#ifndef __ASSIGNED_GOTO_H_INCLUDED
#define __ASSIGNED_GOTO_H_INCLUDED

#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "ArithmeticRDParser.h"
#include "RDParseTreeNode.h"
#include "Logging.h"
#include "ProgramStructure/LineMapping.h"

#include <string>
#include <vector>
#include <memory>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp> 
#include <boost/lexical_cast.hpp>

class ASSIGNED_GOTO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "ASSIGNED GOTO"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "GOTO" + RegexConstants::VARIABLE_NAME + ",\\(([0-9])+((,[0-9]+)+)?\\)";
        std::vector<std::unique_ptr<RDParseTreeNode>> goto_arg_list;
        std::vector<std::string> goto_arg_list_string;
        std::string goto_variable;

};

#endif
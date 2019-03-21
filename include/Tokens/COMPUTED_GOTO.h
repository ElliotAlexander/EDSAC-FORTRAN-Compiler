#ifndef __COMPUTED_GOTO_H_INCLUDED
#define __COMPUTED_GOTO_H_INCLUDED


#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "ProgramStructure/LineMapping.h"
#include "ArithmeticRDParser.h"

#include <string>
#include <vector>
#include <memory>

class COMPUTED_GOTO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "COMPUTED_GOTO"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "GOTO\\(([0-9])+(,[0-9]+)+\\)," + RegexConstants::VARIABLE_NAME;
        std::vector<std::unique_ptr<RDParseTreeNode>> goto_arg_list;
        std::vector<std::string> goto_arg_list_string;
        std::string goto_variable;

};

#endif
#ifndef __PAUSE_H_INCLUDED
#define __PAUSE_H_INCLUDED

#include <vector>
#include <memory>
#include <string>

#include "RDParseTreeNode.h"
#include "Token.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "Logging.h"

class PAUSE : public Token {
    public:
        bool pause_input_variable_set;
        std::unique_ptr<RDParseTreeNode> pause_input_variable;
        bool isValid(std::string input);
        std::string getTokenName(){return "PAUSE_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<RDParseTreeNode*> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "PAUSE|PAUSE"+RegexConstants::ANY_ARG_LIST;

};

#endif
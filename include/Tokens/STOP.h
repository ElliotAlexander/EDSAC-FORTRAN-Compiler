#ifndef __STOP_H_INCLUDED
#define __STOP_H_INCLUDED

#include <vector>
#include <memory>
#include <string>

#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "Logging.h"
#include "ThreeOpCode/ThreeOpCode.h"

class STOP : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "STOP_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc();
        std::unique_ptr<RDParseTreeNode> stop_input_variable;
        bool stop_input_variable_set = 0;
    private:
        std::string TO_MATCH = "STOP|STOP" + RegexConstants::ANY_ARG_LIST;
};


#endif
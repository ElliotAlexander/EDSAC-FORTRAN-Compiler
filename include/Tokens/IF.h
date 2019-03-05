#ifndef __IF_H_INCLUDED
#define __IF_H_INCLUDED


#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "Logging.h"

#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <memory>

enum IF_STATEMENT_TYPE {
    SENSELIGHT,
    SENSESWITCH,
    ACCUMULATOROVERFLOW,
    QUOTIENTOVERFLOW,
    DIVIDECHECK,
    ARITHMETIC
};

struct StringOperationContainer{
    std::string input_string;
    bool result;
};

class IF : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "IF_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::string> generatetoc(int &variable_index);
        std::vector<std::unique_ptr<RDParseTreeNode>> instruction_values;
        std::unique_ptr<RDParseTreeNode> conditional_variable;
    private:
        std::string TO_MATCH = "IF(\\(" + RegexConstants::ANY_ARG + "\\)|ACCUMULATOROVERFLOW|QUOTIENTOVERFLOW|DIVIDECHECK|(\\(SENSELIGHT[0-9]+\\))|(\\(SENSESWITCH[0-9]+\\)))" + RegexConstants::ANY_ARG_LIST;
        bool parseRightHandSideArguments(std::string right_hand_side_string);
        StringOperationContainer parseFixedConditionalString(std::string conditional_string);
        StringOperationContainer parseConditionalArgument(std::string conditional_argument_string);
        std::string stripIFTag(std::string input);
        IF_STATEMENT_TYPE statement_type;
};

#endif
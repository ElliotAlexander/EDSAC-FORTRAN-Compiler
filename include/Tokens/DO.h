#ifndef __DO_H_INCLUDED
#define __DO_H_INCLUDED

#include "Token.h"
#include "ArithmeticRDParser.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "RDParseTreeNode.h"
#include "Logging.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "ProgramStructure/LineMapping.h"
#include "ProgramStructure/DoLoopMapping.h"

#include <stdlib.h>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <iostream>
#include <memory>
#include <vector>
#include <string>

#define DO_LOOP_DEFAULT_ITERATION_AMOUNT 1
#define DO_LOOP_MINIMUM_SIZE 2
#define DO_LOOP_MAXIMUM_SIZE 3

class DO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DO_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "DO([0-9]+)("
            + RegexConstants::ANY_ARG
            + ")="
            + RegexConstants::POSITIVE_INTEGER
            + ","
            + RegexConstants::POSITIVE_INTEGER
            + "(,"
            + RegexConstants::POSITIVE_INTEGER
            + ")?";
        bool parseLeftHandSide(std::string lhs_input_string);
        bool parseRightHandSide(std::string rhs_input_string);
        std::string line_label_loop_end, main_loop_var_toc;
        int loop_start_value, loop_end_value, loop_iteration_amount = 1;
};


#endif
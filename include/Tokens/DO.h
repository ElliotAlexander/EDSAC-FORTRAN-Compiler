#ifndef __DO_H_INCLUDED
#define __DO_H_INCLUDED

#include <string>
#include "Token.h"
#include "ArithmeticRDParser.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include <vector>
#include "RDParseTreeNode.h"
#include "Logging.h"
#include <stdlib.h>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <iostream>
#include <memory>


class DO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DO_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::string> generatetoc(int &variable_index);
        std::unique_ptr<RDParseTreeNode> control_loop_var_toc, main_loop_var_toc;
        std::vector<std::unique_ptr<RDParseTreeNode>> control_vars_right_toc;
    private:
        std::string TO_MATCH = "DO([0-9]+)("
            + RegexConstants::VARIABLE_NAME + "|"
            + RegexConstants::INTEGER + 
            + ")="
            + RegexConstants::ANY_ARG_LIST;
        bool parseLeftHandSide(std::string lhs_input_string);
        bool parseRightHandSide(std::string rhs_input_string);
};


#endif
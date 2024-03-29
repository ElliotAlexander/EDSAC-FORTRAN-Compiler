#ifndef __GOTO_H_INCLUDED
#define __GOTO_H_INCLUDED

#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "ArithmeticRDParser.h"
#include "Globals.h"
#include "Logging.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "ProgramStructure/LineMapping.h"

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp> 
#include <boost/regex.hpp> 
#include <boost/lexical_cast.hpp>
#include <memory>


struct ARG_LIST_WRAPPER {
    std::string arg_list;
    std::string single_arg;
    bool arg_list_set;
};

class GOTO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "GOTO_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        int goto_single_arg;
        std::vector<std::unique_ptr<RDParseTreeNode>> goto_arg_list;
        std::string TO_MATCH = "GOTO" + RegexConstants::POSITIVE_INTEGER;
        ARG_LIST_WRAPPER loadArgumentString(std::string input_argument_string);
        void loadArgumentListValue(std::string argument_list_string);
        void loadSingleArgumentValue(std::string argument_string);    
    }; 

#endif
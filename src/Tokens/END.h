#ifndef __END_H_INCLUDED
#define __END_H_INCLUDED

#include "Token.h"
#include "RDParseTreeNode.h"
#include "Utils.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include "Logging.h"
#include "ThreeOpCode/ThreeOpCode.h"

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <string>
#include <vector>
#include <memory>

class END : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "END_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "END(\\([0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+\\))?|(END)(FILE)"
        + RegexConstants::ANY_ARG;
        bool argument_list_set = false;
        std::vector<std::unique_ptr<RDParseTreeNode>> argument_list;
};


#endif
#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED

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

class PRINT : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "PRINT"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "PRINT" + RegexConstants::ANY_ARG;
		std::unique_ptr<RDParseTreeNode> print_val;
};

#endif
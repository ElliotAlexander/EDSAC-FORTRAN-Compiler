#ifndef __FUNCTION_H_INCLUDED
#define __FUNCTION_H_INCLUDED

#include <string>
#include <vector>
#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Globals.h"
#include "Logging.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <memory>

class FUNCTION : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "FUNCTION"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc();
    private:
        std::string TO_MATCH = "FUNCTION" + RegexConstants::SUBROUTINE_NAME + "\\((" + RegexConstants::ANY_ARG_LIST + ")?\\)";

};

#endif
#ifndef __READ_H_INCLUDED
#define __READ_H_INCLUDED

#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
#include <memory>

class READ : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "READ_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc();
    private:
        std::string TO_MATCH = "READ (T" + RegexConstants::VARIABLE_NAME;
};

#endif
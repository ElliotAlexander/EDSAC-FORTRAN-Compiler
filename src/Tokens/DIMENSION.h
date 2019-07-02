#ifndef __DIMENSION_H_INCLUDED
#define __DIMENSION_H_INCLUDED

#include "Token.h"
#include "Utils.h"
#include "RDParseTreeNode.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "Logging.h"

#include <string>
#include <vector>
#include <memory>

class DIMENSION : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DIMENSION_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "DIMENSION(("
        + RegexConstants::VARIABLE_NAME
        + "\\([0-9]+\\),?)+)";
};


#endif
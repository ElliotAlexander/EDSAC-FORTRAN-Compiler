#ifndef __REWIND_H_INCLUDED
#define __REWIND_H_INCLUDED

#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"

#include <vector>
#include <string>
#include <memory>

class REWIND : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "REWIND_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "REWIND" + RegexConstants::VARIABLE_NAME;
};


#endif
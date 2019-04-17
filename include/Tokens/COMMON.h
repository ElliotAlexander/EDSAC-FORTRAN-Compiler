#ifndef __COMMON_H_INCLUDED
#define __COMMON_H_INCLUDED

#include "Token.h"
#include "Utils.h"
#include "RDParseTreeNode.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"

#include <string>
#include <vector>
#include <memory>

class COMMON : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "DIMENSION_TOKEN"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "COMMON\\/(" + RegexConstants::VARIABLE_NAME +  ")?\\/" +   RegexConstants::MULTI_VARIABLE_LIST;
        std::string common_block_name;
        std::vector<std::string> common_variable_names;
};


#endif
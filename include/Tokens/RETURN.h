#ifndef __RETURN_H_INCLUDED
#define __RETURN_H_INCLUDED

#include "RDParseTreeNode.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "Token.h"
#include "Utils.h"

#include <string>
#include <vector>
#include <memory>
#include "Constants.h"
#include "ProgramStructure/FunctionMapping.h"
#include "ArithmeticRDParser.h"


class RETURN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "RETURN_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
        bool prepareStatements(); 
    private:
        std::string return_value;
        bool return_value_set;
        std::string TO_MATCH = "RETURN|RETURN" + RegexConstants::ANY_ARG;
};


#endif
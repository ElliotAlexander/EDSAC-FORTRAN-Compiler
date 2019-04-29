#ifndef __CONTINUE_H_INCLUDED
#define __CONTINUE_H_INCLUDED

#include "Token.h"
#include "Utils.h"
#include "RDParseTreeNode.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"
#include "Logging.h"

#include <string>
#include <vector>
#include <memory>

class CONTINUE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "CONTINUE"; };
        std::string getRegex(){ return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
    private:
        std::string TO_MATCH = "CONTINUE";
};


#endif
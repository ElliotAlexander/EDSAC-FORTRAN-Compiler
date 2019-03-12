#ifndef __FORMAT_H_INCLUDED
#define __FORMAT_H_INCLUDED


#include "RDParseTreeNode.h"
#include "Token.h"
#include "Utils.h"
#include "Constants.h"
#include "ThreeOpCode/ThreeOpCode.h"

#include <string>
#include <vector>
#include <memory>

class FORMAT : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "FORMAT_FUNCTION"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc();
    private:
        std::string TO_MATCH = "FORMAT\\(([0-9]+)?(((I[0-9]+)|((E|F|H)[0-9]+.[0-9]+)),?)+\\)";

};

#endif
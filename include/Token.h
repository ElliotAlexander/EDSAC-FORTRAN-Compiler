#ifndef __TOKEN_H_INCLUDED
#define __TOKEN_H_INCLUDED

#include <string>
#include <vector>
#include "Utils.h"
#include "Constants.h"
#include "RDParseTreeNode.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

class Token{
    public:
        bool isValid(std::string input, std::string regex);
        virtual std::string getRegex() = 0;
        virtual std::string getTokenName() = 0;
        virtual bool initaliseToken(std::string input) = 0;
        virtual std::vector<std::string> generatetoc(int &variable_index) = 0;
    private:
};

#endif
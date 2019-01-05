#ifndef __TOKEN_H_INCLUDED
#define __TOKEN_H_INCLUDED

#include <string>
#include "Utils.h"
#include "Constants.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

class Token{
    public:
        bool isValid(std::string input, std::string regex);
        virtual std::string getRegex() = 0;
        virtual std::string getTokenName() = 0;
        virtual bool tokenize(std::string input) = 0;
    private:
};

#endif
#ifndef __DO_H_INCLUDED
#define __DO_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"

class DO : public Token {
    public:
        bool isValid(std::string input);
    private:
        std::string TO_MATCH = "([D][O][1-9]+(((([0-9]+)([a-zA-Z]+)?)+)|([0-9]+))[=](([a-zA-Z]+)(((([0-9]+)([a-zA-Z]+)?)+|[a-zA-Z]+)|([0-9]+))|[0-9]+),(([a-zA-Z]+)(((([0-9]+)([a-zA-Z]+)?)+|[a-zA-Z]+)|([0-9]+))|[0-9]+))\\w+";
};


#endif
#ifndef __GOTO_H_INCLUDED
#define __GOTO_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class GOTO : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName();
    private:
        std::string TO_MATCH = "GOTO([0-9]+)(,\\(([0-9]+)((,[0-9]+)?)+\\))?(,[0-9]+)?";

};

#endif
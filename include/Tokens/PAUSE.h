#ifndef __PAUSE_H_INCLUDED
#define __PAUSE_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class PAUSE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName();
    private:
        std::string TO_MATCH = "PAUSE([0-9]+)?";

};

#endif
#ifndef __RETURN_H_INCLUDED
#define __RETURN_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class RETURN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName();
    private:
        std::string TO_MATCH = "RETURN";
};


#endif
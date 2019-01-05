#ifndef __RETURN_H_INCLUDED
#define __RETURN_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class RETURN : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "RETURN_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool tokenize(std::string input);
    private:
        std::string TO_MATCH = "RETURN";
};


#endif
#ifndef __END_H_INCLUDED
#define __END_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include "Constants.h"

class END : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "END_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
    private:
        std::string TO_MATCH = "END(\\(([A-Z]([0-9A-Z]+)?)((,([A-Z]([A-Z0-9]+)?)+)+)?\\))?";
};


#endif
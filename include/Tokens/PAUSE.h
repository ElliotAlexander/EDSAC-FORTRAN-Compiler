#ifndef __PAUSE_H_INCLUDED
#define __PAUSE_H_INCLUDED

#include <vector>
#include "TOC.h"
#include "Token.h"
#include "Constants.h"

class PAUSE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "PAUSE_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool tokenize(std::string input);
        std::vector<TOC> generatetoc(std::string input);
    private:
        std::string TO_MATCH = "PAUSE([0-9]+)?";

};

#endif
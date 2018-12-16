#ifndef __SUBROUTINE_H_INCLUDED
#define __SUBROUTINE_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Token.h"

class SUBROUTINE : public Token {
    public:
        bool isValid(std::string input);
    private:
        std::string TO_MATCH = "[S][U][B][R][O][U][T][I][N][E]";
};

#endif
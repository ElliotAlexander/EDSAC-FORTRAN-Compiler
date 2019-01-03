#ifndef __SUBROUTINE_H_INCLUDED
#define __SUBROUTINE_H_INCLUDED

#include <string>
#include <regex>
#include <iostream>
#include "Utils.h"
#include "Constants.h"
#include "Token.h"


class SUBROUTINE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName();
    private:
    // Note that the second section of this regex matches subroutines without arguments
    // i.e. SUBROUTINE HelloWorld 
    // It's unclear whether this is strictly in the FORTRAN II spec, TOOD
        std::string TO_MATCH = "SUBROUTINE" 
            + RegexConstants::SUBROUTINE_NAME 
            + "(\\("
            + RegexConstants::MULTI_VARIABLE_LIST
            + "\\))?";
        };

#endif
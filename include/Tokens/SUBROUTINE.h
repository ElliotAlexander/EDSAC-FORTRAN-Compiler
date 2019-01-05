#ifndef __SUBROUTINE_H_INCLUDED
#define __SUBROUTINE_H_INCLUDED

#include <string>
#include "Utils.h"
#include "Constants.h"
#include "Token.h"


class SUBROUTINE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "SUBROUTINE_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool tokenize(std::string input);
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
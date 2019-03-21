#ifndef __SUBROUTINE_H_INCLUDED
#define __SUBROUTINE_H_INCLUDED

#include "RDParseTreeNode.h"
#include "Utils.h"
#include "Constants.h"
#include "Token.h"
#include "ThreeOpCode/ThreeOpCode.h"

#include <string>
#include <vector>
#include <memory>

class SUBROUTINE : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "SUBROUTINE_TOKEN"; };
        std::string getRegex(){return TO_MATCH; }
        bool initaliseToken(std::string input);
        std::vector<std::shared_ptr<ThreeOpCode> > generatetoc(int starting_address);
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
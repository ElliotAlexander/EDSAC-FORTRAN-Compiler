#ifndef __CALL_H_INCLUDED
#define __CALL_H_INCLUDED

#include <string>
#include "Token.h"
#include "Utils.h"
#include <vector>
#include "TOC.h"
#include "Constants.h"
#include "Globals.h"
#include "ArithmeticRDParser.h"
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp> 
#include <memory>
#include "Logging.h"

class CALL : public Token {
    public:
        bool isValid(std::string input);
        std::string getTokenName(){return "CALL_TOKEN"; };
        std::string getRegex(){return TO_MATCH; } 
        bool initaliseToken(std::string input);
        std::vector<TOC*> generatetoc(std::string input);
        std::vector<std::unique_ptr<TOC>> subroutine_arguments;
        std::string subroutine_name;
    private:
        std::string TO_MATCH = "CALL" + RegexConstants::SUBROUTINE_NAME + "\\(("
        + RegexConstants::ANY_ARG_LIST
        + ")?\\)";
};


#endif
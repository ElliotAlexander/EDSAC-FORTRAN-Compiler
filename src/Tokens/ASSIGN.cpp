#include "Tokens/ASSIGN.h"

bool ASSIGN::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(ASSIGN::TO_MATCH)));
}

std::string ASSIGN::getTokenName(){
    return std::string("ASSIGN_TOKEN");
}

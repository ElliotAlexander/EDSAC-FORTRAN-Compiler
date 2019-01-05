#include "Tokens/GOTO.h"

bool GOTO::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(GOTO::TO_MATCH)));
}

std::string GOTO::getTokenName(){
    return std::string("GOTO_TOKEN");
}

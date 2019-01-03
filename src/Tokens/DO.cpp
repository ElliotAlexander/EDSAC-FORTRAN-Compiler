#include "Tokens/DO.h"

bool DO::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(DO::TO_MATCH)));
}

std::string DO::getTokenName(){
    return std::string("DO_TOKEN");
}

#include "Tokens/DIMENSION.h"

bool DIMENSION::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(DIMENSION::TO_MATCH)));
}

std::string DIMENSION::getTokenName(){
    return std::string("DIMENSION_TOKEN");
}

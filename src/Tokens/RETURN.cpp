#include "Tokens/RETURN.h"

bool RETURN::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(RETURN::TO_MATCH)));
}

std::string RETURN::getTokenName(){
    return std::string("RETURN_TOKEN");
}

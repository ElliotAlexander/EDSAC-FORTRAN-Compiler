#include "Tokens/CALL.h"

bool CALL::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(CALL::TO_MATCH)));
}

std::string CALL::getTokenName(){
    return std::string("CALL_TOKEN");
}

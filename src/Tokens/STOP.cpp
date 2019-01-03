#include "Tokens/STOP.h"

bool STOP::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(STOP::TO_MATCH)));
}

std::string STOP::getTokenName(){
    return std::string("STOP_TOKEN");
}

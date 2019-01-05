#include "Tokens/IF.h"

bool IF::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(IF::TO_MATCH)));
}

std::string IF::getTokenName(){
    return std::string("IF_TOKEN");
}

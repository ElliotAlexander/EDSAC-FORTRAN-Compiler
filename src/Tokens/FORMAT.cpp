#include "Tokens/FORMAT.h"

bool FORMAT::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(FORMAT::TO_MATCH)));
}

std::string FORMAT::getTokenName(){
    return std::string("FORMAT_TOKEN");
}

#include "Tokens/VAR_DECLR.h"

bool VAR_DECLR::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(VAR_DECLR::TO_MATCH)));
}

std::string VAR_DECLR::getTokenName(){
    return std::string("VAR_DECLR_TOKEN");
}

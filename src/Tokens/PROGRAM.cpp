#include "Tokens/PROGRAM.h"

bool PROGRAM::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(PROGRAM::TO_MATCH)));
}

std::string PROGRAM::getTokenName(){
    return std::string("PROGRAM_TOKEN");
}

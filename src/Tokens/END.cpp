#include "Tokens/END.h"

bool END::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(END::TO_MATCH)));
}

std::string END::getTokenName(){
    return std::string("END_TOKEN");
}

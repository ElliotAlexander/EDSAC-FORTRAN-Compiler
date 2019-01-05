#include "Tokens/END.h"

bool END::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    std::cout << END::TO_MATCH << std::endl;
    boost::regex expr{END::TO_MATCH};
    return (boost::regex_match(input, expr));
}

std::string END::getTokenName(){
    return std::string("END_TOKEN");
}

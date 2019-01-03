#include "Tokens/ARITH_FUNCTION.h"

bool ARITH_FUNCTION::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(ARITH_FUNCTION::TO_MATCH)));
}

std::string ARITH_FUNCTION::getTokenName(){
    return std::string("ARITH_FUNCTION_TOKEN");
}

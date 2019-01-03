#include "Tokens/SUBROUTINE.h"

bool SUBROUTINE::isValid(std::string input){
    input = ::stripWhitespaceString(input);
    return (std::regex_match(input, std::regex(SUBROUTINE::TO_MATCH)));
}


std::string SUBROUTINE::getTokenName(){
    return std::string("SUBROUTINE_TOKEN");
}


// NOTES ON SUBROUTINE
// The subroutine name consists
// of 1 to 6 alphanumeric characters,
// the first of which is
// alphabetic; the final character must
// not be F if the total number of
// characters is 4, 5, or 6.
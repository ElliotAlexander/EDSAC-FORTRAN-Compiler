#include "Token.h"

bool Token::isValid(std::string input, std::string regex){
    boost::regex expr{regex};
    return (boost::regex_match(input, expr));
}
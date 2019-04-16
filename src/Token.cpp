#include "Token.h"

/**
 * 
 *   Abstract Class Token
 * 
 *      This class represents the top level abstraction for a program statement (a Token)
 *      All tokens must implement the following methods, and Token* is used to pass around instances of tokens.
 *      The only common method is isValid, which takes a tokens REGEX value as an input and validates whether it matches the input string.
 **/

bool Token::isValid(std::string input, std::string regex){
    boost::regex expr{regex};
    return (boost::regex_match(input, expr));
}
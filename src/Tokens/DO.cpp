#include "Tokens/DO.h"

bool DO::isValid(std::string input){
    for(int i=0; i < input.length(); i++)
        if(input[i] == ' ') input.erase(i,1);
    return (std::regex_match(input, std::regex(DO::TO_MATCH)));
}
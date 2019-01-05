#include "Tokens/DO.h"

bool DO::tokenize(std::string input){
    std::string first_two = input.substr(0, 2);
    if(first_two == "DO"){
        input.erase(0,2);

        std::vector<std::string> results;
        boost::split(results, input, [](char c){return c == '=';});
        std::cout << results[0] << std::endl;
        return true;
    } else {
        std::cout << "Syntax error!" << std::endl;
    }

    return false;
}
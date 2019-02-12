#include "Tokens/GOTO.h"

bool GOTO::initaliseToken(std::string input){
    input.erase(input.find("GOTO"), 4);
    if(Globals::dump_parsed_values){
        std::cout << StringConstants::INFO_TAG << "Loaded GOTO String: " << input << std::endl;
    }

    
    TOC* result = ::parseADString(input);
    goto_result = result;

    if(Globals::dump_parsed_values){
        std::cout << StringConstants::INFO_TAG << "Loaded Goto line label: " << goto_result->toValue() << std::endl;
    }
    return true;
}

std::vector<TOC*> GOTO::generatetoc(std::string input){
    return {};
}
#include "Tokens/STOP.h"

bool STOP::initaliseToken(std::string input){

    if(!(input.substr(0,4) == "STOP")){
                std::cerr << StringConstants::ERROR_TAG << "Syntax Error - Failed to parse STOP Statement. " << std::endl 
        << StringConstants::ERROR_TAG << "Couldn't find 'STOP' at start of line." << std::endl
        << StringConstants::ERROR_TAG << "Full statement: { " << input << "}. " << std::endl;
        return 0;  
    }
    // Strip the STOP
    input.erase(input.find("STOP"), 4);

    if(input.length() == 0){
        return 1;
    } else {

        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded Stop String: " << input << std::endl;
        }
        stop_input_variable_set = 1;
        TOC* result = ::parseADString(input);
        stop_input_variable = result;
        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded Stop Variable: " << result->toValue() << std::endl;
        }
        return true;
    }
}

std::vector<TOC*> STOP::generatetoc(std::string input){
    return {};
}
#include "Tokens/PAUSE.h"

bool PAUSE::initaliseToken(std::string input){

    // Strip the PAUSE
    input.erase(input.find("PAUSE"), 5);

    if(input.length() == 0){

        return 1;
    } else {
        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded Pause String: " << input << std::endl;
        }
        pause_input_variable_set = 1;
        TOC* result = ::parseADString(input);
        pause_input_variable = result;
        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Loaded Pause Variable: " << result->toValue() << std::endl;
        }
        return 1;
    }}

std::vector<TOC*> PAUSE::generatetoc(std::string input){
    return {};
}
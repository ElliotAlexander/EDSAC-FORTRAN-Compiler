#include "Tokens/PAUSE.h"

bool PAUSE::initaliseToken(std::string input){

    if(!(input.substr(0,5) == "PAUSE")){   
        Logging::logErrorMessage( "Syntax Error - Failed to parse PAUSE Statement. ");
        Logging::logErrorMessage("Full statement: { " + input + "}. ");
        return 0;  
    }

    // Strip the PAUSE
    input.erase(input.find("PAUSE"), 5);
    if(input.length() == 0){
        return 1;
    } else {
        PAUSE::pause_input_variable = ::parseADString(input);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Pause String: " + input);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Pause Variable: " + PAUSE::pause_input_variable->toValue());
        return 1;
    }

}

std::vector<TOC*> PAUSE::generatetoc(std::string input){
    return {};
}
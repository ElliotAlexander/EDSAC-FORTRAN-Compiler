#include "Tokens/STOP.h"

bool STOP::initaliseToken(std::string input){

    if(!(input.substr(0,4) == "STOP")){
        Logging::logErrorMessage( "Syntax Error - Failed to parse STOP Statement. ");
        Logging::logErrorMessage("Couldn't find 'STOP' at start of line.");
        Logging::logErrorMessage("Full statement: { " + input + "}. ");
        return false;  
    }

    // Strip the STOP
    input.erase(input.find("STOP"), 4);
    if(input.length() == 0){
        return true;
    } else {
        STOP::stop_input_variable_set = 1;
        STOP::stop_input_variable = ::parseADString(input);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Stop String: " + input );
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Stop Variable: " + STOP::stop_input_variable->toValue()); 
        return true;
    }
}

std::vector<RDParseTreeNode*> STOP::generatetoc(std::string input){
    return {};
}
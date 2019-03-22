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
        return true;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> STOP::generatetoc(int starting_address){
    if(stop_input_variable != 0){
        Logging::logErrorMessage("Stop variables are not implemented!");
        return {};
    } else {
        std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::string(""), THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false)));
        return pre_string;
    }
}
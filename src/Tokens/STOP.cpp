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
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
    if(stop_input_variable != 0){


        ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
        Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

        TOC_RETURN_VALUE toc_ret = STOP::stop_input_variable->generateThreeOPCode(starting_address);
        pre_string.insert(pre_string.begin(), toc_ret.pre_string.begin(), toc_ret.pre_string.end());
        
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::string(""), THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false)));
        return pre_string;
    } else {
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::string(""), THREE_OP_CODE_OPERATIONS::STOP_PROGRAM, false)));
        return pre_string;
    }
}
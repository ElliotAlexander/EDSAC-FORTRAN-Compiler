#include "Tokens/RETURN.h"

bool RETURN::initaliseToken(std::string input){
    if(input.substr(0,6) == "RETURN"){
        if(input.length() == 6){
            return true;
        } else {
            input = input.erase(0,6);
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded return value string: " + input);
            RETURN::return_value = ::parseADString(input);
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded return value.");
            RETURN::return_value_set = true;
            return true;
        }
    } else {
        Logging::logErrorMessage("Error parsing RETURN statement - keyword not found.");
    }
    return true;
}

std::vector<std::shared_ptr<ThreeOpCode>> RETURN::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
    if(RETURN::return_value_set){
        TOC_RETURN_VALUE x = RETURN::return_value->generateThreeOPCode(starting_address);
        pre_string.insert(pre_string.begin(), x.pre_string.begin(), x.pre_string.end());
        ::exitFunction(x.call_value);
    } else {
        std::vector<std::shared_ptr<ThreeOpCode> > res = ::exitSubroutine(starting_address);
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("0", THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        pre_string.insert(pre_string.end(), res.begin(), res.end());

        //Closed subroutines should always leave the accumulator empty
        Logging::logInfoMessage("Exiting function");
    }
    return pre_string;
}
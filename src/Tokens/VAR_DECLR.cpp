#include "Tokens/VAR_DECLR.h"

bool VAR_DECLR::initaliseToken(std::string input){

    std::vector<std::string> equals_split;
    boost::split(equals_split, input, boost::is_any_of("="));

    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Variable Declaration String " + input);

    VAR_DECLR::variable_name = equals_split[0];
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, std::string("Loaded Variable Name: " + variable_name));
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, std::string("Loaded Variable Assignment: " + equals_split[1]));
    Logging::logConditionalErrorMessage((equals_split[1] == equals_split[0]), std::string("Self Assignment - Assigning " + equals_split[0] + " to " + equals_split[1] + " isn't supported."));
    
    VAR_DECLR::right_hand_side_parsed = ::parseADString(equals_split[1]);    
    return true;

}

std::vector<std::shared_ptr<ThreeOpCode>> VAR_DECLR::generatetoc(){
    return {};
}
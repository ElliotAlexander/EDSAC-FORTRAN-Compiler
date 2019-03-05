#include "Tokens/ASSIGN.h"

bool ASSIGN::initaliseToken(std::string input){
    if(input.substr(0, 6) == "ASSIGN"){
        std::string input_backup = input;
        input.erase(0,6);

        // We need ot handle this a bit differently
        // For silly reasons, ASSIGN doesn't use an equalls operator,
        // Case: what if a variable name is TOTO
        // ASSIGNTOTOTO5 would be valid.

        std::size_t found = input.find_last_of("TO");
        std::string variable_name_temp = input.substr(0, found-1);
        if(variable_name_temp.length() < 1){
            Logging::logErrorMessage("Failed to parse variable name.");
            ::printErrorLocation(found-1, input);
        }

        std::string assignment_string_temp = input.substr(found+1, input.length() );
        if(assignment_string_temp.length() < 1){
            Logging::logErrorMessage("Failed to parse assignment value.");
            ::printErrorLocation(found+1, input);
        }

        ASSIGN::variable_name = variable_name_temp;
        ASSIGN::assignment_value = ::parseADString(assignment_string_temp);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded variable name : " + variable_name_temp);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded variable assignment : " + assignment_string_temp);
        
        return true;
    } else {
        Logging::logErrorMessage( "Failed to load ASSIGN token - couldn't parse ASSIGN keyword.");
        printErrorLocation(0, input);
        return false;
    }
}

std::vector<std::string> ASSIGN::generatetoc(int &variable_index){
    return {};
}
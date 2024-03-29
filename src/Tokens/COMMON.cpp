#include "Tokens/COMMON.h"

bool COMMON::initaliseToken(std::string input){
    if(input.substr(0,6) == "COMMON"){      
        input.erase(0,6);

        /**
         * Note that we're parsing named common blocks
         **/
        unsigned first_slash = input.find_first_of("/");       
        unsigned last_slash = input.find_last_of("/");
        COMMON::common_block_name = input.substr(first_slash, first_slash - last_slash);           
        Logging::logConditionalInfoMessage(!common_block_name.empty() && Globals::dump_parsed_values, "Loaded named COMMON block " + COMMON::common_block_name);      
        Logging::logConditionalInfoMessage(common_block_name.empty() && Globals::dump_parsed_values, "Loaded default COMMON block. (unnamed) "); 
        input.erase(0, last_slash + 1);         // EVerything useful from this section has been removed.

        // Split the string based upon commas, we effectiveflty have a CSV list of variable names.
        boost::split(COMMON::common_variable_names, input, boost::is_any_of(","));
        if(COMMON::common_variable_names.size() == 0 || COMMON::common_variable_names.size() > 10){    
            Logging::logWarnMessage("Warning - loaded an unusual number of COMMON variables (" + std::to_string(COMMON::common_variable_names.size()) + ").");
        }

        int index = 1;
        for(std::vector<std::string>::iterator it = COMMON::common_variable_names.begin(); it != common_variable_names.end(); ++it){
            Logging::logConditionalErrorMessage((*it).empty(), "Loaded empty variable name in position " + std::to_string(index) + "."); 
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded COMMON variable " + (*it) + ".");
            index++;
        }
        return true;
    } else {
        Logging::logErrorMessage("Assertation error - failed to parse COMMON statement.");
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> COMMON::generatetoc(int starting_address){
    Logging::logErrorMessage("Common blocks are not implenented!");
    return {};
}
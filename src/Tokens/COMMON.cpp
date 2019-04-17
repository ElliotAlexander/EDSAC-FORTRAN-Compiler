#include "Tokens/COMMON.h"

bool COMMON::initaliseToken(std::string input){
    if(input.substr(0,6) == "COMMON"){      // This should only ever trigger if there is some regex problem 
        input.erase(0,6);

        // Extract common block name

        unsigned first_slash = input.find_first_of("/");
        unsigned last_slash = input.find_last_of("/");
        COMMON::common_block_name = input.substr(first_slash, first_slash - last_slash);            // Format is: COMMON/<name>/  We've removed the common, so /<name>/ is what we want.
        Logging::logConditionalInfoMessage(!common_block_name.empty() && Globals::dump_parsed_values, "Loaded named COMMON block " + COMMON::common_block_name);           // If named
        Logging::logConditionalInfoMessage(common_block_name.empty() && Globals::dump_parsed_values, "Loaded default COMMON block. (unnamed) ");                            // If an unnamed common block
        input.erase(0, last_slash);         // EVerything useful from this section has been removed.


        // Extract variables

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
        Logging::logErrorMessage("Failed to parse COMMON statement. This may be a problem with your installations REGEX engine.");
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> COMMON::generatetoc(int starting_address){
    return {};
}
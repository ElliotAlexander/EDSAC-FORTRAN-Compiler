#include "Tokens/FUNCTION_DEFINITION.h"

bool FUNCTION_DEFINITION::initaliseToken(std::string input){
    std::string input_original = input;
    if(input.substr(0, 8) == "FUNCTION"){
        input.erase(0,8);

        const char* target = input.c_str();
        boost::regex subroutine_name_regex("(^([A-Z]+))(.*)");
        boost::cmatch char_matches;

        // Parse control variables to the left of the equals sign.
        if (boost::regex_match(target, char_matches, subroutine_name_regex))
        {
            std::string function_name_string = char_matches[2];
            Logging::logInfoMessage("Loaded Function Name: " + function_name_string);

            std::string function_arguments_string = char_matches[3];
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Function Arguments String: " + function_arguments_string);

            if(function_arguments_string.front() == '('){function_arguments_string.erase(0,1); }
            if(function_arguments_string.back() == ')'){function_arguments_string.pop_back(); }
            Logging::logConditionalInfoMessage(function_arguments_string.empty(), "Loaded no function arguments.");
            if(function_arguments_string.empty()) { return true; }
            
            std::vector<std::string> comma_split_string;
            boost::split(comma_split_string, function_arguments_string, boost::is_any_of(","));
            for(std::vector<std::string>::iterator it = comma_split_string.begin(); it != comma_split_string.end(); ++it){
                Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded function argument: " + (*it));
            }

            return true;            
            
        } else {
            Logging::logErrorMessage("Failed to load function name. ");
            ::printErrorLocation(8, input_original);
        }
    } else {
        Logging::logErrorMessage("Failed to parse function Token. ");
        ::printErrorLocation(0, input);
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> FUNCTION_DEFINITION::generatetoc(int starting_address){
    return {};
}
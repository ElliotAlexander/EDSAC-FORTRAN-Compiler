#include "Tokens/FUNCTION_DEFINITION.h"

bool FUNCTION_DEFINITION::initaliseToken(std::string input){

    // Backup the original input - this is useful for error messages.
    std::string input_original = input;

    // Defensive programming
    // This should never happen
    if(input.substr(0, 8) == "FUNCTION"){

        // Remove the keyword
        input.erase(0,8);


        /**
         * 
         * This regular expression splits the name fo the function away from the array of variables.
         *  
         * The documentation on regex_match is probably worth reading.
         * The string will be split into two matching regex tokens, one for the name and one for the rest of the string.
         * 
         * */
        const char* target = input.c_str();
        boost::regex subroutine_name_regex("(^([A-Z]+))(.*)");
        boost::cmatch char_matches;

        // Parse control variables to the left of the equals sign.
        if (boost::regex_match(target, char_matches, subroutine_name_regex))
        {

            // Pull the funciton name out, 
            std::string function_name_string = char_matches[2];
            Logging::logInfoMessage("Loaded Function Name: " + function_name_string);


            // Set a member variable
            FUNCTION_DEFINITION::function_name = function_name_string;


            // Pull the parameterised arguments out
            std::string function_arguments_string = char_matches[3];
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Function Arguments String: " + function_arguments_string);


            /**
             * 
             *  Remove the brackets around the arguments, then break the string up by commas.
             * 
             **/ 
            if(function_arguments_string.front() == '('){function_arguments_string.erase(0,1); }
            if(function_arguments_string.back() == ')'){function_arguments_string.pop_back(); }
            Logging::logConditionalInfoMessage(function_arguments_string.empty(), "Loaded no function arguments.");
            
            // If there are no arguments, exit now.
            if(function_arguments_string.empty()) { return true; }
            

            /**
             * Now we've remove the brackets, break up the string by commas.
             * This gives us a vector of strings for each argument.
             * Iterate through, load each arugment into an internal representation.
             * Note that arguments are decalred, not processed here. Hence they are not arithmetic, and only  stored as strings.
             * */
            std::vector<std::string> comma_split_string;
            boost::split(comma_split_string, function_arguments_string, boost::is_any_of(","));
            for(std::vector<std::string>::iterator it = comma_split_string.begin(); it != comma_split_string.end(); ++it){
                FUNCTION_DEFINITION::function_arguments.push_back((*it));

                // inform the user as we load arguments.
                Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded function argument: " + (*it));
            }

            return true;            
            

            /**
             * 
             * 
             * Defensive programming - neither of these should ever happen
             * 
             **/
        } else {
            Logging::logErrorMessage("Assertion error - Failed to load function name. ");
            ::printErrorLocation(8, input_original);
            return false;
        }
    } else {
        Logging::logErrorMessage("Assertion error - Failed to parse function Token. ");
        ::printErrorLocation(0, input);
        return false;
    }
}


std::vector<std::shared_ptr<ThreeOpCode>> FUNCTION_DEFINITION::generatetoc(int starting_address){

    // All function mappiongs are handled here. We only need to jump into the function
    std::shared_ptr<int> x = ::addFunctionMapping(FUNCTION_DEFINITION::function_name, FUNCTION_DEFINITION::function_arguments, starting_address);
    
    return {

        // Handle the function jump
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::NO_OPERATION, std::string("GKA3F"))),
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode(x, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR,false)),
    };
}
#include "Tokens/CALL.h"

bool CALL::initaliseToken(std::string input){

    // Keep a backup of the original string for error messages.
    std::string input_original = input;
    // This should always pass - regex has checked this for us.
    if(input.substr(0,4) == "CALL"){
        // Rmeove the keyword - the token has been identified.
        input.erase(0,4);


        /**
         * This regex expression is two expressions, the first of which breaks down the name of a function at the start of the string.
         * The function name is extracted, and the argument string left.
         * 
         * 
         * Boost regex breaks this down into seperate regex matching tokens, accessible in an array.
         * The documentation for boost::Regex is essential here
         **/
        const char* target = input.c_str();
        boost::regex subroutine_name_regex("(^([A-Z][A-Z0-9]+))(.*)");
        boost::cmatch char_matches;

        // Parse control variables to the left of the equals sign.
        if (boost::regex_match(target, char_matches, subroutine_name_regex))
        {   
            // Set the function name to a member variable
            CALL::subroutine_name = char_matches[2];
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values,  "Loaded subroutine name " + subroutine_name);

            /***
             * 
             * Having extracted the function name, the arguments string is placed in the next value.
             * This block of code breaks each argument down.
             **/
            //  For clarity.
            std::string subroutine_arguments_string = char_matches[3];
            if(subroutine_arguments_string.back() == ')' && subroutine_arguments_string.front() == '('){        // Ensure that nothing else is attatched. This shouldn't trigger, and is a safety check
                subroutine_arguments_string.erase(0,1);         // Remove the opening bracket
                subroutine_arguments_string.pop_back();         // Remove the final bracket
                if(subroutine_arguments_string.length() == 0){      // if there are no arguments, we are finished.
                    return true;
                } 
                /**
                 * Split the string by commas, with no brackets, we should have a list of arguments in CSV format.
                 **/ 
                std::vector<std::string> comma_split_arguments;
                boost::split(comma_split_arguments, subroutine_arguments_string, boost::is_any_of(","));

                /**
                 * 
                 * Iterate through each arugment - passing it's value to the arithmetic parser and building up a member variable list.
                 * This is the list we'll used to generate symbol table entries later.
                 * 
                 **/
                int index = 0;      // Index is tracked for the user's sake - we can give an accurage picutre of which argument we are loading and in which order.s
                for(std::vector<std::string>::iterator it = comma_split_arguments.begin(); it != comma_split_arguments.end(); ++it){
                    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded function argument [" + std::to_string(index) + "] " + *it);
                    subroutine_arguments.push_back(::parseADString(*it));
                    index++;
                }

                return true;
            } else {

                /**
                 * 
                 * Assertation error - this shouldn't happen.
                 * 
                 **/
                Logging::logErrorMessage("Error parsing arguments for function " + subroutine_name);
                Logging::logErrorMessage("Function Argument String: " + subroutine_arguments_string);
                ::printErrorLocation(4+subroutine_name.size(), input_original);
            }
        } else {
            /**
             * This should never happen - if this triggers then the regex checks have failed.
             **/
            Logging::logErrorMessage("Assertation error - failed to parse CALL token.");
            ::printErrorLocation(0, input_original);
        }
    } else {
        Logging::logErrorMessage("Failed to parse values from CALL Token: { " + input + " }");
    }
    return false;
}

std::vector<std::shared_ptr<ThreeOpCode>> CALL::generatetoc(int starting_address){


    // declare our return variable
    std::vector<std::shared_ptr<ThreeOpCode> > toc_return;
    // This vector contains symbol table entries to each argument
    std::vector<std::shared_ptr<ST_ENTRY> > args;
    

    /**
     * We need to load each argument, construct their three op code string (an argument could be an arithmetic operation, i.e. HelloWORLD(5+5))
     *  Handle this, and then add the final value to the symbol table. 
     **/
    for(std::vector<std::unique_ptr<RDParseTreeNode> >::iterator it = subroutine_arguments.begin(); it != subroutine_arguments.end(); ++it){
        TOC_RETURN_VALUE ret_val = (*it)->generateThreeOPCode(starting_address);
        args.push_back(ret_val.call_value);
        toc_return.insert(toc_return.end(), ret_val.pre_string.begin(), ret_val.pre_string.end());
    }

    /**
     * once all arguments are mapped, call the symbol table.
     * **/
    SUBROUTINE_MAPPING_RETURN sub_return = ::getSubroutineMapping(subroutine_name, starting_address, args);
    Logging::logConditionalErrorMessage(!sub_return.result, "Error - failed to add function " + subroutine_name);

    /**
     * 
     * The symbol table injects return value code into our main program. include that here
     * This is mostly for moving values in and out of the function scope symbol table.
     **/
    toc_return.insert(toc_return.end(), sub_return.toc_inject.begin(), sub_return.toc_inject.end());
    
    return toc_return;
}
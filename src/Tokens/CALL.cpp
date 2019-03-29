#include "Tokens/CALL.h"

bool CALL::initaliseToken(std::string input){
    std::string input_original = input;
    if(input.substr(0,4) == "CALL"){
        input.erase(0,4);

        const char* target = input.c_str();
        boost::regex subroutine_name_regex("(^([A-Z][A-Z0-9]+))(.*)");
        boost::cmatch char_matches;

        // Parse control variables to the left of the equals sign.
        if (boost::regex_match(target, char_matches, subroutine_name_regex))
        {
            std::string function_name_string = char_matches[2];
            CALL::subroutine_name = function_name_string;
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values,  "Loaded subroutine name " + subroutine_name);

            std::string subroutine_arguments_string = char_matches[3];
            if(subroutine_arguments_string.back() == ')' && subroutine_arguments_string.front() == '('){
                subroutine_arguments_string.erase(0,1);
                subroutine_arguments_string.pop_back();
                if(subroutine_arguments_string.length() == 0){
                    return true;
                }

                std::vector<std::string> comma_split_arguments;
                boost::split(comma_split_arguments, subroutine_arguments_string, boost::is_any_of(","));

                int index = 0;
                for(std::vector<std::string>::iterator it = comma_split_arguments.begin(); it != comma_split_arguments.end(); ++it){
                    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded function argument [" + std::to_string(index) + "] " + *it);
                    subroutine_arguments.push_back(::parseADString(*it));
                    index++;
                }

                return true;
            } else {
                Logging::logErrorMessage("Error parsing arguments for function " + subroutine_name);
                Logging::logErrorMessage("Function Argument String: " + subroutine_arguments_string);
                ::printErrorLocation(4+subroutine_name.size(), input_original);
            }
        } else {
            Logging::logErrorMessage("Failed to parse subroutine name from CALL Statement.");
            ::printErrorLocation(0, input_original);
        }
    } else {
        Logging::logErrorMessage("Failed to parse values from CALL Token: { " + input + " }");
    }
    return false;
}

std::vector<std::shared_ptr<ThreeOpCode>> CALL::generatetoc(int starting_address){

    std::vector<std::shared_ptr<ThreeOpCode> > toc_return;
    std::vector<std::shared_ptr<ST_ENTRY> > args;
    for(std::vector<std::unique_ptr<RDParseTreeNode> >::iterator it = subroutine_arguments.begin(); it != subroutine_arguments.end(); ++it){
        TOC_RETURN_VALUE ret_val = (*it)->generateThreeOPCode();
        args.push_back(ret_val.call_value);
        toc_return.insert(toc_return.end(), ret_val.pre_string.begin(), ret_val.pre_string.end());
    }
    SUBROUTINE_MAPPING_RETURN sub_return = ::getSubroutineMapping(subroutine_name, starting_address, args);
    Logging::logConditionalErrorMessage(!sub_return.result, "Error - failed to add function " + subroutine_name);
    toc_return.insert(toc_return.end(), sub_return.toc_inject.begin(), sub_return.toc_inject.end());
    return toc_return;
}
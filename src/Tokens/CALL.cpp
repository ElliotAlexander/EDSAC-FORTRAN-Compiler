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
            if(Globals::dump_parsed_values){
                std::cout << StringConstants::INFO_TAG << "Loaded subroutine name " << subroutine_name << std::endl;
            }

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
                    if(Globals::dump_parsed_values){
                        std::cout << StringConstants::INFO_TAG << "Loaded function argument [" << index << "] " << *it << std::endl;
                    }
                    subroutine_arguments[index] = ::parseADString(*it);
                    index++;
                }
            } else {
                std::cerr << StringConstants::ERROR_TAG << "Error parsing arguments for function " << subroutine_name << std::endl;
                std::cerr << StringConstants::ERROR_TAG << "Function Argument String: " << subroutine_arguments_string << std::endl;
                ::printErrorLocation(4+subroutine_name.size(), input_original);
            }
        } else {
            std::cerr << StringConstants::ERROR_TAG << "Failed to parse subroutine name from CALL Statement." << std::endl;
            ::printErrorLocation(0, input_original);
        }
    } else {
        std::cerr << StringConstants::ERROR_TAG << "Failed to parse values from CALL Token: { " << input << " }" << std::endl;  
        return false;
    }
}

std::vector<TOC*> CALL::generatetoc(std::string input){
    return {};
}
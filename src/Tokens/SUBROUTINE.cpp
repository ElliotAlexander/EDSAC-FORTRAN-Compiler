#include "Tokens/SUBROUTINE.h"

bool SUBROUTINE::initaliseToken(std::string input){
    std::string input_original = input;
    if(input.substr(0, 10) == "SUBROUTINE"){
        input.erase(0,10);

        const char* target = input.c_str();
        boost::regex subroutine_name_regex("(^([A-Z]+))(.*)");
        boost::cmatch char_matches;

        // Parse control variables to the left of the equals sign.
        if (boost::regex_match(target, char_matches, subroutine_name_regex))
        {
            std::string name_string = char_matches[2];
            Logging::logInfoMessage("Loaded Subroutine Name: " + name_string);
            SUBROUTINE::subroutine_name = name_string;

            std::string function_arguments_string = char_matches[3];
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Function Arguments String: " + function_arguments_string);

            if(function_arguments_string.front() == '('){function_arguments_string.erase(0,1); }
            if(function_arguments_string.back() == ')'){function_arguments_string.pop_back(); }
            Logging::logConditionalInfoMessage(function_arguments_string.empty(), "Loaded no function arguments.");
            if(function_arguments_string.empty()) { return true; }
            
            std::vector<std::string> comma_split_string;
            boost::split(comma_split_string, function_arguments_string, boost::is_any_of(","));
            for(std::vector<std::string>::iterator it = comma_split_string.begin(); it != comma_split_string.end(); ++it){
                SUBROUTINE::subroutine_arguments.push_back((*it));
                Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded function argument: " + (*it));
            }

            return true;            
            
        } else {
            Logging::logErrorMessage("Failed to load function name. ");
            ::printErrorLocation(8, input_original);
            return false;
        }
    } else {
        Logging::logErrorMessage("Failed to parse function Token. ");
        ::printErrorLocation(0, input);
        return false;
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> SUBROUTINE::generatetoc(int starting_address){
    std::shared_ptr<int> x = ::addSubroutineMapping(SUBROUTINE::subroutine_name, SUBROUTINE::subroutine_arguments, starting_address);
    
    return {
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, std::string("K"))),
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode("3", THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)),
        std::shared_ptr<ThreeOpCode>(new ThreeOpCode(x, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR,true)),
    };
}
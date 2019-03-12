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
        std::string variable_name_temp = input.substr(0, found);
        if(variable_name_temp.length() < 1){
            Logging::logErrorMessage("Failed to parse variable name.");
            ::printErrorLocation(found-1, input);
        }


        // we need to handle a single character differently - using .substr on two chars will return nothing.
        std::string assignment_string_temp;
        
        if((found + 1 - input.length()) == 0) {
            assignment_string_temp = input.back();
        } else {
            assignment_string_temp = std::string((input.substr(found+1, input.length())));
        } 
        
        if(assignment_string_temp.length() < 1){
            Logging::logErrorMessage("Failed to parse assignment value.");
            ::printErrorLocation(found+1, input_backup);
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

std::vector<std::shared_ptr<ThreeOpCode>> ASSIGN::generatetoc(){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;

    TOC_RETURN_VALUE res = ASSIGN::assignment_value->generateThreeOPCode();
    pre_string.insert(pre_string.end(), res.pre_string.begin(), res.pre_string.end());




    std::shared_ptr<ST_ENTRY> add_result = addDeclaredVariable(ASSIGN::variable_name, std::to_string(res.call_value->base_memory_address), ST_ENTRY_TYPE::FLOAT_T);
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(add_result, THREE_OP_CODE_OPERATIONS::DATA_SET, false)));

    return pre_string;
}
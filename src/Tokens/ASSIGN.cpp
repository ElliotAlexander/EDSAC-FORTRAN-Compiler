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

        std::string assignment_string_temp = std::string((input.substr(found+1, input.length())));
    
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

std::vector<std::shared_ptr<ThreeOpCode>> ASSIGN::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;


    // Generate a temporary address for the value we'll be placing in $1
    TOC_RETURN_VALUE res = ASSIGN::assignment_value->generateThreeOPCode(starting_address);
    // Add this to our TOC.
    pre_string.insert(pre_string.end(), res.pre_string.begin(), res.pre_string.end());

	ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

    // Add our temporary value to the accumulator.
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(res.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    // Copy our temporary value to our new address.
    std::shared_ptr<ST_ENTRY> add_result = SymbolTableController::addDeclaredVariable(ASSIGN::variable_name, std::to_string(res.call_value->base_memory_address), ST_ENTRY_TYPE::FLOAT_T);

    // Add to TOC.
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(add_result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

    return pre_string;
}
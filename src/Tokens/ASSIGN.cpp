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
	TOC_RETURN_VALUE toc_res = assignment_value->generateThreeOPCode(starting_address);

    ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
    Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");


    ALL_ST_SEARCH_RESULT st_res = SymbolTableController::getVariable(ASSIGN::variable_name);
    pre_string.insert(pre_string.begin(), toc_res.pre_string.begin(), toc_res.pre_string.end());
    if(st_res.found){
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Remapping variable " + ASSIGN::variable_name);
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_res.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
		pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_res.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    } else {
        SymbolTableController::addLinkedVariable(toc_res.call_value, ASSIGN::variable_name);
    }

    return pre_string;


}
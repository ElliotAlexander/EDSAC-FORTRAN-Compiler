#include "Tokens/VAR_DECLR.h"

bool VAR_DECLR::initaliseToken(std::string input){

    std::vector<std::string> equals_split;
    boost::split(equals_split, input, boost::is_any_of("="));

    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Variable Declaration String " + input);

    VAR_DECLR::variable_name = equals_split[0];
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, std::string("Loaded Variable Name: " + variable_name));
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, std::string("Loaded Variable Assignment: " + equals_split[1]));
    Logging::logConditionalErrorMessage((equals_split[1] == equals_split[0]), std::string("Self Assignment - Assigning " + equals_split[0] + " to " + equals_split[1] + " isn't supported."));
    
    VAR_DECLR::right_hand_side_parsed = ::parseADString(equals_split[1]);    
    return true;

}

std::vector<std::shared_ptr<ThreeOpCode>> VAR_DECLR::generatetoc(int starting_address){
    
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
    TOC_RETURN_VALUE toc_res = VAR_DECLR::right_hand_side_parsed->generateThreeOPCode();
    pre_string.insert(pre_string.begin(), toc_res.pre_string.begin(), toc_res.pre_string.end());
    std::shared_ptr<ST_ENTRY> result = SymbolTableController::addDeclaredVariable(VAR_DECLR::variable_name, "", ST_ENTRY_TYPE::UNASSIGNED_T);

	ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

    // Clear the accumulator
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_res.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
    pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
    return pre_string;
} 
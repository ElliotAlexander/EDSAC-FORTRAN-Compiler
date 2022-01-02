#include "Tokens/GOTO.h"

bool GOTO::initaliseToken(std::string input){
    if(input.substr(0,4) == "GOTO"){

        // remove the keyword
        input = input.erase(0, 4);
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded GOTO String: " + input);

        // Everything else in the string should be an integer argument.
        // Regex should have ensured that only integers reach this stage, so we can call stoi safely.
        GOTO::goto_single_arg = stoi(input);
        return true;

    // Defensive prgrammming - this shouldn't happen
    } else {
        Logging::logErrorMessage("Assertion Error - Failed to parse GOTO Statement. ");
        return false;  
    }
}

std::vector<std::shared_ptr<ThreeOpCode>> GOTO::generatetoc(int starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
    ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");
    LineMapping::LineMappingReturn mapping = LineMapping::retrieveLineMapping(GOTO::goto_single_arg); 
    Logging::logConditionalErrorMessage(!mapping.result, "Warning - failed to load line mapping for " + std::to_string(GOTO::goto_single_arg));
    std::shared_ptr<int> goto_mapping = mapping.value;

    std::shared_ptr<ST_ENTRY> temp_int = SymbolTableController::addTemp(std::string("1"), ST_ENTRY_TYPE::INT_T);

        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
        
        // Make sure the accumulator is positive
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));

        // There's an edge case here if the index is zero
        // TODO be aware of this
		pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(goto_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
    
    return pre_string;
}
#include "Tokens/PRINT.h"

bool PRINT::initaliseToken(std::string input){
	Logging::logMessage("Initialised with " + input);
	if(input.substr(0,5) == "PRINT"){
		input = input.erase(0,5);
		PRINT::print_val = ::parseADString(input);
		Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded PRINT variable: " + input);
		return true;
	} else {
		Logging::logErrorMessage("Failed to load PRINT statement - couldn't find keyword.");
		return false;
	}
}	

std::vector<std::shared_ptr<ThreeOpCode>> PRINT::generatetoc(int starting_address){
	std::vector<std::shared_ptr<ThreeOpCode> > pre_string;

	TOC_RETURN_VALUE toc_ret = PRINT::print_val->generateThreeOPCode(starting_address);

    ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
    Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");


	std::shared_ptr<int> P6_mapping = Libs::getLibraryLineMapping("P6");

	std::shared_ptr<int> mapping = LineMapping::addTemporaryLineMapping(starting_address + 1 );

	pre_string.insert(pre_string.end(), toc_ret.pre_string.begin(), toc_ret.pre_string.end());

	// This instruction seems to be causing problems
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("", THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(mapping , THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(P6_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
	return pre_string;
}
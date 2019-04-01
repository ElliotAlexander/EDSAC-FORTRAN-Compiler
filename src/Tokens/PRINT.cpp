#include "Tokens/PRINT.h"

bool PRINT::initaliseToken(std::string input){
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
	pre_string.insert(pre_string.begin(), toc_ret.pre_string.begin(), toc_ret.pre_string.end());
	pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(toc_ret.call_value, THREE_OP_CODE_OPERATIONS::PRINT_SYMBOL, false)));
	return pre_string;
}
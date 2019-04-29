#include "Tokens/CONTINUE.h"

bool CONTINUE::initaliseToken(std::string input){
	Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Continue statement successfully.");
    return true;
}

std::vector<std::shared_ptr<ThreeOpCode>> CONTINUE::generatetoc(int starting_address){
    return {};
}
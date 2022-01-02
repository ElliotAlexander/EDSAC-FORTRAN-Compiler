#include "Tokens/CONTINUE.h"

/**
 * bool CONTINUE::initaliseToken(std::string input)
 * 
 * CONTINUE has no effect and no variables, so this class is basically a wrapper./
 **/ 
bool CONTINUE::initaliseToken(std::string input){
	Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded Continue statement successfully.");
    return true;
}

/**
 * Continue is implemented, but it's only functionality is as a line refernce. Hence, there is no three op code to be printed.
 **/ 
std::vector<std::shared_ptr<ThreeOpCode>> CONTINUE::generatetoc(int starting_address){
    return {};
}
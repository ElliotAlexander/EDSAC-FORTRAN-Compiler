#include "Tokens/FORMAT.h"

/**
 * 
 * bool FORMAT::initaliseToken(std::string input)
 * 
 * Format statements are NOT implemented.
 * 
 * This class serves as nothing more than a wrapper for an error message.
 **/ 

bool FORMAT::initaliseToken(std::string input){
    Logging::logErrorMessage("Format statements are not implemented!");
    return false;
}

// std::vector<std::shared_ptr<ThreeOpCode>> FORMAT::generatetoc(int starting_address){
// Not implemented - this returns nothing. 
std::vector<std::shared_ptr<ThreeOpCode>> FORMAT::generatetoc(int starting_address){
    return {};
}
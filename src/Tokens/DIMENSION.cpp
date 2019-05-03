#include "Tokens/DIMENSION.h"

/**
 * bool DIMENSION::initaliseToken(std::string input)
 *  
 * Dimension is not implemented, hence this class is a wrapper for an error message.
 * 
 **/ 
bool DIMENSION::initaliseToken(std::string input){
    Logging::logErrorMessage("Dimension Statements are not supported!");
    return true;
}

std::vector<std::shared_ptr<ThreeOpCode>> DIMENSION::generatetoc(int starting_address){
    return {};
}
#include "Tokens/RETURN.h"

bool RETURN::initaliseToken(std::string input){
    return true;
}

std::vector<std::shared_ptr<ThreeOpCode>> RETURN::generatetoc(int starting_address){
    ::exitFunction();
    Logging::logInfoMessage("Exiting function");
    return {};
}
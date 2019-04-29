#include "Tokens/REWIND.h"

bool REWIND::initaliseToken(std::string input){
    Logging::logErrorMessage("REWIND is not implemented on EDSAC!");
    return true;
}

std::vector<std::shared_ptr<ThreeOpCode>> REWIND::generatetoc(int starting_address){
    return {};
}
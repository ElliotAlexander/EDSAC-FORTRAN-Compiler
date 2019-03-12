#include "Utils.h"


bool lineIsComment(std::string line){
    if(line.length() > 0){
        return (line.at(0) == 'C' || line.at(0) == 'c' || line.at(0) == '!') ? true : false;
    } else { return false; }
}


bool printErrorLocation(int location, std::string input){
    Logging::logErrorMessage("Error location: \n" +  input);
    Logging::logErrorMessage(std::string(location -1, ' ') + "^");
    return true;
}



// TODO change the name on this.
std::string getEnumString(int i){
    switch (i) {
        case 0: 
            return "FUNCTION";
            break;
        case 1:
            return "PROGRAM";
            break;
        case 2: 
            return "SUBROUTINE";
            break;
        default:
            return "UNKNOWN";
    }
}

std::string stripWhitespaceString(std::string input){
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
    return input;
}

void print_header(){
    Logging::logMessage("\n\n===== EDSAC FORTRAN II Compiler  =====\n");
}

void print_footer(){
    Logging::logMessage("\n\n==== End of runtime  ====\n");; 
}

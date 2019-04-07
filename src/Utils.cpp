#include "Utils.h"


bool lineIsComment(std::string line){
    if(line.length() > 0){
        return (line.at(0) == 'C' || line.at(0) == 'c' || line.at(0) == '!') ? true : false;
    } else { return false; }
}


bool printErrorLocation(int location, std::string input){
    Logging::logErrorMessage("Error location: ");
    Logging::logErrorMessage(input);
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

void printTOCOutput(std::vector<std::shared_ptr<ThreeOpCode> > three_op_code_arr, int total_offset){
    if(Globals::dump_three_op_code){
        Logging::logMessage("\n\n:: Three Op Code Output :: \n\n");
        for(int index = 0; index < three_op_code_arr.size(); index++){
            Logging::logMessage(std::string("[" + std::to_string(index + total_offset - 1) + "] " + three_op_code_arr.at(index)->printToString()));
        }
        Logging::logMessage("\n --- end Three Op Code output --- \n");
    }
}
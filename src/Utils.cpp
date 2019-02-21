#include "Utils.h"


bool lineIsComment(std::string line){
    if(line.length() > 0){
        return (line.at(0) == 'C' || line.at(0) == 'c' || line.at(0) == '!') ? true : false;
    } else { return false; }
}


bool printErrorLocation(int location, std::string input){
    std::cerr << StringConstants::ERROR_TAG << "Error location: " << std::endl << input << std::endl;
    std::cerr << std::string(location -1, ' ') << "^" << std::endl;
    return true;
}


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
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    return input;
}

void print_header(){
    std::cout << "\n\n" << "===== " << "EDSAC FORTRAN II Compiler " << " =====" << "\n\n";
}

void print_footer(){
    std::cout << "\n\n" << "==== " << "End of runtime " << " ====" << "\n\n"; 
}

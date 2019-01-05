#include "Utils.h"


bool lineIsComment(std::string line){
    if(line.length() > 0){
        return (line.at(0) == 'C' || line.at(0) == 'c') ? true : false;
    } else { return false; }
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
    for(int i=0; i < input.length(); i++) { if(input[i] == ' ') { (input.erase(i,1)); } };
    return input;
}

void print_header(){
    std::cout << "\n\n" << "===== " << "EDSAC FORTRAN II Compiler " << " =====" << "\n\n";
}

void print_footer(){
    std::cout << "\n\n" << "==== " << "End of runtime " << " ====" << "\n\n"; 
}

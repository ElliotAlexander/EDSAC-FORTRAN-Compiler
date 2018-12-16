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

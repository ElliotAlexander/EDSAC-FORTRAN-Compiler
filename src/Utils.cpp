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
    Logging::logMessage("\n\n===== EDSAC FORTRAN II Compiler  =====\n");
}

void print_footer(){
    Logging::logMessage("\n\n==== End of runtime  ====\n");; 
}

unsigned long long getTotalSystemMemory()
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
}
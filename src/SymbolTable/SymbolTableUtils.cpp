#include "SymbolTable/SymbolTableUtils.h"

std::string symbolTableNameToString(int i){ 
    switch (i){
        case 0:
            return std::string("COMMON");
        case 1:
            return std::string("TEMP_VAR");
        case 2:
            return std::string("DECLARED_VAR");
        case 3:
            return std::string("UNDECLARED_VAR");
        default:
            return std::string("ERROR - UNKNOWN");
    }
}
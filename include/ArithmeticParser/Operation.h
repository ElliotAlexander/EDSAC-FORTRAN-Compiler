#ifndef __OPERATION_H_INCLUDED
#define __OPERATION_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "TOC.h"

enum OPS {
    SUBTRACT,
    ADD,
    MULTIPLY,
    DIVIDE,
    EXPONENT
};

class Operation : public TOC{

    OPS op;
    public:
        TOC* arg1;
        TOC* arg2;
        int final_var_index = -1;
        Operation(TOC* arg1_in, TOC* arg2_in, OPS operation);
        std::string toOPType(OPS e);
        std::string toValue();
        std::vector<std::string> toTOCStr(int &variable_index);
};

#endif
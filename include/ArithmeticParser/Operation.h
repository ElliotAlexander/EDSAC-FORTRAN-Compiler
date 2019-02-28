#ifndef __OPERATION_H_INCLUDED
#define __OPERATION_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "RDParseTreeNode.h"
#include "Constants.h"

enum OPS {
    SUBTRACT,
    ADD,
    MULTIPLY,
    DIVIDE,
    EXPONENT
};

class Operation : public RDParseTreeNode{

    OPS op;
    public:
        RDParseTreeNode* arg1;
        RDParseTreeNode* arg2;
        int final_var_index = -1;
        Operation(RDParseTreeNode* arg1_in, RDParseTreeNode* arg2_in, OPS operation);
        std::string toOPType(OPS e);
        std::string toValue();
        std::vector<std::string> toTOCStr(int &variable_index);
        virtual ~Operation() {};
};

#endif
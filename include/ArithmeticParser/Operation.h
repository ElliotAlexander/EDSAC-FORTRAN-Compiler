#ifndef __OPERATION_H_INCLUDED
#define __OPERATION_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "RDParseTreeNode.h"
#include "Constants.h"
#include "SymbolTable/STController.h"
#include <memory>

enum OPS {
    SUBTRACT,
    ADD,
    MULTIPLY,
    DIVIDE,
    EXPONENT
};

class Operation : public RDParseTreeNode{
    public:
        OPS op;
        RDParseTreeNode* arg1;
        RDParseTreeNode* arg2;
        Operation(RDParseTreeNode* arg1_in, RDParseTreeNode* arg2_in, OPS operation);
        std::string toOPType(OPS e);
        TOC_RETURN_VALUE generateThreeOPCode();
        virtual ~Operation() {};
};

#endif
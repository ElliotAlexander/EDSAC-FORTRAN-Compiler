#ifndef __OPERATION_H_INCLUDED
#define __OPERATION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "../TOC.h"

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
        Operation(TOC* arg1_in, TOC* arg2_in, OPS operation){
            tt = TOC_TYPES::OPERATION_E;
            arg1 = arg1_in;
            arg2 = arg2_in;
            op = operation;
        };


        std::string toOPType(OPS e){
            switch (e){
                case SUBTRACT:
                    return "-";
                case ADD:
                    return "+";
                case MULTIPLY:
                    return "*";
                case DIVIDE:
                    return "/";
                case EXPONENT:
                    return "^";
                default:
                    return "[Operation Error!]";
            }
        }

        std::string toTOCStr(){
            return arg1->toTOCStr() + toOPType(op) + arg2->toTOCStr();
        }
};

#endif
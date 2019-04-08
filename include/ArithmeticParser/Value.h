#ifndef __VALUE_H_INCLUDED
#define __VALUE_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "RDParseTreeNode.h"
#include <math.h>
#include "SymbolTable/STController.h"
#include "Logging.h"
#include <memory>

template <class T> class Value : public RDParseTreeNode {
    public:
        T argument;
        Value(T arg) {
            tt = TOC_TYPES::VALUE_E;
            argument = arg;
            bool is_int;
            if (ceil(arg) == arg){
                st_entry = SymbolTableController::addTemp(std::to_string(arg), ST_ENTRY_TYPE::INT_T);
            } else {
                st_entry = SymbolTableController::addTemp(std::to_string(arg), ST_ENTRY_TYPE::FLOAT_T);
            }
        }
        TOC_RETURN_VALUE generateThreeOPCode(int &starting_address) {
            return {{}, st_entry};   
        }
        virtual ~Value() {}
};

#endif
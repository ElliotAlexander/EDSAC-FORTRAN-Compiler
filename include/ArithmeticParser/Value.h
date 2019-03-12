#ifndef __VALUE_H_INCLUDED
#define __VALUE_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "RDParseTreeNode.h"
#include <math.h>
#include "SymbolTable/STController.h"
#include <memory>

template <class T> class Value : public RDParseTreeNode {
    public:
        T argument;
        Value(T arg) {
            tt = TOC_TYPES::VALUE_E;
            argument = arg;
            bool is_int;
            if (ceil(arg) == arg){
                st_entry = ::addTemp(std::to_string(arg), ST_ENTRY_TYPE::INT_T);
            } else {
                st_entry = ::addTemp(std::to_string(arg), ST_ENTRY_TYPE::FLOAT_T);
            }
        }
        TOC_RETURN_VALUE generateThreeOPCode() {
            return {};
            //return { { std::string("ASSIGN " + std::to_string(st_entry->base_memory_address) + " to " + st_entry->value)}, st_entry };
        }
        virtual ~Value() {}
    private:
        int assigned_variable;
};

#endif
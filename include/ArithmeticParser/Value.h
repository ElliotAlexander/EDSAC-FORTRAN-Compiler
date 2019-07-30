#ifndef __VALUE_H_INCLUDED
#define __VALUE_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
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
            st_entry = SymbolTableController::addTemp(std::to_string(arg), getType());
        }

        ST_ENTRY_TYPE getType() override {
            return std::is_floating_point<T>::value ? ST_ENTRY_TYPE::FLOAT_T : ST_ENTRY_TYPE::INT_T;
        }

        TOC_RETURN_VALUE generateThreeOPCode(int &starting_address) override {
            return {{}, st_entry};   
        }

        std::string toString() override {
            return "(" + std::to_string(argument) + (st_entry->type == ST_ENTRY_TYPE::INT_T? "I":"F") + ")";
        }

        virtual ~Value() {}
};

#endif
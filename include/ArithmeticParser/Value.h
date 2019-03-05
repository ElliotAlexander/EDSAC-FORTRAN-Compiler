#ifndef __VALUE_H_INCLUDED
#define __VALUE_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "RDParseTreeNode.h"

template <class T> class Value : public RDParseTreeNode {
    public:
        T argument;
        Value(T arg) {
            tt = TOC_TYPES::VALUE_E;
            argument = arg;
        }

        TOC_RETURN_VALUE generateThreeOPCode(int &variable_index) {
            return {std::vector<std::string>(), std::to_string(argument)};
        };
        virtual ~Value() {}
    private:
        int assigned_variable;
};

#endif
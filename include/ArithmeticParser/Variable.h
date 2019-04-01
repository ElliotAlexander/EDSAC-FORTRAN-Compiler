#ifndef __VARIABLE_T_H_INCLUDED
#define __VARIABLE_T_H_INCLUDED

#include <string>
#include <vector>
#include <stdio.h>
#include <map>
#include <memory>

#include "Logging.h"
#include "SymbolTable/STController.h"
#include "RDParseTreeNode.h"
#include "ThreeOpCode/ThreeOpCode.h"


    class Variable : public RDParseTreeNode {
        public:
            std::string name;
            Variable(std::string name_in);
            TOC_RETURN_VALUE generateThreeOPCode(int &starting_address);
            virtual ~Variable() {}
    };

#endif
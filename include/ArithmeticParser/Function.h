#ifndef __FUNCTION_H_INCLUDED
#define __FUNCTION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "RDParseTreeNode.h"
#include "ProgramStructure/FunctionMapping.h"


    class Function : public RDParseTreeNode {
        public:
            std::vector<RDParseTreeNode*> function_arguments;
            std::string function_name;
            
            Function(std::vector<RDParseTreeNode*> args_in, std::string function_name_in);
            TOC_RETURN_VALUE generateThreeOPCode(int &starting_address);
            virtual ~Function() {};
    };
    
#endif
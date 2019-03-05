#ifndef __FUNCTION_H_INCLUDED
#define __FUNCTION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "RDParseTreeNode.h"


    class Function : public RDParseTreeNode {
        private:
            std::string function_call;;
        public:
            std::vector<RDParseTreeNode*> args;
            std::string function_name;
            Function(std::vector<RDParseTreeNode*> args_in, std::string function_name_in);
            TOC_RETURN_VALUE generateThreeOPCode(int &variable_index);
            virtual ~Function() {};
    };
    
#endif
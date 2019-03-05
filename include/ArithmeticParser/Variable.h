#ifndef __VARIABLE_T_H_INCLUDED
#define __VARIABLE_T_H_INCLUDED

#include <string>
#include <vector>
#include <stdio.h>
#include <map>
#include "RDParseTreeNode.h"

#include "Logging.h"


    class Variable : public RDParseTreeNode {
        public:
            char *name;
            int memory_mapping;
            bool memory_mapped;
            Variable(char* name_in);
            TOC_RETURN_VALUE generateThreeOPCode(int &variable_index);
            virtual ~Variable() {}
    };

#endif
#ifndef __TOC_H_INCLUDED
#define __TOC_H_INCLUDED


#include <string>
#include <vector>
#include <memory>
#include "SymbolTable/STController.h"
#include "ThreeOpCode/ThreeOpCode.h"

    enum TOC_TYPES { 
        VARIABLE_E, 
        VALUE_E,
        OPERATION_E,
        FUNCTION_E
    };

    
    struct TOC_RETURN_VALUE {
        // Pre string represents all the things we need to do in order to setup the initial variable.
        std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
        // The final variable value.
        std::shared_ptr<ST_ENTRY> call_value;
    };

    class RDParseTreeNode{
        public:
            std::shared_ptr<ST_ENTRY> st_entry;
            TOC_TYPES tt;   
            virtual TOC_RETURN_VALUE generateThreeOPCode(int &starting_address) = 0;
            virtual std::string toString() = 0;
            virtual ~RDParseTreeNode() {};
    };

#endif
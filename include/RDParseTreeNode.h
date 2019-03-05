#ifndef __TOC_H_INCLUDED
#define __TOC_H_INCLUDED


#include <string>
#include <vector>

    enum TOC_TYPES { 
        VARIABLE_E, 
        VALUE_E,
        OPERATION_E,
        FUNCTION_E
    };

    
    struct TOC_RETURN_VALUE {
        // Pre string represents all the things we need to do in order to setup the initial variable.
        std::vector<std::string> pre_string;
        // The final variable value.
        std::string call_value;
    };

    class RDParseTreeNode{
        public:
            TOC_TYPES tt;   
            virtual TOC_RETURN_VALUE generateThreeOPCode(int &variable_index) = 0;
            virtual ~RDParseTreeNode() {};
    };

#endif
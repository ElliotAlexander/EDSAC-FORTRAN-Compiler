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

    
    class RDParseTreeNode{
        public:
            TOC_TYPES tt;   
            virtual std::vector<std::string> toTOCStr(int &variable_index) = 0;
            virtual std::string toValue() = 0;
            virtual ~RDParseTreeNode() {};
    };

#endif
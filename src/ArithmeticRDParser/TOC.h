#ifndef __TOC_H_INCLUDED
#define __TOC_H_INCLUDED


#include <string>

    enum TOC_TYPES { 
        VARIABLE_E, 
        VALUE_E,
        OPERATION_E
    };
    
    class TOC{
        public:
            TOC_TYPES tt;   
            virtual std::string toTOCStr() = 0;
    };

#endif
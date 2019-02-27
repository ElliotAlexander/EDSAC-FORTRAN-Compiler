#ifndef _WRAPPER_T_H_INCLUDED
#define _WRAPPER_T_H_INCLUDED

#include <string>
#include <vector>
#include <stdio.h>
#include "TOC.h"


/**
 * 
 * 
 * Wrapper exists to maintain a reference to return values from bison
 * TODO - Understand this better, passing the stack value into a new class copies it (I assume?)
 * Without this class, we don't have a reference once control flow leaves bison.
**/

    class Wrapper : public TOC {
        public:
            TOC* in_save;
            Wrapper(TOC* in);
            std::vector<std::string> toTOCStr(int &variable_index);
            std::string toValue();
            virtual ~Wrapper() {}
    };

#endif
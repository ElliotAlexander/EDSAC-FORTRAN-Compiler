#ifndef __VARIABLE_T_H_INCLUDED
#define __VARIABLE_T_H_INCLUDED

#include <string>
#include <vector>
#include <stdio.h>
#include "TOC.h"


    class Variable : public TOC {
        public:
            char *name;
            Variable(char* name_in);
            std::vector<std::string> toTOCStr(int &variable_index);
            std::string toValue();
            virtual ~Variable() {}
    };

#endif
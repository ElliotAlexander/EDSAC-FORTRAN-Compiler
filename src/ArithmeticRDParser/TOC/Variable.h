#ifndef __VARIABLE_T_H_INCLUDED
#define __VARIABLE_T_H_INCLUDED

#include <string>
#include <vector>
#include <stdio.h>
#include "../TOC.h"


    class Variable : public TOC {
        public:
            char *name;
            Variable(char* name_in){
                tt = TOC_TYPES::VARIABLE_E;
                name = name_in;
            }
            std::vector<std::string> toTOCStr(int &variable_index){
                std::vector<std::string> x;
                x.push_back(std::string("$" + std::to_string(variable_index) + "=" + name));
                variable_index++;
                return x;
            }

            std::string toValue(){
                std::string x = name;
                return x;
            }
    };

#endif
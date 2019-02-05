#ifndef __VALUE_H_INCLUDED
#define __VALUE_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "../TOC.h"



    template <class T> class Value : public TOC {
        public:
            T argument;
            Value(T arg){
                tt = TOC_TYPES::VALUE_E;
                argument = arg;
            }


            std::string toValue(){
                return std::to_string(argument);
            }
    
            std::vector<std::string> toTOCStr(int &variable_index){
                std::vector<std::string> x = {"$" + std::to_string(variable_index) + "=" + std::to_string(argument)};
                variable_index++;
                return x;
            }
    };
    
    #endif
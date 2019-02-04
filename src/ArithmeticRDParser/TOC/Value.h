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
    
            std::string toTOCStr(){
                std::string x = std::to_string(argument);
                return x;
            }
    };
    
    #endif
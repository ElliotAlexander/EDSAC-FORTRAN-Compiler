#ifndef __FUNCTION_H_INCLUDED
#define __FUNCTION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "TOC.h"



    class Function : public TOC {
        private:
            std::string function_call = "";
        public:
            std::vector<TOC*> args;
            std::string function_name;
            Function(std::vector<TOC*> args_in, std::string function_name_in);
            std::string toValue();
            std::vector<std::string> toTOCStr(int &variable_index);
            virtual ~Function() {};
    };
    
#endif
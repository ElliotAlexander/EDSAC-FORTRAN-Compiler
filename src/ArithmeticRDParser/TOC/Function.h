#ifndef __FUNCTION_H_INCLUDED
#define __FUNCTION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "../TOC.h"



    class Function : public TOC {
        public:
            std::vector<TOC*> args;
            std::string function_name;
            Function(std::vector<TOC*> args_in, std::string function_name_in){
                tt = TOC_TYPES::FUNCTION_E;
                args = args_in;
                function_name = function_name_in;
            }


            std::string toValue(){
                return "Not implemented";
            }
    
            std::vector<std::string> toTOCStr(int &variable_index){
                int arg_vars[args.size()];
                int index = 0;


                std::vector<std::string> return_arr;
                for(std::vector<TOC*>::iterator it = args.begin(); it != args.end(); ++it) {
                    std::vector<std::string> tmp_return = (*it)->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), tmp_return.begin(), tmp_return.end());
                    arg_vars[index] = variable_index-1;
                    index++; 
                }

                std::string func_call = function_name + "(";

                for(const int &text : arg_vars) {
                    func_call.append(std::to_string(text));
                    if(text == arg_vars[index-1]){
                        func_call.append(")");
                    } else {
                        func_call.append(",");
                    }
                }

                return_arr.push_back(func_call);
                return return_arr;
            }
    };
    
    #endif
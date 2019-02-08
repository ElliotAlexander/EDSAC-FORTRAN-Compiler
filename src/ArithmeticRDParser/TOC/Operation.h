#ifndef __OPERATION_H_INCLUDED
#define __OPERATION_H_INCLUDED

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "../TOC.h"

enum OPS {
    SUBTRACT,
    ADD,
    MULTIPLY,
    DIVIDE,
    EXPONENT
};

class Operation : public TOC{

    OPS op;
    public:
        TOC* arg1;
        TOC* arg2;
        int final_var_index = -1;
        Operation(TOC* arg1_in, TOC* arg2_in, OPS operation){
            tt = TOC_TYPES::OPERATION_E;
            arg1 = arg1_in;
            arg2 = arg2_in;
            op = operation;
        };


        std::string toOPType(OPS e){
            switch (e){
                case SUBTRACT:
                    return "-";
                case ADD:
                    return "+";
                case MULTIPLY:
                    return "*";
                case DIVIDE:
                    return "/";
                case EXPONENT:
                    return "^";
                default:
                    return "[Operation Error!]";
            }
        }

        std::string toValue(){
            return "$" + std::to_string(final_var_index);
        }

        std::vector<std::string> toTOCStr(int &variable_index){
            std::vector<std::string> return_arr;
            if(arg1->tt == TOC_TYPES::OPERATION_E || arg2->tt == TOC_TYPES::OPERATION_E){

                if(arg1->tt == TOC_TYPES::OPERATION_E && arg2->tt == TOC_TYPES::OPERATION_E){
                    std::vector<std::string> x = arg1->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), x.begin(), x.end());                                        
                                        
                    std::vector<std::string> y = arg2->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), y.begin(), y.end());
    
                    return_arr.push_back("$" + std::to_string(variable_index) + std::string("=$") + std::to_string(variable_index-2) + toOPType(op) + std::string("$") + std::to_string(variable_index-1));
                } else if(arg1->tt == TOC_TYPES::OPERATION_E){
                    std::vector<std::string> x = arg1->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), x.begin(), x.end());
                    return_arr.push_back("$" + std::to_string(variable_index) + std::string("=$") + std::to_string(variable_index-1) + toOPType(op) + arg2->toValue());
                } else if(arg2->tt == TOC_TYPES::OPERATION_E){
                    std::vector<std::string> x = arg2->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), x.begin(), x.end());
                    return_arr.push_back("$" + std::to_string(variable_index) + std::string("=$") + std::to_string(variable_index-1) + toOPType(op) + arg1->toValue());
                }                    
                final_var_index = variable_index;
                variable_index++;
                return return_arr;
            } else if ( arg1->tt == TOC_TYPES::FUNCTION_E || arg2->tt == TOC_TYPES::FUNCTION_E) {
                if(arg1->tt == TOC_TYPES::FUNCTION_E && arg2->tt == TOC_TYPES::FUNCTION_E) {
                } else if(arg1->tt == TOC_TYPES::FUNCTION_E){
                    std::vector<std::string> pre_string = arg1->toTOCStr(variable_index);
                    // Function call is already added.
                    return_arr.insert(return_arr.end(), pre_string.begin(), pre_string.end());
                    return_arr.pop_back();
                    return_arr.push_back("$" + std::to_string(variable_index) + std::string("=") + arg2->toValue() + toOPType(op) + arg1->toValue());
                } else if(arg2->tt == TOC_TYPES::FUNCTION_E){
                    std::vector<std::string> pre_string = arg2->toTOCStr(variable_index);
                    // Function call is already added.
                    return_arr.insert(return_arr.end(), pre_string.begin(), pre_string.end());
                    return_arr.pop_back();
                    return_arr.push_back("$" + std::to_string(variable_index) + std::string("=") + arg1->toValue() + toOPType(op) + arg2->toValue());
                }
                return return_arr;
            } else {
                return_arr.push_back("$" + std::to_string(variable_index) + "=" + arg1->toValue());
                return_arr.push_back("$" + std::to_string(variable_index+1) + "=" + arg2->toValue());
                return_arr.push_back("$" + std::to_string(variable_index+2) + "=$" + std::to_string(variable_index) + toOPType(op) + "$" + std::to_string(variable_index+1));
                final_var_index = variable_index + 2;
                variable_index = variable_index + 3;
                return return_arr;
            }
        }
};

#endif
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
            return "$1" + toOPType(op) + "$2";
        }

        std::vector<std::string> toTOCStr(int &variable_index){
            std::vector<std::string> return_arr;
            if(arg1->tt == TOC_TYPES::OPERATION_E || arg2->tt == TOC_TYPES::OPERATION_E){

                if(arg1->tt == TOC_TYPES::OPERATION_E && arg2->tt == TOC_TYPES::OPERATION_E){
                    std::vector<std::string> x = arg1->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), x.begin(), x.end());                                        
                                        
                    std::vector<std::string> y = arg2->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), y.begin(), y.end());

                    return_arr.push_back("$" + std::to_string(variable_index) + std::string("=$") + std::to_string(variable_index) + toOPType(op) + std::string("$") + std::to_string(variable_index-1));
                    return return_arr;
                }


                if(arg1->tt == TOC_TYPES::OPERATION_E){
                    int variable_index_og = variable_index;
                    std::vector<std::string> x = arg1->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), x.begin(), x.end());
                    return_arr.push_back("$" + std::to_string(variable_index+1) + std::string("=$") + std::to_string(variable_index) + toOPType(op) + arg2->toValue());
                    variable_index++;
                } 


                if(arg2->tt == TOC_TYPES::OPERATION_E){
                    int variable_index_og = variable_index;
                    std::vector<std::string> x = arg2->toTOCStr(variable_index);
                    return_arr.insert(return_arr.end(), x.begin(), x.end());
                    return_arr.push_back("$" + std::to_string(variable_index+1) + std::string("=$") + std::to_string(variable_index) + toOPType(op) + arg1->toValue());
                    variable_index++;
                }
                return return_arr;
            } else {
                return_arr.push_back("$" + std::to_string(variable_index) + "=" + arg1->toValue());
                return_arr.push_back("$" + std::to_string(variable_index+1) + "=" + arg2->toValue());
                return_arr.push_back("$" + std::to_string(variable_index+2) + "=$" + std::to_string(variable_index) + toOPType(op) + "$" + std::to_string(variable_index+1));
                variable_index = variable_index + 2;
                return return_arr;
            }
        }
};

#endif
#ifndef __FUNCTION_H_INCLUDED
#define __FUNCTION_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "../TOC.h"



    class Function : public TOC {
        private:
            std::string function_call = "";
        public:
            std::vector<TOC*> args;
            std::string function_name;

            Function(std::vector<TOC*> args_in, std::string function_name_in){
                tt = TOC_TYPES::FUNCTION_E;
                args = args_in;
                function_name = function_name_in;
            }


            std::string toValue(){
                return function_call;
            }
    
            std::vector<std::string> toTOCStr(int &variable_index){
                int index = 0;
                std::vector<TOC*> arg_list;


                // Prestring represents operations + variable setup for function calls.
                std::vector<std::string> pre_string;
                
                for(std::vector<TOC*>::iterator it = args.begin(); it != args.end(); ++it) {
                    // Iterate through argument list.

                    // We need to build a pre-string for Operations and other functiosn.
                    // This might involve setting variables, or completing operations.
                    if((*it)->tt == TOC_TYPES::OPERATION_E || (*it)->tt == TOC_TYPES::FUNCTION_E){
                        if((*it)->tt == TOC_TYPES::OPERATION_E){
                            std::vector<std::string> op_pre_string = (*it)->toTOCStr(variable_index);
                            pre_string.insert(pre_string.end(), op_pre_string.begin(), op_pre_string.end());
                            arg_list.push_back(*it);
                        } else if((*it)->tt == TOC_TYPES::FUNCTION_E){
                            std::vector<std::string> op_pre_string = (*it)->toTOCStr(variable_index);
                            pre_string.insert(pre_string.end(), op_pre_string.begin(), op_pre_string.end());

                            // Remove the final element (i.e. the function call) for functions used as operations.
                            pre_string.pop_back();
                            arg_list.push_back(*it);
                        }
                    } else {
                        arg_list.push_back((*it));
                    }
                }


                // Setup our final function call.
                // Note that this must be the final thing outputted, preceded by the pre-string.
                std::string func_call = function_name + "(";


                /**
                 *  Build output string.
                 *  <FUNCTION_NAME> <PAREN> <ARGS> <COMMA>? <ARGS>? <PAREN>
                 */ 
                if(arg_list.begin() == arg_list.end()){
                    func_call.append(std::string(")"));
                } else {
                    // Iterate through TOC representations of reach argument. 
                    // Iterate backwards - FIFO
                    for (std::vector<TOC*>::reverse_iterator it = arg_list.rbegin();  it != arg_list.rend(); ++it ) {
                    //for (std::vector<TOC*>::iterator it = arg_list.begin(); it != arg_list.end(); ++it) {
                        /** Append value to output string.
                        Note that functions and operations will print their 'final_var_index' - i.e.
                        Setup will be appended to pre-string, for example:
                        5+5 as an argument will be interpreted as:
                        
                        Prestring:
                            $0 = 5
                            $1 = 5
                            $2 = 5 + 5 
                            <final_var_index = 2>

                        Output string:
                            $2

                        **/
                        func_call.append((*it)->toValue());


                        // If we're at the end of the list, print a closing parenthesis.
                        // If we're not at the end of the list, print a comma.
                        if(it+1 == arg_list.rend()){
                            func_call.append(std::string(")"));
                        } else {
                            func_call.append(std::string(","));
                        }
                    }
                }

                function_call = func_call;

                // Add our final output string to the pre-string.
                pre_string.push_back(func_call);

                // return combined string.
                return pre_string;
            }
    };
    
    #endif
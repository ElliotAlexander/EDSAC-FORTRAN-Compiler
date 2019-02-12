#include "Tokens/ARITH_FUNCTION.h"


bool ARITH_FUNCTION::initaliseToken(std::string input){
    std::string input_original = input;

    ARITH_FUNCTION::function_name = input.substr(0, input.find('('));

    bool in_args = 0;
    std::string variable_list;
    for(char &c: input){
        if(in_args == 0 && c == '('){
            in_args = 1;
        } else if(in_args == 1 && c == ')'){
            break;
        } else if(in_args){
            variable_list.push_back(c);
        } 
    }


    boost::split(ARITH_FUNCTION::function_arguments, variable_list, boost::is_any_of(","));
    //std::string expression = input_original.substr(input_original.find('='), input_original.length() -1);

    if(Globals::dump_parsed_values){
        std::cout << StringConstants::INFO_TAG << "Loaded function name: " << ARITH_FUNCTION::function_name << std::endl;
        for(std::vector<std::string>::iterator it = ARITH_FUNCTION::function_arguments.begin(); it != ARITH_FUNCTION::function_arguments.end(); it++){
            std::cout << StringConstants::INFO_TAG << "Loaded function argument: " << *it << std::endl;
        }
    }
}

std::vector<TOC*> ARITH_FUNCTION::generatetoc(std::string input){
    return {};
}
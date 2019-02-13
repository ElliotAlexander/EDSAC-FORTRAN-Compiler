#include "Tokens/ARITH_FUNCTION.h"

ARITH_FUNCTION::ARITH_FUNCTION(){
    std::string function_name;
    std::vector<TOC*> function_arguments;
}

bool ARITH_FUNCTION::initaliseToken(std::string input){

    std::vector<std::string> equals_split;
    boost::split(equals_split, input, boost::is_any_of("="));
    if(equals_split.size() > 2){
        // TODO
    }

    bool in_args = 0;
    std::string variable_list = "";
    std::string function_name_temp;
    for(std::string::size_type i = 0; i < equals_split.at(0).size(); i++) {
        if(in_args == 0 && equals_split.at(0)[i] == '('){
            in_args = 1;
        } else if(in_args == 1 && equals_split.at(0)[i] == ')'){
            break;
        } else if(in_args){
            variable_list.push_back(equals_split.at(0)[i]);
        } else if(!in_args){
            function_name_temp.push_back(equals_split.at(0)[i]);
        }
    }
    

    ARITH_FUNCTION::function_name = function_name_temp;
    std::vector<std::string> var_list_temp;
    boost::split(var_list_temp, variable_list, boost::is_any_of(","));

    for(std::vector<std::string>::iterator it = var_list_temp.begin(); it != var_list_temp.end(); ++it){
        TOC* x = ::parseADString(*it);
        ARITH_FUNCTION::function_arguments.push_back(x);
        if(Globals::dump_parsed_values){
            std::cout << StringConstants::INFO_TAG << "Function argument : " << *it << std::endl;
        }
    }




    std::string rhs_string;
    bool rhs = 0;
    for(std::string::size_type i = 0; i < input.size(); ++i) {
        if(input[i] == '='){
            rhs = 1;
        } else if(rhs){
            rhs_string.push_back(input[i]);
        }
    }


    if(Globals::dump_parsed_values){
        std::cout << StringConstants::INFO_TAG << "Function name: " << ARITH_FUNCTION::function_name << std::endl;
        std::cout << StringConstants::INFO_TAG << "Right hand side " << rhs_string << std::endl;
    }
    
}

std::vector<TOC*> ARITH_FUNCTION::generatetoc(std::string input){
    return {};
}
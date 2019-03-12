#include "Tokens/ARITH_FUNCTION.h"

ARITH_FUNCTION::ARITH_FUNCTION(){
    std::string function_name; 
    RDParseTreeNode* function_resolution;
    std::vector<RDParseTreeNode*> function_arguments;
}

bool ARITH_FUNCTION::initaliseToken(std::string input){

    std::vector<std::string> equals_split;
    boost::split(equals_split, input, boost::is_any_of("="));
    Logging::logConditionalErrorMessage((equals_split.size() > 2), "Syntax Error - found multiple equals symbols in Arithmetic Statement.");

    bool in_args = 0;
    std::string variable_list, function_name_temp;
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

    if(var_list_temp.size() == 0){
        Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Loaded zero command arguments");
    } else {
        for(std::vector<std::string>::iterator it = var_list_temp.begin(); it != var_list_temp.end(); ++it){
            ARITH_FUNCTION::function_arguments.push_back(::parseADString(*it));
            Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Function argument : " + *it);
        }
    }

    ARITH_FUNCTION::function_resolution = std::unique_ptr<RDParseTreeNode>(::parseADString(equals_split[1]));
    Logging::logConditionalErrorMessage((equals_split[1].length() == 0), "Failed to load right hand side string, length was zero.");
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Function name: " + ARITH_FUNCTION::function_name);
    Logging::logConditionalInfoMessage(Globals::dump_parsed_values, "Right hand side " + equals_split[1]);
    return true;
    
}

std::vector<std::shared_ptr<ThreeOpCode>> ARITH_FUNCTION::generatetoc(){
	return {};
}
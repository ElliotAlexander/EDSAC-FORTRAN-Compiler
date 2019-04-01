#include "ArithmeticParser/Function.h"

Function::Function(std::vector<RDParseTreeNode *> args_in, std::string function_name_in) : 
    function_arguments(args_in), 
    function_name(function_name_in.substr(0, function_name_in.find_first_of('(')))
{
    // TODO implement arguments
    Logging::logInfoMessage(function_name);
    Logging::logInfoMessage(std::to_string(args_in.size()));
    tt = TOC_TYPES::FUNCTION_E;
}

TOC_RETURN_VALUE Function::generateThreeOPCode(int &starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > return_string;
    std::vector<std::shared_ptr<ST_ENTRY> > arguments;
    for(std::vector<RDParseTreeNode*>::iterator it = function_arguments.begin(); it != function_arguments.end(); ++it)
    { 
        TOC_RETURN_VALUE toc_res = (*it)->generateThreeOPCode(starting_address);
        return_string.insert(return_string.end(), toc_res.pre_string.begin(), toc_res.pre_string.end());
        arguments.push_back(toc_res.call_value);
    }


    ARITH_FUNCTION_MAPPING_RETURN function_mapping = ::getArithmeticFunctionMapping(function_name, arguments);
    if(function_mapping.found){
        return_string.insert(return_string.end(), function_mapping.function_body.begin(), function_mapping.function_body.end());
        starting_address += return_string.size();
        return {return_string, function_mapping.return_val};
    } else {

        // TODO bring both funciton mappings in line with each other
        FUNCTION_MAPPING_RETURN function_mapping = ::getFunctionMapping(function_name, arguments, starting_address);
        if(function_mapping.result){
            return_string.insert(return_string.end(), function_mapping.toc_inject.begin(), function_mapping.toc_inject.end());
            starting_address += return_string.size();
            return {return_string, function_mapping.return_val };
        } else {
            Logging::logErrorMessage("Function " + function_name + " not found. Exiting Arithmetic Parser unsuccessfully.");
            return {};
        }
    }
}
#include "ArithmeticParser/Function.h"

Function::Function(std::vector<RDParseTreeNode *> args_in, std::string function_name_in) : function_arguments(args_in), function_name(function_name_in)
{
    // TODO implement arguments
    Logging::logInfoMessage(function_name);
    tt = TOC_TYPES::FUNCTION_E;
}

TOC_RETURN_VALUE Function::generateThreeOPCode(){
    std::vector<std::shared_ptr<ThreeOpCode> > return_string;
    std::vector<std::shared_ptr<ST_ENTRY> > arguments;
    for(std::vector<RDParseTreeNode*>::iterator it = function_arguments.begin(); it != function_arguments.end(); ++it)
    { 
        TOC_RETURN_VALUE toc_res = (*it)->generateThreeOPCode();
        return_string.insert(return_string.end(), toc_res.pre_string.begin(), toc_res.pre_string.end());
        arguments.push_back(toc_res.call_value);
    }


    FUNCTION_MAPPING_RETURN function_mapping = ::getArithmeticFunctionMapping(function_name, arguments);
    return_string.insert(return_string.end(), function_mapping.function_body.begin(), function_mapping.function_body.end());
    return {function_mapping.function_body, function_mapping.return_val};
}
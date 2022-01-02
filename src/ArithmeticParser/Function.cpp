#include "ArithmeticParser/Function.h"

Function::Function(std::vector<RDParseTreeNode *> args_in, std::string function_name_in) : 
    function_arguments(args_in),            
    function_name(function_name_in.substr(0, function_name_in.find_first_of('(')))
{
    tt = TOC_TYPES::FUNCTION_E;         // Set the type of this node.
}

TOC_RETURN_VALUE Function::generateThreeOPCode(int &starting_address){
    // The three op code output of the final function 
    std::vector<std::shared_ptr<ThreeOpCode> > return_string;

    // Symbol table entries for each argument
    std::vector<std::shared_ptr<ST_ENTRY> > arguments;

    // Construct symbol table entries for each computed argument value
    // Recall that each fucntion argument can be an arithmetic, hence we need to compute 
    // a parse tree, build the value and then add a reference in the symbol table.

    int offset = 0;#
     // iterate through the functions arguments
    for(std::vector<RDParseTreeNode*>::iterator it = function_arguments.begin(); it != function_arguments.end(); ++it)     
    {   
        // The return value of the computef argument - i.e. the instructions required to compute the function argument
        TOC_RETURN_VALUE toc_res = (*it)->generateThreeOPCode(starting_address);          
        return_string.insert(return_string.end(), toc_res.pre_string.begin(), toc_res.pre_string.end());
        offset += toc_res.pre_string.size();
        arguments.push_back(toc_res.call_value); 
    }

    FUNCTION_MAPPING_RETURN function_mapping = ::getFunctionMapping(function_name, arguments, starting_address);

    if(function_mapping.result){
        return_string.insert(return_string.end(), function_mapping.toc_inject.begin(), function_mapping.toc_inject.end());
        starting_address += return_string.size() - offset;
        return {return_string, function_mapping.return_val };
    } else {
        Logging::logErrorMessage("Function " + function_name + " not found. Exiting Arithmetic Parser unsuccessfully.");
        exit(-1);
        return {};
    }
}
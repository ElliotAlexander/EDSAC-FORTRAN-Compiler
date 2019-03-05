#include "ArithmeticParser/Function.h"

Function::Function(std::vector<RDParseTreeNode *> args_in, std::string function_name_in)
{
    tt = TOC_TYPES::FUNCTION_E;
    args = args_in;
    function_name = function_name_in;
}

TOC_RETURN_VALUE Function::generateThreeOPCode(int &variable_index){

    std::vector<std::string> arg_list;
    std::vector<std::string> pre_string;

    for (std::vector<RDParseTreeNode *>::iterator it = args.begin(); it != args.end(); ++it) {
        TOC_RETURN_VALUE opreturn = (*it)->generateThreeOPCode(variable_index);
        std::vector<std::string> op_pre_string = opreturn.pre_string;
        pre_string.insert(pre_string.end(), op_pre_string.begin(), op_pre_string.end());
        arg_list.push_back(opreturn.call_value);
    }

    // Setup our final function call.
    // Note that this must be the final thing outputted, preceded by the pre-string.
    Function::function_call = function_name + "(";
    for(int i = arg_list.size() - 1; i != 0; i--){
        Function::function_call.append(arg_list.at(i));
        Function::function_call.append(",");
    }
    Function::function_call.pop_back();
    Function::function_call.append(")");

    // return combined string.
    return {pre_string, Function::function_call};
}
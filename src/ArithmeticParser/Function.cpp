#include "ArithmeticParser/Function.h"

Function::Function(std::vector<RDParseTreeNode *> args_in, std::string function_name_in)
{
    tt = TOC_TYPES::FUNCTION_E;
    args = args_in;
    function_name = function_name_in;
}

TOC_RETURN_VALUE Function::generateThreeOPCode(){
    return {};
}
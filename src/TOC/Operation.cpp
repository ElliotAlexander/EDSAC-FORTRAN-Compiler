#include "ArithmeticParser/Operation.h"

Operation::Operation(RDParseTreeNode *arg1_in, RDParseTreeNode *arg2_in, OPS operation)
{
    tt = TOC_TYPES::OPERATION_E;
    arg1 = arg1_in;
    arg2 = arg2_in;
    op = operation;
};

std::string Operation::toOPType(OPS e)
{
    switch (e)
    {
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

TOC_RETURN_VALUE Operation::generateThreeOPCode(int &variable_index){
    std::vector<std::string> pre_string;


    TOC_RETURN_VALUE arg1_ret = arg1->generateThreeOPCode(variable_index);
    TOC_RETURN_VALUE arg2_ret = arg2->generateThreeOPCode(variable_index);
    
    pre_string.insert(pre_string.end(), arg1_ret.pre_string.begin(), arg1_ret.pre_string.end());
    pre_string.insert(pre_string.end(), arg2_ret.pre_string.begin(), arg2_ret.pre_string.end());

    pre_string.push_back("$" + std::to_string(variable_index) + std::string("=") + arg1_ret.call_value + toOPType(op) + arg2_ret.call_value);
    std::string return_call_value = std::string("$" + std::to_string(variable_index));
    
    return {pre_string, return_call_value};
}
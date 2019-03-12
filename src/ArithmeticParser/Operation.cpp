#include "ArithmeticParser/Operation.h"

Operation::Operation(RDParseTreeNode* arg1_in, RDParseTreeNode* arg2_in, OPS operation) : 
    arg1(arg1_in), 
    arg2(arg2_in), 
    op(operation)
{
    Operation::st_entry = addTemp("", ST_ENTRY_TYPE::FLOAT_T);
    tt = TOC_TYPES::OPERATION_E;
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

TOC_RETURN_VALUE Operation::generateThreeOPCode(){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;

    TOC_RETURN_VALUE arg1_ret = arg1->generateThreeOPCode();
    TOC_RETURN_VALUE arg2_ret = arg2->generateThreeOPCode();


    pre_string.insert(pre_string.begin(), arg1_ret.pre_string.begin(), arg1_ret.pre_string.end());
    pre_string.insert(pre_string.begin(), arg2_ret.pre_string.begin(), arg2_ret.pre_string.end());

    switch (Operation::op) {
        case SUBTRACT:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        case ADD:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        default:
            std::cout << "Error" << std::endl;
    }
    
    return {pre_string, st_entry};
}
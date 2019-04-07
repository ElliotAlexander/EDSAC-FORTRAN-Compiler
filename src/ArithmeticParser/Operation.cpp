#include "ArithmeticParser/Operation.h"

Operation::Operation(RDParseTreeNode* arg1_in, RDParseTreeNode* arg2_in, OPS operation) : 
    arg1(arg1_in), 
    arg2(arg2_in), 
    op(operation)
{
    Operation::st_entry = SymbolTableController::addTemp("", ST_ENTRY_TYPE::FLOAT_T);
    tt = TOC_TYPES::OPERATION_E;
	Logging::logMessage("Initialised op with " + arg1_in->st_entry->value);
	Logging::logMessage("Initialised op with " + arg2_in->st_entry->value);
	Logging::logMessage("initialised with op type " + toOPType(op));
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

TOC_RETURN_VALUE Operation::generateThreeOPCode(int &starting_address){
    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;

    TOC_RETURN_VALUE arg1_ret = arg1->generateThreeOPCode(starting_address);
    TOC_RETURN_VALUE arg2_ret = arg2->generateThreeOPCode(starting_address);


    pre_string.insert(pre_string.begin(), arg1_ret.pre_string.begin(), arg1_ret.pre_string.end());
    pre_string.insert(pre_string.begin(), arg2_ret.pre_string.begin(), arg2_ret.pre_string.end());

	ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

    switch (Operation::op) {
        case SUBTRACT:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        case ADD:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        case MULTIPLY:
        // TODO clear Multiplier?
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::MULTIPLY_AND_ADD, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        default:
            std::cout << "Error - operation not implemented" << std::endl;
    }

    Logging::logInfoMessage("Incrementing starting address by " + std::to_string(pre_string.size()));
    starting_address += pre_string.size();
    
    return {pre_string, st_entry};
}
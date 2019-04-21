#include "ArithmeticParser/Operation.h"

Operation::Operation(RDParseTreeNode* arg1_in, RDParseTreeNode* arg2_in, OPS operation) : 
    arg1(arg1_in), 
    arg2(arg2_in), 
    op(operation)
{
    Operation::st_entry = SymbolTableController::addTemp("", ST_ENTRY_TYPE::FLOAT_T);
    tt = TOC_TYPES::OPERATION_E;
};

std::string Operation::toOPType(OPS e)
{
    switch (e)
    {
    case SUBTRACT_OPERATION:
        return "-";
    case ADD_OPERATION:
        return "+";
    case MULTIPLY_OPERATION:
        return "*";
    case DIVIDE_OPERATION:
        return "/";
    case EXPONENT_OPERATION:
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

    int argument_offset_size = arg1_ret.pre_string.size() + arg2_ret.pre_string.size();
    
	ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");

    switch (Operation::op) {
        case SUBTRACT_OPERATION:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        case ADD_OPERATION:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        case MULTIPLY_OPERATION:
        // TODO clear Multiplier?
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::COPY_TO_MULTIPLIER, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::MULTIPLY_AND_ADD, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        case EXPONENT_OPERATION:
            {
                std::shared_ptr<int> loop_start_line_mapping = LineMapping::addTemporaryLineMapping(starting_address + 8);
                std::shared_ptr<int> loop_end_line_mapping = LineMapping::addTemporaryLineMapping(starting_address + 20);
                std::shared_ptr<ST_ENTRY> temp_int_one = SymbolTableController::addTemp("1", ST_ENTRY_TYPE::INT_T);
                std::shared_ptr<ST_ENTRY> temp_int_two = SymbolTableController::addTemp("2", ST_ENTRY_TYPE::INT_T);
                std::shared_ptr<ST_ENTRY> temp_int_rolling = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);

                std::shared_ptr<ST_ENTRY> arg_2_working_copy = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);

                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

                // Copy arg 1
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

                // Copy arg 2
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

                // Subtract once
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_one, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));

                // loop reentry
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_one, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));

                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_end_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));


                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::COPY_TO_MULTIPLIER, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::MULTIPLY_AND_ADD, false)));

                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));

                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_start_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                break;
            }
        default: 
            Logging::logErrorMessage("Operation not implemented");
    }

    starting_address += pre_string.size() - argument_offset_size;
    
    return {pre_string, st_entry};
}
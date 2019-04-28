#include "ArithmeticParser/Operation.h"

/**
 *  Class Operation
 *      
 * 
 *  This class is solely responsible for building instructions for all simple arithmetic operations inside the compiler.    
 *  This class takes two values (or arguments), which are both references to the top of another parse tree. 
 *  This class also takes an operation type. Depending on the operation type, three op code is generated which computes the value of the operation.
 *
 * 
 *      Member Variables:
 *           arg1: The first argument for the operation (LHS)
 *           ar2: The second argument for the operattion (RHS)
 *           op: The operation type
 *
 * 
 **/

Operation::Operation(RDParseTreeNode* arg1_in, RDParseTreeNode* arg2_in, OPS operation) : 
    arg1(arg1_in), 
    arg2(arg2_in), 
    op(operation)
{   
    Operation::st_entry = SymbolTableController::addTemp("", ST_ENTRY_TYPE::FLOAT_T);
    // Set the type of parse tree node
    tt = TOC_TYPES::OPERATION_E;
};



// This function is the brains of all the arithmetic
// This is effectively a big macro stackint the correct series of operations ot manipulate both arguments.
// Depending on the operation, we buiild a big list of the three op code required toi compute the final value.
TOC_RETURN_VALUE Operation::generateThreeOPCode(int &starting_address){

    std::vector<std::shared_ptr<ThreeOpCode> > pre_string;


    // We need ot generate the three op code required for both arguments to have a consistent state.
    // This class might represent X + Y, where X = 1+1 and Y = functioncall(5)
    // Compute both these arguments first, and append their three op code to the final output.
    TOC_RETURN_VALUE arg1_ret = arg1->generateThreeOPCode(starting_address);        // Recall that arguments are also Parse tree nodes. 
    TOC_RETURN_VALUE arg2_ret = arg2->generateThreeOPCode(starting_address);

    // Cnonstruct a complete output
    pre_string.insert(pre_string.begin(), arg2_ret.pre_string.begin(), arg2_ret.pre_string.end());
    pre_string.insert(pre_string.begin(), arg1_ret.pre_string.begin(), arg1_ret.pre_string.end());

    // When iterating starting address, we need to ignore the size of the appended three op code.
    // The generateThreeOpCode method for each argument will modify starting_address by reference, so we can ignore that here.
    // Without this line, multiople stacked operations would slowly offset themselves too far, causing referencing errors. 
    int argument_offset_size = arg1_ret.pre_string.size() + arg2_ret.pre_string.size();
    
    // load a buffer flush variable, check it's initialised properly. 
    // This variabvle is used to clear the accumulator into when we're done with values in it.
	ALL_ST_SEARCH_RESULT flush_to = SymbolTableController::getVariable(Globals::BUFFER_FLUSH_NAME);
	Logging::logConditionalErrorMessage(!flush_to.found, "Failed to find buffer flush ST_ENTRY!");


    // The three op code we generate is dependent on the argument. 
    // For all possible operations, we have two arguments and one op.
    // arg1 == LHS
    // arg2 == RHS
    // it is important that all of these operations leave the accumulator in an empty state - we don't know  which operatioon might be following it.
    switch (Operation::op) {
        /**
         *  Subtraction is simple to implement. The algorithm is as follows:
         *  1) Clear the accumulator
         *  2) Add the left hand side to the accumulator.
         *  3) Subtract the right hand side from the accumulator
         *  4) Transfer the accumulator out, clearing it in the process and setting the return value.
         * 
         **/
        case SUBTRACT_OPERATION:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        /**
         *  Additoin is implemented in a similar way to subtraction, with the exception of an addition instead of a substraction. THe algorithm is as follows:
         *  1) Clear the accumulator
         *  2) Add the left hand side to the accumulator.
         *  3) Add the right hand side to the accumulator
         *  4) Transfer the accumulator out, clearing it in the process and setting the return value.
         **/
        case ADD_OPERATION:
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        case MULTIPLY_OPERATION:
        /**
         *  Multiplication is slightly more complex than addition and subtraction.
         *  We need to add one value to the multiplier, then multiply the value into the cleared accumulator.
         *  EDSAC repreents all values as fractions, so for two short integers, we need to shift the value left by 16 bits twice.
         *  THis bit shift is essential for correct values, as edsac represents all values as fracitons. Multipling fractions causes them to shrink!
         *  Once we've bit shfited the two values, we can transfer them out of the return value into the accumulator.
         **/
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::COPY_TO_MULTIPLIER, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::MULTIPLY_AND_ADD, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));
            pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
            break;
        /**
         * The implementation of EXPONENTS is complex, involving a top-heavy loop. 
         * We set backup 'working' copies of each variable - this is important if the same bit of code is called twice.
         * We can't modify the original values of anything, else the second iteration of the code won't work.
         * 
         * We set backup variables, and then set the top of a loop. The algorithm for the whole loop is as follows:
         * 1) Set backup variables of both arguments. 
         * 2) Ensure that these backup variables are *reinitialised* each time the code runs. This means not just assigning a symbol table value, but copying it programatically.
         * 3) Subtract one from the exponent argument. This is important, we'll count down the exponent until it's zero - so we need to subtract one. i.e. 5^2 only multiples five by itself once, not twice
         *      This step is important for ensuring that x^n doesn't become x^n+1
         * 4) Enter the loop. The loop is top heavy (the bottom of the loop always returns to the top, where the loop may exit via a jump. The loop should *never* exit from the bottom).
         *      subtract one from the exponent count. Check if the exponent count is zero. If it is - exit the loop.
         *  5) If the exponent count is not zero - multiply n * n.  Remember that we need to bit shift this value left by 16 bits twice to ensure that it's properly placed in the accumulator.
         *  6) Replace argument 1 with the new value. This means that the next time we loop, we won't be doing n*n, but (N*N)*N. One variable never needs to change, the other is gradually built up.
         *  7) return to the top of the loop
         * **/ 
        case EXPONENT_OPERATION:
            {

                std::shared_ptr<int> loop_start_line_mapping = LineMapping::addTemporaryLineMapping(starting_address + 8);
                std::shared_ptr<int> loop_end_line_mapping = LineMapping::addTemporaryLineMapping(starting_address + 20);
                std::shared_ptr<ST_ENTRY> temp_int_one = SymbolTableController::addTemp("1", ST_ENTRY_TYPE::INT_T);
                std::shared_ptr<ST_ENTRY> temp_int_two = SymbolTableController::addTemp("2", ST_ENTRY_TYPE::INT_T);
                std::shared_ptr<ST_ENTRY> temp_int_rolling = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);


                // Seup a rolling copy of arg2 
                std::shared_ptr<ST_ENTRY> arg_2_working_copy = SymbolTableController::addTemp("", ST_ENTRY_TYPE::UNASSIGNED_T);

                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

                // Copy arg 1
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

                // Copy arg 2
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg2_ret.call_value, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));

                // Set arg2 to arg2 - 1
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_one, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));

                // loop reentry
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_one, THREE_OP_CODE_OPERATIONS::SUBTRACT_TO_ACCUMULATOR, false)));

                // Main multiplication code
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg_2_working_copy, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_end_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_NEGATIVE, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));


                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(arg1_ret.call_value, THREE_OP_CODE_OPERATIONS::COPY_TO_MULTIPLIER, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::MULTIPLY_AND_ADD, false)));

                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode("64", THREE_OP_CODE_OPERATIONS::SHIFT_ACCUMULATOR_LEFT, false)));


                // Return loop to th etop
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACCUMULATOR_NO_CLEAR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(loop_start_line_mapping, THREE_OP_CODE_OPERATIONS::ACCUMULATOR_IF_POSTITIVE, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(flush_to.result, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(temp_int_rolling, THREE_OP_CODE_OPERATIONS::ADD_TO_ACCUMULATOR, false)));
                pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR, false)));
                break;
            }
        default: 
            Logging::logErrorMessage("Division operations are not supported.");
    }


    // Iterate the starting address. Note that this is passed down by reference through all the parse trees, so that each node of the tree knows its relative position.
    starting_address += pre_string.size() - argument_offset_size;
    
    // Return the three op code string requried to build the computed valuee
    // as well as a refer4ence to the computed value.
    // 
    return {pre_string, st_entry};
}

// Convert the op type to string
// This is a utility class, and has no impact on the internal state of the class
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


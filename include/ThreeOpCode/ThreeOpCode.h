#ifndef __TOC_HEADER_
#define __TOC_HEADER_

#include <memory>
#include "SymbolTable/SymbolTable.h"
#include "ThreeOpCode/ThreeOpCodeUtils.h"


enum THREE_OP_CODE_OPERATIONS {
    ADD_TO_ACCUMULATOR = 0,
    SUBTRACT_TO_ACCUMULATOR = 1,
    COPY_TO_MULTIPLIER = 2,
    MULTIPLY_AND_ADD = 3,
    MULTIPLY_AND_SUBTRACT = 4,
    TRANSFER_FROM_ACUMULATOR = 5,
    TRANSFER_FROM_ACCUMULATOR_NO_CLEAR = 6,
    COLLATE_WITH_MULTIPLER_REGISTER = 7,
    SHIFT_ACCUMULATOR_RIGHT = 8,
    SHIFT_ACCUMULATOR_LEFT = 9,
    ACCUMULATOR_IF_POSTITIVE = 10, 
    ACCUMULATOR_IF_NEGATIVE = 11,
    READ_NEXT_SYMBOL = 12,
    PRINT_SYMBOL = 13,
    READ_LAST_CHAR = 14,
    NO_OPERATION = 15,
    ROUND_ACCUMULATOR_TO_34_BITS = 16,
    STOP_PROGRAM = 17,
    DATA_SET = 18,
};

// This is entire encapsulated within the constructors.
enum ARG_TYPE {
	ARG_IS_ST_ENTRY,
	ARG_IS_STRING,
	ARG_IS_LINE_MAPPING,
};


// Three Op Code and SymbolTable are cyclic
// Forward declare everything we use
struct ST_ENTRY;
class SymbolTable;

class ThreeOpCode {
    public:
        ThreeOpCode(std::shared_ptr<ST_ENTRY> arg1_in_st_entry, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in);
		ThreeOpCode(std::shared_ptr<int> arg1_in_line_mapping, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in);
		ThreeOpCode(std::string arg_in, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in);
        std::string getAddress();
        THREE_OP_CODE_OPERATIONS getOperation();
        std::string printToString();
        bool getLongAddress();
    private: 
		ARG_TYPE input_arg_type;
        std::shared_ptr<ST_ENTRY> ARGUMENT_ST_ENTRY;
		std::shared_ptr<int> ARGUMENT_LINE_MAPPING;
        std::string ARGUMENT_STR;
        THREE_OP_CODE_OPERATIONS OPERATION;
        bool LONG_ADDRESS;
};


#endif
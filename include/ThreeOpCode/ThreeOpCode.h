#ifndef __TOC_HEADER_
#define __TOC_HEADER_

#include <memory>
#include "SymbolTable/STController.h"
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
    PINT_SYMBOL = 13,
    READ_LAST_CHAR = 14,
    NO_OPERATION = 15,
    ROUND_ACCUMULATOR_TO_34_BITS = 16,
    STOP_PROGRAM = 17,
    DATA_SET = 18,
};

class ThreeOpCode {
    public:
        ThreeOpCode(std::shared_ptr<ST_ENTRY>, THREE_OP_CODE_OPERATIONS, bool);
        std::string toString();
    private: 
        std::shared_ptr<ST_ENTRY> ARGUMENT;
        THREE_OP_CODE_OPERATIONS OPERATION;
        bool LONG_ADDRESS;
};


#endif
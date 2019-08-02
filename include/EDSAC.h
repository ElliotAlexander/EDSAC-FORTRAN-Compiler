#ifndef __EDSAC_H_
#define __EDSAC_H_

#include <bitset>
#include <vector>
#include <string>
#include "ThreeOpCode/ThreeOpCode.h"

namespace EDSAC
{

    #define EDSAC_LONG_VALUE "D"
    #define EDSAC_SHORT_VALUE "F"
    #define EDSAC_DATA_VAL_1_REPRESENTATION "D"
    #define EDSAC_DATA_VAL_0_REPRESENTATION "0F"
    #define EDSAC_PROGRAM_ENTRY_POINT_DEFINITION std::string("T" + std::to_string(Globals::base_memory_offset) + "K")

    #define EDSAC_ADD_TO_ACCUMULATOR_INSTRUCTION "A"
    #define EDSAC_SUBTRACT_TO_ACCUMULATOR_INSTRUCTION "S"
    #define EDSAC_COPY_TO_MULTIPLIER_INSTRUCTION "H"
    #define EDSAC_MULTIPLY_AND_ADD_INSTRUCTION "V"
    #define EDSAC_MULTIPLY_AND_SUBTRACT_INSTRUCTION "N"
    #define EDSAC_TRANSFER_FROM_ACCUMULATOR_INSTRUCTION "T"
    #define EDSAC_TRANSFER_FROM_ACCUMULATOR_NO_CLEAR_INSTRUCTION "U"
    #define EDSAC_COLLATE_WITH_MULTIPLIER_REGISTER_INSTRUCTION "C"
    #define EDSAC_SHIFT_ACCUMULATOR_RIGHT_INSTRUCTION "R"
    #define EDSAC_SHIFT_ACCUMULATOR_LEFT_INSTRUCTION "L"
    #define EDSAC_ACCUULATOR_IF_POSITIVE_INSTRUCTION "E"
    #define EDSAC_ACCUULATOR_IF_NEGATIVE_INSTRUCTION "G"
    #define EDSAC_READ_NEXT_CHAR_INSTRUCTION "I"
    #define EDSAC_PRINT_SYMMBOL_INSTRUCTION "O"
    #define EDSAC_READ_LAST_CHAR_INSTRUCTION "F"
    #define EDSAC_NO_OPERATION_INSTRUCTION "X"
    #define EDSAC_ROUND_ACCUMULATOR_INSTRUCTION "Y"
    #define EDSAC_STOP_PROGRAM_INSTRUCTION "Z"

    #define EDSAC_DATA_ORDER_INSTRUCTION "P"
    #define EDSAC_DATA_FLOAT_INSTRUCTION "Q"


    std::string convertOperationEnumToString(THREE_OP_CODE_OPERATIONS op);

    std::bitset<17> convert_float_to_edsac_bitset17 (float f);
    std::string convert_edsac_bitset17_to_edsac_op(std::bitset<17> bits);
    std::vector<std::string> generateEDSAC(std::vector<std::shared_ptr<ThreeOpCode> > input, std::vector<std::string> libraries);
} // EDSAC

#endif
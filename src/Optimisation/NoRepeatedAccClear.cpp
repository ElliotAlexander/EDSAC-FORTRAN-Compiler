#include "Optimization/NoRepeatedAccClear.h"

NoRepeatedAccClear::NoRepeatedAccClear() {
}

std::vector<std::shared_ptr<ThreeOpCode> > NoRepeatedAccClear::processProgram(std::vector<std::shared_ptr<ThreeOpCode> > input) {
    for(int index = 0; index < input.size() - 1; index++){
        if(input.at(index)->getOperation() == THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR &&
            input.at(index + 1)->getOperation() == THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR) {
                for (int erase_index = index + 1; erase_index < input.size() - 1; ++erase_index) {
                    input[erase_index] = input[erase_index + 1]; 
                }
        }
    }
    return input;
}
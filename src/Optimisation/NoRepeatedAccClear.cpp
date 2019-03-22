#include "Optimization/NoRepeatedAccClear.h"

NoRepeatedAccClear::NoRepeatedAccClear() {
}

std::vector<std::shared_ptr<ThreeOpCode> > NoRepeatedAccClear::processProgram(std::vector<std::shared_ptr<ThreeOpCode> > input) {
    for(int index = 0; index < input.size() - 1; index++){
        if(input.at(index)->getOperation() == THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR &&
            input.at(index)->getOperation() == THREE_OP_CODE_OPERATIONS::TRANSFER_FROM_ACUMULATOR){
                std::shared_ptr<ThreeOpCode> ptr;
                input.erase(std::remove(input.begin(), input.end(), ptr), input.end());
        }
    }
    return input;
}
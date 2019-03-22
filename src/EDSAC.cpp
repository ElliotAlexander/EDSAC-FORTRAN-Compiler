#include "EDSAC.h"

namespace EDSAC {
    std::vector<std::string> generateEDSAC(std::vector<std::shared_ptr<ThreeOpCode> > input) {
        std::vector<std::string> output;
        for(std::vector<std::shared_ptr<ThreeOpCode> >::iterator it = input.begin(); it != input.end(); ++it){
            THREE_OP_CODE_OPERATIONS op = (*it)->getOperation();
            std::string build_string;
            build_string.append(convertOperationEnumToString(op));
            build_string.append((*it)->getAddress());

            std::string long_string = (*it)->getLongAddress() ? "L" : "S";
            build_string.append(long_string);
            output.push_back(build_string);
        }
        return output;
    }


    std::string convertOperationEnumToString(THREE_OP_CODE_OPERATIONS op) {
        switch (op) {
            case ADD_TO_ACCUMULATOR:
                return "A";
            case SUBTRACT_TO_ACCUMULATOR:
                return "S";
            case COPY_TO_MULTIPLIER:
                return "H";
            case MULTIPLY_AND_ADD:
                return "V";
            case MULTIPLY_AND_SUBTRACT:
                return "N";
            case TRANSFER_FROM_ACUMULATOR:
                return "T";
            case TRANSFER_FROM_ACCUMULATOR_NO_CLEAR:
                return "U";
            case COLLATE_WITH_MULTIPLER_REGISTER:
                return "C";
            case SHIFT_ACCUMULATOR_RIGHT:
                return "R";
            case SHIFT_ACCUMULATOR_LEFT:
                return "L";
            case ACCUMULATOR_IF_POSTITIVE:
                return "E";
            case ACCUMULATOR_IF_NEGATIVE:
                return "G";
            case READ_NEXT_SYMBOL:
                return "I";
            case PRINT_SYMBOL:
                return "O";
            case READ_LAST_CHAR:
                return "F";
            case NO_OPERATION:
                return "X";
            case ROUND_ACCUMULATOR_TO_34_BITS:
                return "Y";
            case STOP_PROGRAM:
                return "Z";
            case DATA_SET:
                return "P";
            default:
                Logging::logErrorMessage("Something went wrong - failed to generate EDSAC character codes.");
                return {};
        }
    }
}

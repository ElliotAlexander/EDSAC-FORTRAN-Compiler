#include "EDSAC.h"

namespace EDSAC {

    // This function maps the ENUM value for each Three Op Code to the string value used for EDSAC
    // Input -> internal representation of instruction 
    // Output -> String value for each instruction.
    // Note that NO_OPERATION returns an empty string.
    std::string convertOperationEnumToString(THREE_OP_CODE_OPERATIONS op) {
        switch (op) {
            case ADD_TO_ACCUMULATOR:
                return EDSAC_ADD_TO_ACCUMULATOR_INSTRUCTION;
            case SUBTRACT_TO_ACCUMULATOR:
                return EDSAC_SUBTRACT_TO_ACCUMULATOR_INSTRUCTION;
            case COPY_TO_MULTIPLIER:
                return EDSAC_COPY_TO_MULTIPLIER_INSTRUCTION;
            case MULTIPLY_AND_ADD:
                return EDSAC_MULTIPLY_AND_ADD_INSTRUCTION;
            case MULTIPLY_AND_SUBTRACT:
                return EDSAC_MULTIPLY_AND_SUBTRACT_INSTRUCTION;
            case TRANSFER_FROM_ACUMULATOR:
                return EDSAC_TRANSFER_FROM_ACCUMULATOR_INSTRUCTION;
            case TRANSFER_FROM_ACCUMULATOR_NO_CLEAR:
                return EDSAC_TRANSFER_FROM_ACCUMULATOR_NO_CLEAR_INSTRUCTION;
            case COLLATE_WITH_MULTIPLER_REGISTER:
                return EDSAC_COLLATE_WITH_MULTIPLIER_REGISTER_INSTRUCTION;
            case SHIFT_ACCUMULATOR_RIGHT:
                return EDSAC_SHIFT_ACCUMULATOR_RIGHT_INSTRUCTION;
            case SHIFT_ACCUMULATOR_LEFT:
                return EDSAC_SHIFT_ACCUMULATOR_LEFT_INSTRUCTION;
            case ACCUMULATOR_IF_POSTITIVE:
                return EDSAC_ACCUULATOR_IF_POSITIVE_INSTRUCTION;
            case ACCUMULATOR_IF_NEGATIVE:
                return EDSAC_ACCUULATOR_IF_NEGATIVE_INSTRUCTION;
            case READ_NEXT_SYMBOL:
                return EDSAC_READ_NEXT_CHAR_INSTRUCTION;
            case PRINT_SYMBOL:
                return EDSAC_PRINT_SYMMBOL_INSTRUCTION;
            case READ_LAST_CHAR:
                return EDSAC_READ_LAST_CHAR_INSTRUCTION;
            case NO_OPERATION:
                return EDSAC_NO_OPERATION_INSTRUCTION;
            case ROUND_ACCUMULATOR_TO_34_BITS:
                return EDSAC_ROUND_ACCUMULATOR_INSTRUCTION;
            case STOP_PROGRAM:
                return EDSAC_STOP_PROGRAM_INSTRUCTION;
            case DATA_SET:
                return EDSAC_DATA_ORDER_INSTRUCTION;
            case DATA_SET_FLOAT:
                return EDSAC_DATA_FLOAT_INSTRUCTION;
            default:
                // Defensive programming - this shouldn't happen.
                Logging::logErrorMessage("Something went wrong - failed to generate EDSAC character codes.");
                return {};  // Return no instruction
        }
    }

    // 	std::string convert_int_to_edsac_op(int x); 
    // This function converts a typical EDSAC 'address' into the correct bit pattern for a data value of the same number.
    // i.e. for positive ints, a data value = 2n, and 2n + 1 for negative ints. 
    // The two exceptions to this process are 0  and 1, which are repsented as OF and D / OD respectively. 
    // 
	std::string convert_int_to_edsac_op(int address_value){
		if (address_value == 0) {
			return EDSAC_DATA_VAL_0_REPRESENTATION;
		} else if (address_value == 1) {
			return EDSAC_DATA_VAL_1_REPRESENTATION;
		} else if (address_value % 2 == 0) {
			return std::string(std::to_string(address_value / 2) + EDSAC_SHORT_VALUE);
		} else {
			return std::string(std::to_string((address_value - 1)  / 2) + EDSAC_LONG_VALUE);
		}
	}

    // Assumes IEEE 754 binary32 floating-point format is used.
    std::bitset<17> convert_float_to_edsac_bitset17(float f) {
        const int float32_exp_bias = 127;
        const int float17_exp_bias = 15;

        const int float17_sign_bits = 1;
        const int float17_exp_bits = 5;
        const int float17_sig_bits = 11;

        const int float32_sign_bits = 1;
        const int float32_exp_bits = 8;
        const int float32_sig_bits = 23;

        // float to bit string
        std::bitset<32> float32_bits(*(unsigned int *) (&f));
        std::string float32_bits_str = float32_bits.to_string();

        // extract sign
        std::string float17_bits_sign_str = float32_bits_str.substr(0, float32_sign_bits);

        // extract and calculate new exp
        std::string float32_bits_exp_str = float32_bits_str.substr(float32_sign_bits, float32_exp_bits);
        int float32_bits_exp_biased = std::stoi(float32_bits_exp_str, nullptr, 2);
        int float32_bits_exp_unbiased = float32_bits_exp_biased - float32_exp_bias;
        int float17_bits_exp_biased = float32_bits_exp_unbiased + float17_exp_bias;
        if (float32_bits_exp_biased == 0) {  // exception: when biased exp is zero, it means zero.
            float17_bits_exp_biased = 0;
        }
        std::string float17_bits_exp_str = std::bitset<float17_exp_bits>(float17_bits_exp_biased).to_string();

        // extract and process significand
        std::string float32_bits_sig_str = float32_bits_str.substr(float32_sign_bits + float32_exp_bits, float32_sig_bits);
        std::string float17_bits_sig_str = float32_bits_sig_str.substr(0, float17_sig_bits);

        // concat result
        std::string float17_str = float17_bits_sign_str + float17_bits_exp_str + float17_bits_sig_str;
        return std::bitset<17>(float17_str);
    }

    std::string convert_edsac_bitset17_to_edsac_op(std::bitset<17> bits) {
        const std::string perforator_letters = "PQWERTYUIOJ#SZK*.F@D!HNM&LXGABCV";

        std::string bits_str = bits.to_string();
        std::string bits_opcode = bits_str.substr(0, 5);
        std::string bits_address = bits_str.substr(5, 11);
        std::string bits_length = bits_str.substr(16, 1);

        int bits_opcode_int = std::stoi(bits_opcode, nullptr, 2);
        int bits_address_int = std::stoi(bits_address, nullptr, 2);
        int bits_length_int = std::stoi(bits_length, nullptr, 2);

        return perforator_letters.substr(bits_opcode_int, 1) +
               std::to_string(bits_address_int) +
               (bits_length_int ? EDSAC_LONG_VALUE : EDSAC_SHORT_VALUE);
    }

    //  std::vector<std::string> generateEDSAC(std::vector<std::shared_ptr<ThreeOpCode> > input, std::vector<std::string> libraries) 
    //  This function takes an input of ThreeOpCode, and a string of pre_built libraries.
    //  The functionality of this function is to build ThreeOpCode into a string value for final EDSAC instructions.
    //  The return value for this function is the final generated EDSAC instructions, incuding the libraries.
    //  
    std::vector<std::string> generateEDSAC(std::vector<std::shared_ptr<ThreeOpCode> > input, std::vector<std::string> libraries) {
        std::vector<std::string> output = libraries;                                        // initialise final output data value to libraries.  Libraries are appended to the start of all programs.
        output.insert(output.begin(), EDSAC_PROGRAM_ENTRY_POINT_DEFINITION);                // Insert the T<entry point>K instruction required to set the Initial Orders 2 entry point.
        for(auto & it : input){      // Iterate through Program body.
            std::string build_string;                                                       // Build string is the final output value of each loop. It represents the 'EDSAC' instruction string.
			std::string address = it->getAddress();                                      // Set the address ot a variable, for readability.
            std::string opcode = convertOperationEnumToString(it->getOperation());

			if (it->getOperation() == THREE_OP_CODE_OPERATIONS::DATA_SET && !address.empty()) {  // If the instruction is a data value, we need to convert the address to a 'pseudo-order'
                build_string.append(opcode);
				build_string.append(convert_int_to_edsac_op(std::stoi(address)));           // Convert address to a 'pseudo-order' so it's set properly as data.
			} else if (it->getOperation() == THREE_OP_CODE_OPERATIONS::DATA_SET_FLOAT && !address.empty()) {
                build_string.append(convert_edsac_bitset17_to_edsac_op(convert_float_to_edsac_bitset17(std::stof(address))));
            } else {
                build_string.append(opcode);       // Begin constructing the instruction string with the instruction value - i.e. the T in T56K. Recall that EDSAC instructions are formatted:
                                                                                             //      <instruction> <address> <short / long>
                build_string.append(address);                                               // If the instruction type isn't a data value, we can treat the address as normal.
				if (it->containsCustomBit()) {                                   // Some control codes specify a unique end bit, handled by initial orders. Handle this if required
					build_string.append(it->getCustomBit());
				} else {
                    build_string.append(it->getLongAddress() ? EDSAC_LONG_VALUE : EDSAC_SHORT_VALUE);               // Else - set the appropriate value for the final bit.
				}
			}
            output.push_back(build_string);                                                 // Construct a final output list of all instructions.
        }
        return output;                                                                      // return a list of strings - our final EDSAC instruction output.
    }

}

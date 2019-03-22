#include "ThreeOpCode/ThreeOpCode.h"

std::string ThreeOpCode::printToString(){
	switch (ThreeOpCode::input_arg_type) {
		case ARG_TYPE::ARG_IS_LINE_MAPPING:
			return std::string(TOCOperationToString(ThreeOpCode::OPERATION) + " " + std::to_string(*ThreeOpCode::ARGUMENT_LINE_MAPPING));
		case ARG_TYPE::ARG_IS_STRING:
			return std::string(TOCOperationToString(ThreeOpCode::OPERATION) + " " + ThreeOpCode::ARGUMENT_STR);
		case ARG_TYPE::ARG_IS_ST_ENTRY:
			return std::string(TOCOperationToString(ThreeOpCode::OPERATION) + " " + std::to_string(ThreeOpCode::ARGUMENT_ST_ENTRY->base_memory_address));
		default:
			return std::string("ERROR - ThreeOpCode generation failed");
	}
}


THREE_OP_CODE_OPERATIONS ThreeOpCode::getOperation(){
    return ThreeOpCode::OPERATION;
}

std::string ThreeOpCode::getAddress(){
    switch (ThreeOpCode::input_arg_type) {
		case ARG_TYPE::ARG_IS_LINE_MAPPING:
			return std::string(std::to_string(*ThreeOpCode::ARGUMENT_LINE_MAPPING));
		case ARG_TYPE::ARG_IS_STRING:
			return std::string(ThreeOpCode::ARGUMENT_STR);
		case ARG_TYPE::ARG_IS_ST_ENTRY:
			return std::string(std::to_string(ThreeOpCode::ARGUMENT_ST_ENTRY->base_memory_address));
		default:
			return std::string("ERROR - ThreeOpCode generation failed");
	}
}

bool ThreeOpCode::getLongAddress(){
    return ThreeOpCode::LONG_ADDRESS;
}


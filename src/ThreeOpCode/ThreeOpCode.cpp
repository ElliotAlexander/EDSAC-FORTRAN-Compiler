#include "ThreeOpCode/ThreeOpCode.h"

ThreeOpCode::ThreeOpCode(std::shared_ptr<ST_ENTRY> arg1_in_st_entry, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in) : 
    ARGUMENT_ST_ENTRY(arg1_in_st_entry), 
    OPERATION(op_in), LONG_ADDRESS(long_addr_in),
	CUSTOM_FINAL_BIT_SET(false), 
    input_arg_type(ARG_TYPE::ARG_IS_ST_ENTRY) 
{};


ThreeOpCode::ThreeOpCode(std::shared_ptr<int> arg1_in_line_mapping, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in) : 
    ARGUMENT_LINE_MAPPING(arg1_in_line_mapping), 
    OPERATION(op_in), LONG_ADDRESS(long_addr_in), 
	CUSTOM_FINAL_BIT_SET(false),
    input_arg_type(ARG_TYPE::ARG_IS_LINE_MAPPING) 
{};

ThreeOpCode::ThreeOpCode(std::string arg_in, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in) : 
    ARGUMENT_STR(arg_in), 
    OPERATION(op_in), 
    LONG_ADDRESS(long_addr_in), 
	CUSTOM_FINAL_BIT_SET(false),
    input_arg_type(ARG_TYPE::ARG_IS_STRING) 
{};

ThreeOpCode::ThreeOpCode(std::string arg_in, THREE_OP_CODE_OPERATIONS op_in, std::string custom_final_bit) : 
    ARGUMENT_STR(arg_in), 
    OPERATION(op_in), 
    CUSTOM_FINAL_BIT(custom_final_bit),
	CUSTOM_FINAL_BIT_SET(true),
    input_arg_type(ARG_TYPE::ARG_IS_STRING),
	LONG_ADDRESS(false)
{};



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

bool ThreeOpCode::containsCustomBit(){
	return CUSTOM_FINAL_BIT_SET;
}

std::string ThreeOpCode::getCustomBit(){
	return CUSTOM_FINAL_BIT;
}
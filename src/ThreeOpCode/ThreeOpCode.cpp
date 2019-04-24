#include "ThreeOpCode/ThreeOpCode.h"

/**
 * 
 * 
 * 	Class ThreeOpCode
 * 
 *  This class encapsulates the internal representation of all EDSAC instructions. 
 *  It encapsulates the argument, operation type, and short / long bit of each isntruction. 
 * 	Multiple constructors are provided to allow for multiplle argument types.
 * 	
 * 
 * 
 * This class is the complete interenal representation, including data values and control codes. Control codes can be set using the string value for the custom_final_bit
 * 
 * 
 * 			Member Variables:
 * 				ARG_TYPE input_arg_type -> The type of each argument, this allows us to differentiate later between each argument constructor.
 *				std::shared_ptr<ST_ENTRY> ARGUMENT_ST_ENTRY -> This argument is used if the argument set is a symbol table entry.
 *				std::shared_ptr<int> ARGUMENT_LINE_MAPPING -> This argument is sued if the argument is a line mapping entry.
 *				std::string ARGUMENT_STR -> this argument is used if the argument is a string value (a constant string value)
 *				THREE_OP_CODE_OPERATIONS OPERATION -> This flag represents the OPERATION specified. This field is used by all constructors, 
 *				bool LONG_ADDRESS -> this flag is set if a long address is provided.
 * 				bool CUSTOM_FINAL_BIT_SET -> This flag is set if a custom long bit is provided. Note that this flag overrides LONG_ADDRESS
 * 				std::string CUSTOM_FINAL_BIT -> If a custom final bit is set - it's value is stored here.
 **/ 			


/** This constructor allows control codes to be set using the string valuee as the final bit **/
/** Control codes are invisible to EDSAC, so appending them to the end of one instruction allows us to treat them as one address while including them **/
ThreeOpCode::ThreeOpCode(std::string arg_in, THREE_OP_CODE_OPERATIONS op_in, std::string custom_final_bit) : 
    ARGUMENT_STR(arg_in), 
    OPERATION(op_in), 
    CUSTOM_FINAL_BIT(custom_final_bit),
	CUSTOM_FINAL_BIT_SET(true),
    input_arg_type(ARG_TYPE::ARG_IS_STRING)
{	
	// Flag for final bit
	CUSTOM_FINAL_BIT_SET = true;
};

ThreeOpCode::ThreeOpCode(std::shared_ptr<ST_ENTRY> arg1_in_st_entry, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in) : 
    ARGUMENT_ST_ENTRY(arg1_in_st_entry), 
    OPERATION(op_in), 
	LONG_ADDRESS(long_addr_in),
	CUSTOM_FINAL_BIT_SET(false), 
    input_arg_type(ARG_TYPE::ARG_IS_ST_ENTRY) 
{};


ThreeOpCode::ThreeOpCode(std::shared_ptr<int> arg1_in_line_mapping, THREE_OP_CODE_OPERATIONS op_in, bool long_addr_in) : 
    ARGUMENT_LINE_MAPPING(arg1_in_line_mapping), 
    OPERATION(op_in), 
	LONG_ADDRESS(long_addr_in), 
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
#include "ThreeOpCode/ThreeOpCode.h"

ThreeOpCode::ThreeOpCode(std::shared_ptr<ST_ENTRY> ARG_IN, THREE_OP_CODE_OPERATIONS OP_IN, bool LONG_ARG) : ARGUMENT(ARG_IN), OPERATION(OP_IN), LONG_ADDRESS(LONG_ARG) 
{};


std::string ThreeOpCode::toString(){
    return std::string(TOCOperationToString(ThreeOpCode::OPERATION) + " " + std::to_string(ThreeOpCode::ARGUMENT->base_memory_address));
}
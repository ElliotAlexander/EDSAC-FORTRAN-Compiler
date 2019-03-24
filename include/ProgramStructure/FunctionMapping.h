#ifndef __FUNCTION_MAPPING_H_
#define __FUNCTION_MAPPING_H_


#include <memory>
#include <string>
#include <map>
#include <vector>

#include "SymbolTable/STController.h"
#include "SymbolTable/SymbolTable.h"
#include "Globals.h"
#include "ThreeOpCode/ThreeOpCode.h"

struct ARITH_FUNCTION_MAPPING_ENTRY {
    // The return value for the function exists at this address.
    std::shared_ptr<ST_ENTRY> value_return_address;
    std::vector<std::shared_ptr<ThreeOpCode> > function_body;
    std::vector<std::shared_ptr<ST_ENTRY> > arguments;
};

struct ARITH_FUNCTION_MAPPING_RETURN {
    bool found;
    std::vector<std::shared_ptr<ThreeOpCode> > function_body;
    std::shared_ptr<ST_ENTRY> return_val;
};

extern std::map<std::string, ARITH_FUNCTION_MAPPING_ENTRY> arithmetic_function_mappings;

ARITH_FUNCTION_MAPPING_ENTRY addArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments, std::vector<std::shared_ptr<ThreeOpCode> > function_body, std::shared_ptr<ST_ENTRY> return_addr);
ARITH_FUNCTION_MAPPING_RETURN getArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments);



#endif
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
#include "ProgramStructure/LineMapping.h"

enum FUNCTION_ENTRY_TYPE {
    SUBROUTINE_TYPE = 0,
    FUNCTION_TYPE = 0
};

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

struct FUNCTION_MAPPING_ENTRY {
    std::shared_ptr<int> start_line;
    std::vector<std::string> arguments;
    FUNCTION_ENTRY_TYPE type;
};


struct FUNCTION_MAPPING_RETURN {
    std::vector<std::shared_ptr<ThreeOpCode> > toc_inject;
    bool result;
};

extern std::map<std::string, ARITH_FUNCTION_MAPPING_ENTRY> arithmetic_function_mappings;
extern std::map<std::string, FUNCTION_MAPPING_ENTRY> function_mappings;
extern std::shared_ptr<int> return_address_mapping;

ARITH_FUNCTION_MAPPING_ENTRY addArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments, std::vector<std::shared_ptr<ThreeOpCode> > function_body, std::shared_ptr<ST_ENTRY> return_addr);
ARITH_FUNCTION_MAPPING_RETURN getArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments);

bool addFunctionMapping(std::string name, std::vector<std::string> arguments, int start_line);

#endif
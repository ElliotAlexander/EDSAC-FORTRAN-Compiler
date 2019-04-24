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
    std::shared_ptr<ST_ENTRY> value_return_address;
    bool return_val_set;
};

struct FUNCTION_MAPPING_RETURN{
    bool result;
    std::vector<std::shared_ptr<ThreeOpCode> > toc_inject;
    std::shared_ptr<ST_ENTRY> return_val;
};

struct SUBROUTINE_MAPPING_ENTRY {
    std::shared_ptr<int> start_line;
    std::vector<std::string> arguments;
};

struct SUBROUTINE_MAPPING_RETURN {
    std::vector<std::shared_ptr<ThreeOpCode> > toc_inject;
    bool result;
};



extern std::map<std::string, ARITH_FUNCTION_MAPPING_ENTRY> arithmetic_function_mappings;
ARITH_FUNCTION_MAPPING_ENTRY addArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments, std::vector<std::shared_ptr<ThreeOpCode> > function_body, std::shared_ptr<ST_ENTRY> return_addr);
ARITH_FUNCTION_MAPPING_RETURN getArithmeticFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments);


extern std::map<std::string, SUBROUTINE_MAPPING_ENTRY> subroutine_mappings;
extern std::map<std::string, FUNCTION_MAPPING_ENTRY> function_mappings;
extern std::pair<std::shared_ptr<int>, std::shared_ptr<int>> SUBROUTINE_MAPPING_PAIR;
extern std::shared_ptr<int> return_address_mapping;
extern std::string current_function_name;

std::shared_ptr<int> addSubroutineMapping(std::string name, std::vector<std::string> arguments, int start_line);
SUBROUTINE_MAPPING_RETURN getSubroutineMapping(std::string subroutine_name, int return_address, std::vector<std::shared_ptr<ST_ENTRY> > arguments);
std::vector<std::shared_ptr<ThreeOpCode> > exitSubroutine(int end_line);


bool addFunctionMapping(std::string name, std::vector<std::string> arguments, int start_line);
FUNCTION_MAPPING_RETURN getFunctionMapping(std::string function_name, std::vector<std::shared_ptr<ST_ENTRY> > arguments, int return_address);
std::vector<std::shared_ptr<ThreeOpCode> > exitFunction(std::shared_ptr<ST_ENTRY> return_value);

#endif
#ifndef __SYMBOLTABLE_H_
#define __SYMBOLTABLE_H_

#include <map>
#include <string>
#include <memory>
#include "Logging.h"
#include "Globals.h"
#include "SymbolTable/SymbolTableUtils.h"

enum SYMBOL_TABLE_TYPE {
    COMMON = 0,
    TEMP_VAR = 1,
    DECLARED_VAR = 2,
    UNDECLARED_VAR = 3
};

enum ST_ENTRY_TYPE {
    INT_T,
    FLOAT_T,
    UNASSIGNED_T
};

struct ST_ENTRY {
    ST_ENTRY_TYPE type;
    bool assigned;
    int base_memory_address;
    std::string value;
};

struct ST_QUERY_RESULT {
    bool found;
    std::shared_ptr<ST_ENTRY> result;
};

class SymbolTable {
    public:
        int rolling_memory_addr = 0;
        SYMBOL_TABLE_TYPE ST_TYPE;
        SymbolTable(SYMBOL_TABLE_TYPE st);
        bool remove(std::string name);
        std::shared_ptr<ST_ENTRY> add(std::string name, std::string value, ST_ENTRY_TYPE type);
        void printSymbolTable();
        std::vector<std::string> buildSymbolTableOutput();
        int applyOffset(int memory_offset);
        ST_QUERY_RESULT get(std::string name);
    private:
        std::vector<int> freed_vars;
        std::map<std::string, std::shared_ptr<ST_ENTRY> > st_map;
};

#endif
#ifndef _ST_CONTROLLER_H
#define _ST_CONTROLLER_H

#include <memory>
#include "SymbolTable.h"
#include <vector>
#include <string>

const std::unique_ptr<SymbolTable> symbol_tables[4] = {
    std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::DECLARED_VAR)),
    std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::UNDECLARED_VAR)),
    std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::TEMP_VAR)),
    std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::COMMON))
};

struct ALL_ST_SEARCH_RESULT {
    int table_found;
    bool found;
    std::shared_ptr<ST_ENTRY> result;
};

std::shared_ptr<ST_ENTRY> addDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type);
std::shared_ptr<ST_ENTRY> addUnDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type);
std::shared_ptr<ST_ENTRY> addCommon(std::string name, std::string value, ST_ENTRY_TYPE type);
std::shared_ptr<ST_ENTRY> addTemp(std::string value, ST_ENTRY_TYPE type);
std::shared_ptr<ST_ENTRY> copyValue(int st_from, int addr_from, int st_to, int addr_to);
ALL_ST_SEARCH_RESULT getVariable(std::string name);
bool removeVariable(std::string name);

std::shared_ptr<SymbolTable> getST(SYMBOL_TABLE_TYPE type);
bool offsetST(int memory_offset);
void printSymbolTables();
std::vector<std::string> outputSymbolTable();

#endif
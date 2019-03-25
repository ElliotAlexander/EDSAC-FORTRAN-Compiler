#ifndef _ST_CONTROLLER_H
#define _ST_CONTROLLER_H

#include <memory>
#include "SymbolTable/SymbolTable.h"
#include <vector>
#include <string>
#include <map>


struct ALL_ST_SEARCH_RESULT {
    int table_found;
    bool found;
    std::shared_ptr<ST_ENTRY> result;
};

namespace SymbolTableController {

    extern std::unique_ptr<SymbolTable> symbol_tables[4];
    extern std::map<std::string, std::vector<std::shared_ptr<SymbolTable> > > function_symbol_tables;
    extern bool in_function_scope;
    extern std::string function_scope_name;

    
    bool enterFunctionScope(std::string function_name);
    bool exitFunctionScope();


    std::shared_ptr<ST_ENTRY> addDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type);
    std::shared_ptr<ST_ENTRY> addUnDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type);
    std::shared_ptr<ST_ENTRY> addCommon(std::string name, std::string value, ST_ENTRY_TYPE type);
    std::shared_ptr<ST_ENTRY> addTemp(std::string value, ST_ENTRY_TYPE type);
    
    ALL_ST_SEARCH_RESULT getVariable(std::string name);
    bool addLinkedVariable(std::shared_ptr<ST_ENTRY> value, std::string name);
    bool removeVariable(std::string name);

    std::shared_ptr<SymbolTable> getST(SYMBOL_TABLE_TYPE type);
    bool offsetST(int memory_offset);
    void printSymbolTables();
    std::vector<std::shared_ptr<ThreeOpCode> > outputSymbolTable();



}



#endif
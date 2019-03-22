#include "SymbolTable/STController.h"

namespace SymbolTableController{

    std::shared_ptr<ST_ENTRY> addCommon(std::string name, std::string value, ST_ENTRY_TYPE type) {
        return symbol_tables[3]->add(name, value, type);
    }

    std::shared_ptr<ST_ENTRY> addTemp(std::string value, ST_ENTRY_TYPE type){
        return symbol_tables[2]->add(std::to_string(symbol_tables[2]->rolling_memory_addr), value, type);
    }

    std::shared_ptr<ST_ENTRY> addDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type){
        return symbol_tables[0]->add(name, value, type);
    }

    std::shared_ptr<ST_ENTRY> addUnDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type){
        return symbol_tables[1]->add(name, value, type);
    }

    ALL_ST_SEARCH_RESULT getVariable(std::string name){
        ST_QUERY_RESULT res = symbol_tables[0]->get(name);
        if(res.found == 1){
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Found symbol table entry for " + name + " in declared variables"));
            return {0, true, res.result};
        } else {
            ST_QUERY_RESULT res = symbol_tables[1]->get(name);
            if(res.found == 1){
                Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Found symbol table entry for " + name + " in undeclared varaibles."));
                return {1, true, res.result};
            } else {
                return {-1, false, nullptr};
            }
        }
    }


    bool removeVariable(std::string name){
        for(int i = 0; i < 4; i++){
            if(((symbol_tables[i])->get(name)).found == 1){
                symbol_tables[i]->remove(name);
                Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Removing " + name + " from " + std::to_string(i)));
                return true;
            } 
        }
        return true;
    }

    void printSymbolTables(){
        if(Globals::dump_symbol_table){
            Logging::logMessage("\n\n:: Symbol Table Dump ::\n\n");
            Logging::logMessage("Symbol table format: \n\t[address] <name>:<value>\n");
            for(int i = 0; i < 4; i++){
                Logging::logMessage(std::string("--- " + ::symbolTableNameToString(symbol_tables[i]->ST_TYPE) + " ---"));
                symbol_tables[i]->printSymbolTable();
            }
            Logging::logMessage(" --- end Symbol Table Dump --- \n");
        }
    }

    std::vector<std::shared_ptr<ThreeOpCode> > outputSymbolTable(){
        std::vector<std::shared_ptr<ThreeOpCode> > output;
        for(int i = 0; i < 4; i++){
            std::vector<std::shared_ptr<ThreeOpCode> > st_out = symbol_tables[i]->buildSymbolTableOutput();
            output.insert(output.end(), st_out.begin(), st_out.end());
        }
        return output;
    }



    bool offsetST(int memory_offset) {
        Logging::logMessage(":: Symbol Table Transformations :: \n\n");
        Logging::logConditionalMessage(Globals::output_symbol_table_operations, " \n--- Beginning Symbol Table Transformations --- \n");
        for(int i = 0; i < 4; i++){
            memory_offset += symbol_tables[i]->applyOffset(memory_offset);
        }
        Logging::logConditionalMessage(Globals::output_symbol_table_operations, " \n\n--- End Symbol Table Transformations --- \n\n");
        return true;
    }
} // SymbolTableController
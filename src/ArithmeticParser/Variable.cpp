#include "ArithmeticParser/Variable.h"

Variable::Variable(std::string name_in)
{
    tt = TOC_TYPES::VARIABLE_E;
    name = name_in;

    ALL_ST_SEARCH_RESULT x = SymbolTableController::getVariable(name);
    if(x.found){
        st_entry = x.result;
    } else {
        Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Variable " + std::string(name) + " not found in Symbol Table."));
        st_entry = SymbolTableController::addUnDeclaredVariable(name, std::string(), ST_ENTRY_TYPE::UNASSIGNED_T);
    }    
}

TOC_RETURN_VALUE Variable::generateThreeOPCode(int &starting_address){
    ALL_ST_SEARCH_RESULT x = SymbolTableController::getVariable(name);
    if(x.found){
        st_entry = x.result;
        if(x.result->assigned){
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Returning already existing variable " + std::string(name) + " in location " + std::to_string(st_entry->base_memory_address)));
        } else {
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Returning already existing, unassigned variable " + std::string(name) + " in location " + std::to_string(st_entry->base_memory_address)));
        }
        return {{}, st_entry};
    } else {
        std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::DATA_SET, false)));
        starting_address += pre_string.size();
        return {
                pre_string,
                st_entry
        };
    }
}
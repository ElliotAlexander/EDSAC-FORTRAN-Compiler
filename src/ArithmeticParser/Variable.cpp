#include "ArithmeticParser/Variable.h"

Variable::Variable(std::string name_in)
{
    tt = TOC_TYPES::VARIABLE_E;
    name = name_in;

    ALL_ST_SEARCH_RESULT x = getVariable(name);
    if(x.found){
        st_entry = x.result;
    } else {
        Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Variable " + std::string(name) + " not found in Symbol Table."));
        st_entry = addUnDeclaredVariable(name, std::string(), ST_ENTRY_TYPE::UNASSIGNED_T);
    }    
}

TOC_RETURN_VALUE Variable::generateThreeOPCode(){
    ALL_ST_SEARCH_RESULT x = getVariable(name);
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
        return {
                pre_string,
                st_entry
        };
    }
}
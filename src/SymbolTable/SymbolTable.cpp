#include "SymbolTable/SymbolTable.h"




/**
 * SymbolTable::SymbolTable(SYMBOL_TABLE_TYPE st) : ST_TYPE(st) 
 * 
 * This method initialises the symbol table, definining its type from a constructor argument.
 * 
 * 
 * This method also intiialsies a buffer flush value on the symbol table, in the instance that the type of symbol table 
 * is set to declared var. 
 * 
 * This buffer flush variable is used as a bin value for the scope of all values within it.
 * 
 * 
 **/ 
SymbolTable::SymbolTable(SYMBOL_TABLE_TYPE st) : ST_TYPE(st) {  
    Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Initialising " + std::to_string(st) + " Symbol Table. "));
	if (st == SYMBOL_TABLE_TYPE::DECLARED_VAR) {
		ST_ENTRY entry = {
				ST_ENTRY_TYPE::UNASSIGNED_T,
				false,
				rolling_memory_addr,
				std::string("0")
            };
		SymbolTable::st_map.insert(std::map<std::string, std::shared_ptr<ST_ENTRY> >::value_type(Globals::BUFFER_FLUSH_NAME, std::make_shared<ST_ENTRY>(entry)));
        SymbolTable::rolling_memory_addr += 1;
	}
}



/**
 * 
 * bool SymbolTable::remove(std::string name)
 * 
 * 
 * This function removes an entry from the symbol table.
 * Entries are referenced by name.
 * The return value indicates whether the value was successfully removed - if tno value exists, then the return val is false.
 * 
 * 
 **/ 
bool SymbolTable::remove(std::string name){
    std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it = SymbolTable::st_map.find(name);
    std::shared_ptr<ST_ENTRY> ptr;
    if(it != SymbolTable::st_map.end()) {
        SymbolTable::freed_vars.push_back(it->second->base_memory_address);
        SymbolTable::st_map.erase(it);
        return true;
    } else {
        Logging::logConditionalWarnMessage(Globals::output_symbol_table_operations, "Failed to find variable " + name);
        return false;
    }
}


// We can't use polymorphic values, so a string will have to do.
/**
 * 
 *  This function is used for adding variables to the symbol table.
 *  the function takes the name, value and type of an entry, and returns a pointer to the entry.
 *  
 * 
 **/ 
std::shared_ptr<ST_ENTRY> SymbolTable::add(std::string name, std::string value, ST_ENTRY_TYPE type){
    bool assigned = value.empty();
    int variable_index;
    if(!SymbolTable::freed_vars.empty()){
        variable_index = freed_vars.back();
        SymbolTable::freed_vars.pop_back();
        Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Using previously freed memory address " + std::to_string(variable_index)));
    } else {
        variable_index = SymbolTable::rolling_memory_addr;
    }

    ST_ENTRY temp = {
        type,
        assigned,
        variable_index,
        value
    };

    std::shared_ptr<ST_ENTRY> p = std::make_shared<ST_ENTRY>(temp);
    SymbolTable::st_map.insert(std::map<std::string, std::shared_ptr<ST_ENTRY> >::value_type(name, p));
    Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Added " + name + " to symbol table " + symbolTableNameToString(ST_TYPE)));
    rolling_memory_addr += 1;
    return p;
}


/**
 * 
 * 
 * 
 * This fucntion is used for retrieveing values from the symbol table.
 * 
 * Functions are referenced by name, and a pointer to the value of the symbol table entry is returned.
 * 
 * 
 * 
 **/ 
ST_QUERY_RESULT SymbolTable::get(std::string name){
    std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it = SymbolTable::st_map.find(name);
    if(it != SymbolTable::st_map.end()) {
        Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, "Loaded " + name + " from " + symbolTableNameToString(ST_TYPE));
        return {true, it->second};
    } else {
        std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it2 = SymbolTable::linked_st_map.find(name);
        if(it2 != SymbolTable::linked_st_map.end()){
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, "Loaded Linked Variable" + name + " from " + symbolTableNameToString(ST_TYPE));
            return {true, it2->second};
        } else {
            return {false, nullptr };
        }
    }
}

void SymbolTable::printSymbolTable(){
    std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it;
    for ( it = st_map.begin(); it != st_map.end(); it++ ){
        Logging::logMessage(std::string("[" + std::to_string(it->second->base_memory_address) + "] " + it->first + ":" + it->second->value));
    }


    // TODO
    std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it2;
    for ( it2 = linked_st_map.begin(); it2 != linked_st_map.end(); it2++ ){
        Logging::logMessage(std::string("[" + std::to_string(it2->second->base_memory_address) + "] " + it2->first + ":" + it2->second->value));
    }

    Logging::logNewLine();
}


std::vector<std::shared_ptr<ThreeOpCode> > SymbolTable::buildSymbolTableOutput(){
    std::vector<std::shared_ptr<ThreeOpCode> > output_str;
    if(SymbolTable::ST_TYPE == SYMBOL_TABLE_TYPE::TEMP_VAR){
        typedef std::function<bool(std::pair<std::string, std::shared_ptr<ST_ENTRY> >, std::pair<std::string, std::shared_ptr<ST_ENTRY> >)> Comparator;
        Comparator compFunctor = [](std::pair<std::string, std::shared_ptr<ST_ENTRY> > elem1 ,std::pair<std::string, std::shared_ptr<ST_ENTRY> > elem2)
        {
            return std::stoi(elem1.first) < std::stoi(elem2.first);
        };

        std::set<std::pair<std::string, std::shared_ptr<ST_ENTRY> >, Comparator> sorted_symbol_table(st_map.begin(), st_map.end(), compFunctor);
        for (std::pair<std::string, std::shared_ptr<ST_ENTRY> > element : sorted_symbol_table) {
            output_str.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::string(element.second->value), THREE_OP_CODE_OPERATIONS::DATA_SET, false)));
        }
    } else {
        std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it;
        for ( it = st_map.begin(); it != st_map.end(); it++ ){
            output_str.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(std::string(it->second->value), THREE_OP_CODE_OPERATIONS::DATA_SET, false)));
        }
    }
    return output_str;
}

bool SymbolTable::addLinkedVariable(std::shared_ptr<ST_ENTRY> linked_var, std::string name){
    std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it = SymbolTable::st_map.find(name);
    std::shared_ptr<ST_ENTRY> ptr;
    if(it != SymbolTable::st_map.end()) {
        Logging::logConditionalWarnMessage(Globals::output_symbol_table_operations, "Warning - variable " + name + " already exists in Symbol Table. It's value will be overwritten.");
        it->second = linked_var;
        return false;
    } else {
        linked_st_map.insert(std::map<std::string, std::shared_ptr<ST_ENTRY> >::value_type(name, linked_var));
        Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, "Adding linked variable " + name + " to address + " + std::to_string(linked_var->base_memory_address));
        return true;
    }

}


int SymbolTable::applyOffset(int memory_offset){
    Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, "Applying memory offset of " + std::to_string(memory_offset) + " to Symbol Table " + ::symbolTableNameToString(SymbolTable::ST_TYPE));

    if(SymbolTable::ST_TYPE == SYMBOL_TABLE_TYPE::TEMP_VAR){
        typedef std::function<bool(std::pair<std::string, std::shared_ptr<ST_ENTRY> >, std::pair<std::string, std::shared_ptr<ST_ENTRY> >)> Comparator;
        Comparator compFunctor = [](std::pair<std::string, std::shared_ptr<ST_ENTRY> > elem1 ,std::pair<std::string, std::shared_ptr<ST_ENTRY> > elem2)
        {
            return std::stoi(elem1.first) < std::stoi(elem2.first);
        };

        std::set<std::pair<std::string, std::shared_ptr<ST_ENTRY> >, Comparator> sorted_symbol_table(st_map.begin(), st_map.end(), compFunctor);

        int offset_amount = 0;
        for (std::pair<std::string, std::shared_ptr<ST_ENTRY> > element : sorted_symbol_table) {
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Applying memory offset of " + std::to_string(memory_offset) + ": " + std::to_string(element.second->base_memory_address) + " -> " + std::to_string(element.second->base_memory_address + memory_offset)));
            element.second->base_memory_address += memory_offset;
            offset_amount++;
        }
        return offset_amount;
    } else {
        std::map<std::string, std::shared_ptr<ST_ENTRY> >::iterator it;
        int offset_amount = 0;
        for ( it = st_map.begin(); it != st_map.end(); it++ ){
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Applying memory offset of " + std::to_string(memory_offset) + ": " + std::to_string(it->second->base_memory_address) + " -> " + std::to_string(it->second->base_memory_address + memory_offset)));
            it->second->base_memory_address += memory_offset;
            offset_amount++;
        }
        return offset_amount;
    }
}


bool SymbolTable::clearSymbolTable(){
    Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, "Clearing Symbol Table " + ::symbolTableNameToString(SymbolTable::ST_TYPE));
    SymbolTable::st_map.clear();
    return true;
}
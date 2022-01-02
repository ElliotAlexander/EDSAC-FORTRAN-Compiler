#include "SymbolTable/STController.h"

namespace SymbolTableController{

    bool in_function_scope;
    std::string function_scope_name;

    /**
     * 
     * These are the Main program block symbol tables. 
     * They're used for all variables outside of Function or Subroutine blocks. 
     * 
     **/ 
    std::unique_ptr<SymbolTable> symbol_tables[4] = {
        std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::DECLARED_VAR)),
        std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::UNDECLARED_VAR)),
        std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::TEMP_VAR)),         // Temp vars are declared as only ever passed or access by reference .
        std::unique_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::COMMON_VAR))        // Common isn't implemented, so isn't used.
    };

    // each object is initialised with another set of four unique symbol tables
    // Each fucntion or subroutine scope is mapped to a set of symbol tables.
    // Once entering or leaving function scope, we switch to this set of symbol tables.
    // They are *NOT* cleared between scope instances.
    std::map<std::string, std::vector<std::shared_ptr<SymbolTable> > > function_symbol_tables;

    /**
     *  bool addLinkedVariable(std::shared_ptr<ST_ENTRY> value, std::string name)
     *  
     *  Input:
     *      value -> Variable value, passed as a reference to another variable in the symbol table.
     *      name -> the name to map the existing value onto. 
     * 
     * 
     *  Output -> Success or failure of the link. 
     *      
     * 
     * This function takes an input variable as a reference to an existing variable, and adds a new mapping. 
     * For example - if a variable was declared as X = 10, where Xs is a pointer to the symbol table entry for X
     * The variable Y could then also be mapped to the same value as X, via addLinkedVariable(xs, "Y")
     * 
     **/ 
    bool addLinkedVariable(std::shared_ptr<ST_ENTRY> value, std::string name){
        if(in_function_scope){
            Logging::logConditionalErrorMessage(function_scope_name.empty(), "Error - entered function scope symbol table without a symbol table being assigned.");
            return function_symbol_tables.find(function_scope_name)->second.at(0)->addLinkedVariable(value, name);
        }
        return symbol_tables[0]->addLinkedVariable(value, name);
    }

    /**
     * 
     * This block of 'put' methods largely encapsulates functionality for adding a varible.
     * The type of the varitable is determined by the function type.
     * The value of ST_ENTRY_TYPE is ignored. 
     * 
     * std::shared_ptr<ST_ENTRY> addCommon(std::string common_block_label, std::string name, std::string value, ST_ENTRY_TYPE type)
     * 
     * Input:
     *      common_block_label -> Not implemented, planned support for named common blocks. However, common blocks are not implemented.
     *                            If common blocks were implemetned, this value should represent the label of the common block.
     * 
     *      name -> The name of the variable to add. 
     * 
     *      type -> Unused. 
     * 
     * 
     * Output:
     *      A reference to the symbol table entry for the finished variable. 
     * 
     **/
    std::shared_ptr<ST_ENTRY> addCommon(std::string common_block_label, std::string name, std::string value, ST_ENTRY_TYPE type) {
        if(in_function_scope){
            Logging::logConditionalErrorMessage(function_scope_name.empty(), "Error - entered function scope symbol table without a symbol table being assigned.");
            return function_symbol_tables.find(function_scope_name)->second.at(3)->add(name, value, type);
        }
        return symbol_tables[3]->add(name, value, type);
    }


    /**
     * std::shared_ptr<ST_ENTRY> addTemp(std::string value, ST_ENTRY_TYPE type)
     * 
     * Input:
     *      std::string value -> The value of the variable. 
     *      ST_ENTRY_TYPE type -> Unused. This represents the type of the variable at conception,
     * 
     * Output:
     *      A reference to the symbol table entry for the finished variable. 
     * 
     * Temporary variables are declared in the code with no further use - i.e. 
     * They are declared when a specific operation requires them, and accessed only by reference.
     * A temporary variable can be disgarded immediately after the completion of the intiialising operation. 
     **/
    std::shared_ptr<ST_ENTRY> addTemp(std::string value, ST_ENTRY_TYPE type) {
        if(in_function_scope){
            Logging::logConditionalErrorMessage(function_scope_name.empty(), "Error - entered function scope symbol table without a symbol table being assigned.");
            return function_symbol_tables.find(function_scope_name)->second.at(2)->add(std::to_string(function_symbol_tables.find(function_scope_name)->second.at(2)->rolling_memory_addr), value, type);
        }
        return symbol_tables[2]->add(std::to_string(symbol_tables[2]->rolling_memory_addr), value, type);
    }

    /**
     * std::shared_ptr<ST_ENTRY> addTemp(std::string value, ST_ENTRY_TYPE type)
     * 
     * Input:
     *      std::string value -> The value of the variable. 
     *      ST_ENTRY_TYPE type -> Unused. This represents the type of the variable at conception,
     * 
     * Output:
     *      A reference to the symbol table entry for the finished variable. 
     * 
     * Temporary variables are declared in the code with no further use - i.e. They are declared when a specific operation requires them, and accessed only by reference.
     * A temporary variable can be disgarded immediately after the completion of the intiialising operation. 
     **/
    std::shared_ptr<ST_ENTRY> addDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type){
        if(in_function_scope){
            Logging::logConditionalErrorMessage(function_scope_name.empty(), "Error - entered function scope symbol table without a symbol table being assigned.");
            return function_symbol_tables.find(function_scope_name)->second.at(0)->add(name, value, type);
        }
        return symbol_tables[0]->add(name, value, type);
    }

    std::shared_ptr<ST_ENTRY> addUnDeclaredVariable(std::string name, std::string value, ST_ENTRY_TYPE type){
        if(in_function_scope){
            Logging::logConditionalErrorMessage(function_scope_name.empty(), "Error - entered function scope symbol table without a symbol table being assigned.");
            return function_symbol_tables.find(function_scope_name)->second.at(0)->add(name, value, type);
        }
        return symbol_tables[1]->add(name, value, type);
    }

    ALL_ST_SEARCH_RESULT getVariable(std::string name){
        if(in_function_scope){
            std::vector<std::shared_ptr<SymbolTable> > func_st = function_symbol_tables.find(function_scope_name)->second;
            ST_QUERY_RESULT func_declared_res = func_st.at(0)->get(name);
            if(func_declared_res.found){
                Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Found symbol table entry for " + name + " in declared variables for function " + function_scope_name));
                return {0, true, func_declared_res.result};
            } else {
                func_declared_res = func_st.at(1)->get(name);
                if(func_declared_res.found){
                    Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Found symbol table entry for " + name + " in undeclared variables for function " + function_scope_name));
                    return {0, true, func_declared_res.result};
                }
            }
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Failed to find variable " + name + " in function scope. Checking Global Scope next."));
        }


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

            for(std::map<std::string, std::vector<std::shared_ptr<SymbolTable> > >::iterator it = function_symbol_tables.begin(); it != function_symbol_tables.end(); ++it ){
                Logging::logMessage("--- Function " + it->first + " ---\n");
                for(std::vector<std::shared_ptr<SymbolTable> >::iterator s_it = it->second.begin(); s_it != it->second.end(); ++s_it) {
                    Logging::logMessage(std::string("--- " + ::symbolTableNameToString((*s_it)->ST_TYPE) + " ---"));
                    (*s_it)->printSymbolTable();
                }
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



        for(std::map<std::string, std::vector<std::shared_ptr<SymbolTable> > >::iterator it = function_symbol_tables.begin(); it != function_symbol_tables.end(); ++it ){
            for(std::vector<std::shared_ptr<SymbolTable> >::iterator s_it = it->second.begin(); s_it != it->second.end(); ++s_it) {
                std::vector<std::shared_ptr<ThreeOpCode> > st_func = (*s_it)->buildSymbolTableOutput();
                output.insert(output.end(), st_func.begin(), st_func.end());
            }
        }

        return output;
    }

    bool enterFunctionScope(std::string function_name){

        if(in_function_scope){
            Logging::logErrorMessage("Recursive Function / Subroutine call detected! This is not supported.");
            Logging::logErrorMessage("Compilation will exit.");
            exit(1);
        }
        std::map<std::string, std::vector<std::shared_ptr<SymbolTable> > >::iterator it = function_symbol_tables.find(function_name);
        Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Calling function " + function_name + ".");
        if(it != function_symbol_tables.end()) {
            Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Loaded function symbol table for function " + function_name);
        } else {
            Logging::logConditionalInfoMessage(Globals::output_function_mappings, "Adding new function symbol table for function " + function_name);
            std::vector<std::shared_ptr<SymbolTable> > vect;
            vect.push_back(std::shared_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::DECLARED_VAR)));
            vect.push_back(std::shared_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::UNDECLARED_VAR)));
            vect.push_back(std::shared_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::TEMP_VAR)));
            vect.push_back(std::shared_ptr<SymbolTable>(new SymbolTable(SYMBOL_TABLE_TYPE::COMMON_VAR)));
            function_symbol_tables.insert(std::map<std::string, std::vector<std::shared_ptr<SymbolTable> > >::value_type(function_name, vect));
        }

        in_function_scope = true;
        function_scope_name = function_name;
        Logging::logConditionalInfoMessage(Globals::output_function_mappings,"Entering Function Scope");
        return true;
    }


    bool exitFunctionScope(){
        Logging::logConditionalInfoMessage(Globals::output_function_mappings,"Leaving function scope.");
        in_function_scope = false;
        function_scope_name = "";
        return true;
    }

    bool offsetST(int memory_offset) {
        Logging::logConditionalMessage(Globals::output_symbol_table_operations, ":: Symbol Table Transformations :: \n\n");
        Logging::logConditionalMessage(Globals::output_symbol_table_operations, "\n Offsetting symbol table by " + std::to_string(memory_offset) + ".\n");
        Logging::logConditionalMessage(Globals::output_symbol_table_operations, " \n--- Beginning Symbol Table Transformations --- \n");
        for(int i = 0; i < 4; i++){
            memory_offset += symbol_tables[i]->applyOffset(memory_offset);
        }


        for(std::map<std::string, std::vector<std::shared_ptr<SymbolTable> > >::iterator it = function_symbol_tables.begin(); it != function_symbol_tables.end(); ++it ){
            for(std::vector<std::shared_ptr<SymbolTable> >::iterator s_it = it->second.begin(); s_it != it->second.end(); ++s_it) {
                memory_offset += (*s_it)->applyOffset(memory_offset);
            }
        }

        Logging::logConditionalMessage(Globals::output_symbol_table_operations, " \n\n--- End Symbol Table Transformations --- \n\n");
        return true;
    }
}
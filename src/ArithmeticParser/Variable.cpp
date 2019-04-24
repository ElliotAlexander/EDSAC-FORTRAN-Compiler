#include "ArithmeticParser/Variable.h"


/**
 *  Class Variable  
 *      
 *  This class is a possible leaf of the parse tree - representing a symbol table entry.
 *  This class effectively wraps the name of the variable.
 *  No three op code is generated from this class. 
 *  When called, the class registers itself with the symbol table. If no value is found in the symbol table, a placeholder is generated. 
 *  The class then returns an empty list and a refereence to the symbol table.
 * 
 *  Member variables: 
 *         std::string name -> The name of the variable represented by this class.
 **/
Variable::Variable(std::string name_in)
{

	// This is a hotfix for some weird behaviour on MSVC + flex + bison 
	// When pulling variable names, the next cahracter (the op) is included
	// Op still processes fine

    // This block of code allivietes this issue by ensuring that no operation characters are pulled into the variable name.
    // Variable names are always Alphanumeric, so this fix should never be detrimental. 
	char symbols[] = { '+', '/', '-', '*', '^' };
	int symbols_size = sizeof(name_in) / sizeof(char);

	for (int j = 0; j < symbols_size; j++)
		std::replace(name_in.begin(), name_in.end(), symbols[j], ' ');
	
    // See above issue - weird characters being pulled in from flex
    name_in = ::stripWhitespaceString(name_in);
	

	tt = TOC_TYPES::VARIABLE_E; // Set the toc type, so we can identify this class on the top level.
    name = name_in;             // Setup internal representation. We don't do this in the constructor.


    /**
     * 
     * The class now registers itself with the symbol table. If a variable does not exist, it is added as an undeclared variable.
     * **/
    ALL_ST_SEARCH_RESULT x = SymbolTableController::getVariable(name);
    if(x.found){
        st_entry = x.result;
    } else {
        // Adding the variable here means that when we come to generate three op code, the variable already exists.
        Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Variable " + std::string(name) + " not found in Symbol Table."));
        st_entry = SymbolTableController::addUnDeclaredVariable(name, std::string(), ST_ENTRY_TYPE::UNASSIGNED_T);
    }    
}

TOC_RETURN_VALUE Variable::generateThreeOPCode(int &starting_address){
    ALL_ST_SEARCH_RESULT x = SymbolTableController::getVariable(name);

    /**
     * 
     * Return a reference to the symbol table entry for the variable. 
     * No three op code is required, the data values are generated by the symbol table.
     * Ultimately, the symbol table handles the instructiojn values for data, and just returns a reference to where the data values 'will' be, once compilation has finsihed.
     * **/
    if(x.found){

        // note that because we don't return any three op code (an empty array), there's no need to iterate starting_address.
        st_entry = x.result;
        if(x.result->assigned){
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Returning already existing variable " + std::string(name) + " in location " + std::to_string(st_entry->base_memory_address)));
        } else {
            Logging::logConditionalInfoMessage(Globals::output_symbol_table_operations, std::string("Returning already existing, unassigned variable " + std::string(name) + " in location " + std::to_string(st_entry->base_memory_address)));
        }
        return {{}, st_entry};
    } else {
        // This should NEVER trigger.
        //  The variable is always added if not found in the constructor.
        // If x is found, something has gone wrong.
        std::vector<std::shared_ptr<ThreeOpCode> > pre_string;
        pre_string.push_back(std::shared_ptr<ThreeOpCode>(new ThreeOpCode(st_entry, THREE_OP_CODE_OPERATIONS::DATA_SET, false)));
        starting_address += pre_string.size();
        return {
                pre_string,
                st_entry
        };
    }
}